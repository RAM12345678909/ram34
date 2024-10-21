#include <iostream>
#include <Windows.h>
#include <objbase.h>
#include <atlbase.h>

using namespace std;

// Excel constants
const CLSID CLSID_Application = {0x00024500,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
const IID IID_Application = {0x000208D5,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
const DISPID DISPID_WORKBOOKS_OPEN = 234;
const DISPID DISPID_WORKBOOK_GET_ACTIVE_SHEET = 131;
const DISPID DISPID_RANGE_GET_USED_RANGE = 67;
const DISPID DISPID_RANGE_ITEM = 0;
const DISPID DISPID_VALUE = 0;

// Function to search for hash in Excel file
wstring searchHashInExcel(const wstring& filename, const wstring& hash) {
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        cerr << "Failed to initialize COM library" << endl;
        return L"";
    }

    // Start Excel application
    CComPtr<IDispatch> pExcelApp;
    hr = pExcelApp.CoCreateInstance(CLSID_Application);
    if (FAILED(hr)) {
        cerr << "Failed to start Excel application" << endl;
        CoUninitialize();
        return L"";
    }

    // Make Excel visible
    pExcelApp->PutProperty(0x0000000e, COleVariant(true));

    // Open the workbook
    VARIANT result;
    VARIANT filenameVariant;
    filenameVariant.vt = VT_BSTR;
    filenameVariant.bstrVal = SysAllocString(filename.c_str());
    hr = pExcelApp->Invoke(DISPID_WORKBOOKS_OPEN, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &result, &filenameVariant, NULL, NULL);
    if (FAILED(hr)) {
        cerr << "Failed to open workbook" << endl;
        CoUninitialize();
        return L"";
    }

    CComPtr<IDispatch> pWorkbook = result.pdispVal;

    // Get the active sheet
    CComVariant activeSheet;
    hr = pWorkbook->GetTypeInfo()->Invoke(pWorkbook, DISPID_WORKBOOK_GET_ACTIVE_SHEET, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, NULL, &activeSheet, NULL, NULL);
    if (FAILED(hr)) {
        cerr << "Failed to get active sheet" << endl;
        CoUninitialize();
        return L"";
    }
    CComPtr<IDispatch> pActiveSheet = activeSheet.pdispVal;

    // Get range of the used cells in the sheet
    CComVariant usedRange;
    hr = pActiveSheet->GetTypeInfo()->Invoke(pActiveSheet, DISPID_RANGE_GET_USED_RANGE, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, NULL, &usedRange, NULL, NULL);
    if (FAILED(hr)) {
        cerr << "Failed to get used range" << endl;
        CoUninitialize();
        return L"";
    }
    CComPtr<IDispatch> pUsedRange = usedRange.pdispVal;

    // Get values of the used range
    CComVariant valueVariant;
    hr = pUsedRange->GetTypeInfo()->Invoke(pUsedRange, DISPID_VALUE, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, NULL, &valueVariant, NULL, NULL);
    if (FAILED(hr)) {
        cerr << "Failed to get range values" << endl;
        CoUninitialize();
        return L"";
    }

    // Check if the value is a 2D SafeArray
    if (valueVariant.vt != VT_ARRAY || valueVariant.parray == NULL || valueVariant.parray->cDims != 2) {
        cerr << "Invalid range values" << endl;
        CoUninitialize();
        return L"";
    }

    // Get the SafeArray of values
    SAFEARRAY* pArray = valueVariant.parray;
    VARIANT cellValue;
    LONG rowIndex, columnIndex;
    LONG lowerRow, upperRow, lowerColumn, upperColumn;
    SafeArrayGetLBound(pArray, 1, &lowerRow);
    SafeArrayGetUBound(pArray, 1, &upperRow);
    SafeArrayGetLBound(pArray, 2, &lowerColumn);
    SafeArrayGetUBound(pArray, 2, &upperColumn);

    // Loop through cells to find the hash
    for (rowIndex = lowerRow; rowIndex <= upperRow; ++rowIndex) {
        for (columnIndex = lowerColumn; columnIndex <= upperColumn; ++columnIndex) {
            VARIANT cell;
            cell.vt = VT_I4;
            cell.lVal = columnIndex;
            hr = pUsedRange->GetTypeInfo()->Invoke(pUsedRange, DISPID_RANGE_ITEM, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, NULL, &cell, NULL, NULL);
            if (FAILED(hr)) {
                cerr << "Failed to get cell" << endl;
                CoUninitialize();
                return L"";
            }
            cellValue.vt = VT_EMPTY;
            hr = cell.pdispVal->GetTypeInfo()->Invoke(cell.pdispVal, DISPID_VALUE, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, NULL, &cellValue, NULL, NULL);
            if (FAILED(hr)) {
                cerr << "Failed to get cell value" << endl;
                CoUninitialize();
                return L"";
            }
            if (cellValue.vt == VT_BSTR && wstring(cellValue.bstrVal) == hash) {
                hr = pUsedRange->GetTypeInfo()->Invoke(pUsedRange, DISPID_RANGE_ITEM, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, NULL, &cell, NULL, NULL);
                if (FAILED(hr)) {
                    cerr << "Failed to get cell" << endl;
                    CoUninitialize();
                    return L"";
                }
                hr = cell.pdispVal->GetTypeInfo()->Invoke(cell.pdispVal, DISPID_VALUE, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, NULL, &cellValue, NULL, NULL);
                if (FAILED(hr)) {
                    cerr << "Failed to get cell value" << endl;
                    CoUninitialize();
                    return L"";
                }
                CComBSTR bstrResult = cellValue.bstrVal;
                wstring result(bstrResult);
                CoUninitialize();
                return result;
            }
        }
    }

    cerr << "Hash not found in Excel file" << endl;
    CoUninitialize();
    return L"";
}

int main() {
    wstring filename = L"Rainbow_Table_EXCEL.xlsx"; // Excel file containing hashed values
    wstring hashInput;
    wcout << L"Enter hash string: ";
    wcin >> hashInput;

    wstring originalText = searchHashInExcel(filename, hashInput);
    if (!originalText.empty()) {
        wcout << L"Original text: " << originalText << endl;
    } else {
        wcout << L"No matching hash found." << endl;
    }

    return 0;
}
