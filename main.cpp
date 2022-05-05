#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tdh.h>
#include <iostream>
#include <string>
#include <unordered_map>

static std::unordered_map<std::string , UINT  > const HOTKEY_MODS({
    { "ALT",     MOD_ALT     },
    { "CONTROL", MOD_CONTROL },
    { "CTRL",    MOD_CONTROL },
    { "SHIFT",   MOD_SHIFT   },
    { "WINDOWS", MOD_WIN     },
    { "WIN",     MOD_WIN     },
});

static std::unordered_map<std::string, UINT  > const HOTKEY_KEYS ({
    { "BACKSPACE", VK_BACK },
    { "TAB", VK_TAB },
    { "CLEAR", VK_CLEAR },
    { "ENTER", VK_RETURN },
    { "PAUSE", VK_PAUSE },
    { "CAPSLOCK", VK_CAPITAL },
    { "ESC", VK_ESCAPE },
    { "SPACE", VK_SPACE },
    { "PAGEUP", VK_PRIOR },
    { "PAGEDOWN", VK_NEXT },
    { "END", VK_END },
    { "HOME", VK_HOME },
    { "LEFT", VK_LEFT },
    { "UP", VK_UP },
    { "RIGHT", VK_RIGHT },
    { "DOWN", VK_DOWN },
    { "PRINTSCREEN", VK_SNAPSHOT },
    { "INS", VK_INSERT },
    { "DEL", VK_DELETE },
    { "HELP", VK_HELP },
    { "NUMLOCK", VK_NUMLOCK },
    { "NUM0", VK_NUMPAD0 },
    { "NUM1", VK_NUMPAD1 },
    { "NUM2", VK_NUMPAD2 },
    { "NUM3", VK_NUMPAD3 },
    { "NUM4", VK_NUMPAD4 },
    { "NUM5", VK_NUMPAD5 },
    { "NUM6", VK_NUMPAD6 },
    { "NUM7", VK_NUMPAD7 },
    { "NUM8", VK_NUMPAD8 },
    { "NUM9", VK_NUMPAD9 },
    { "MULTIPLY", VK_MULTIPLY },
    { "ADD", VK_ADD },
    { "SEPARATOR", VK_SEPARATOR },
    { "SUBTRACT", VK_SUBTRACT },
    { "DECIMAL", VK_DECIMAL },
    { "DIVIDE", VK_DIVIDE },
    { "0", 0x30 },
    { "1", 0x31 },
    { "2", 0x32 },
    { "3", 0x33 },
    { "4", 0x34 },
    { "5", 0x35 },
    { "6", 0x36 },
    { "7", 0x37 },
    { "8", 0x38 },
    { "9", 0x39 },
    { "A", 0x41 },
    { "B", 0x42 },
    { "C", 0x43 },
    { "D", 0x44 },
    { "E", 0x45 },
    { "F", 0x46 },
    { "G", 0x47 },
    { "H", 0x48 },
    { "I", 0x49 },
    { "J", 0x4A },
    { "K", 0x4B },
    { "L", 0x4C },
    { "M", 0x4D },
    { "N", 0x4E },
    { "O", 0x4F },
    { "P", 0x50 },
    { "Q", 0x51 },
    { "R", 0x52 },
    { "S", 0x53 },
    { "T", 0x54 },
    { "U", 0x55 },
    { "V", 0x56 },
    { "W", 0x57 },
    { "X", 0x58 },
    { "Y", 0x59 },
    { "Z", 0x5A },
    { "F1", VK_F1 },
    { "F2", VK_F2 },
    { "F3", VK_F3 },
    { "F4", VK_F4 },
    { "F5", VK_F5 },
    { "F6", VK_F6 },
    { "F7", VK_F7 },
    { "F8", VK_F8 },
    { "F9", VK_F9 },
    { "F10", VK_F10 },
    { "F11", VK_F11 },
    { "F12", VK_F12 },
    { "F13", VK_F13 },
    { "F14", VK_F14 },
    { "F15", VK_F15 },
    { "F16", VK_F16 },
    { "F17", VK_F17 },
    { "F18", VK_F18 },
    { "F19", VK_F19 },
    { "F20", VK_F20 },
    { "F21", VK_F21 },
    { "F22", VK_F22 },
    { "F23", VK_F23 },
    { "F24", VK_F24 },
});

static void printHelpMes() {
    std::cout << "\n------- Usage ---------\n";
    std::cout << "HotkeyListener.exe -hotkey HOT_KEY_COMBINATION -program PATH_OF_PROGRAM\n";
    std::cout << "Example: HotkeyListener.exe -hotkey SHIFT+CONTROL+T -program C:\\log.cmd\n";
    std::cout << "Press CONTROL+C to terminate the program.\n";
    std::cout << "-----------------------\n\n";
    std::cout << "Supported KEY modifiers are: \n";
    for (auto pair : HOTKEY_MODS) {
        std::cout << pair.first << ", ";
    }
    std::cout << std::endl;
    std::cout << "Supported KEY codes are: \n";
    for (auto pair : HOTKEY_KEYS) {
        std::cout << pair.first << ", ";
    }
    std::cout << std::endl;

} 

int main(int argc, char** argv) {

    char* hotkey = NULL;
    char* program = NULL;

    // parse arg
    for (int i = 1; i < argc; ++i) {
        if ( strcmp(argv[i], "--help") == 0 ) {
            printHelpMes();
            return 1;
        }
        if (strcmp(argv[i], "-hotkey") == 0) {
            hotkey = argv[++i];
        }
        if (strcmp(argv[i], "-program") == 0) {
            program = argv[++i];
        }
    }
    if (hotkey == NULL || program == NULL) {
        std::cout << "!!! Missing required argument -hotkey or -program.\n";
        printHelpMes();
        return 1;
    }

    // process and validate
    UINT keyMod = 0;
    UINT keyCode = 0;
    auto token = strtok(hotkey, "+");
    for (;;) {
        auto prev = token;
        token = strtok(nullptr, "+");
        if (token == nullptr) {
            // parse key code at the end
            if (HOTKEY_KEYS.find(std::string(prev)) == HOTKEY_KEYS.end()) {
                std::cout << "!!! KEYCODE " << prev << " not sopported.\n";
                std::cout << "Supported KEY codes are: \n";
                for (auto pair : HOTKEY_KEYS) {
                    std::cout << pair.first << ", ";
                }
                std::cout << std::endl;
                return 0;
            }
            else {
                keyCode = HOTKEY_KEYS.at(std::string(prev));
            }
            break;
        }
        // parse key mod and combine
        if (HOTKEY_MODS.find(std::string(prev)) == HOTKEY_MODS.end()) {
            std::cout << "!!!! KEY modifier " << prev << " not sopported.\n";
            std::cout << "Supported KEY modifiers are: \n";
            for (auto pair : HOTKEY_MODS) {
                std::cout << pair.first << ", ";
            }
            std::cout << std::endl;
            return 0;
        }
        else {
            keyMod = keyMod | HOTKEY_MODS.at(std::string(prev));
        }
    }
    // avoid ctrl+c cuz need that to be a termination 
    if (keyCode == 0x43 && keyMod == MOD_CONTROL) {
        std::cout << "!!! Cannot use hotkey CONTROL+C, since this is what we use to terminate this program\n";
        return 0;
    }

    // register
    if (RegisterHotKey(NULL, 1, keyMod, keyCode))    //0x42 is 'b'
    {
        std::cout << "----- Listener started ------\n";
        std::cout << "Will call program " << program << ", when hotkey pressed\n";
    }
    else {
        std::cout << "!!! HotKey registration failed. \n";
        return 0;
    }

    // loop for listening message
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			std::cout <<   "!!! HOTKEY PRESSED, Run " << program << ":\n";
            // run thr program
            system(program);
		}
	}

	return 1;
}







