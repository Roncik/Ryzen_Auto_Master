#include <Windows.h>
#include <iostream>

void start_executable(LPCTSTR lpApplicationName, STARTUPINFO &si, PROCESS_INFORMATION &pi)
{
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    CreateProcess(lpApplicationName,
        NULL,           // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
    );

}

void HWNDmsg_ClickKey(HWND windowhandle, int VK_code)
{
    SetFocus(windowhandle);
    PostMessageA(windowhandle, WM_KEYDOWN, VK_code, NULL); //VK_RETURN = ENTER
    Sleep(5);
    PostMessageA(windowhandle, WM_KEYUP, VK_code, NULL);
}

void HWNDmsg_Click_n_times(HWND windowhandle, int VK_code, int n)
{
    SetFocus(windowhandle);
    for (int i = 0; i < n; i++)
    {
        HWNDmsg_ClickKey(windowhandle, VK_code);
    }
}

static INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    if (__argc > 2)
    {
        MessageBoxA(0, "Incorrect number of parameters", "Error", MB_OK);
        return 1;
    }
    int selected_profile = 1;
    if (__argc == 2)
    {
        char option = *(char*)__argv[1];
        switch (option)
        {
        case '1':
            break;
        case '2':
            selected_profile = 2;
            break;
        default:
            MessageBoxA(0, "Incorrect parameter", "Error", MB_OK);
            return 1;
        }
    }
    
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    const char* path = "C:\\Program Files\\AMD\\RyzenMaster\\bin\\AMD Ryzen Master.exe";

    //Start Ryzen Master software
    start_executable(path, si, pi);

    //Get popup window handle
    HWND popup_window = NULL;
    HWND main_window = NULL;
    while (!popup_window)
    {
        popup_window = FindWindowA(NULL, "AMD RYZEN MASTER");
        main_window = FindWindowA(NULL, "AMD RYZEN MASTER");
        Sleep(10);
    }

    //Send message to the window
    //SetForegroundWindow(popup_window);
    HWNDmsg_ClickKey(popup_window, VK_RETURN);

    while (!main_window && main_window == popup_window) //Get the main window
    {
        main_window = FindWindowA(NULL, "AMD RYZEN MASTER");
        Sleep(10);
    }
    
    Sleep(2000);
    main_window = FindWindowA(NULL, "AMD RYZEN MASTER");

    if (selected_profile == 1)
    {
        HWNDmsg_Click_n_times(main_window, VK_TAB, 8); //TAB*8 To get to profile 1
    }
    else if (selected_profile == 2)
    {
        HWNDmsg_Click_n_times(main_window, VK_TAB, 9); //TAB*9 To get to profile 2
    }

    Sleep(100);

    HWNDmsg_ClickKey(main_window, VK_RETURN); //Enter to select profile 1

    Sleep(100);

    if (selected_profile == 1)
    {
        HWNDmsg_Click_n_times(main_window, VK_TAB, 35); //TAB*35 To get to apply
    }
    else if (selected_profile == 2)
    {
        HWNDmsg_Click_n_times(main_window, VK_TAB, 34); //TAB*34 To get to apply
    }

    Sleep(100);

    HWNDmsg_ClickKey(main_window, VK_RETURN); //Enter to apply profile 1

    Sleep(100);

    //Close Ryzen Master
    PostMessageA(main_window, WM_CLOSE, 0, 0);

    return 0;
}