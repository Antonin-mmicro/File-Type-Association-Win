// Dépendances
#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <commctrl.h>
#include <stdlib.h>

#pragma comment(lib, "comctl32.lib")

#define ID_OPTIONAPP1 201
#define ID_OPTIONAPP2 202
#define ID_OPTIONAPP3 203
#define ID_OPTIONAPP4 204
#define ID_OPTIONAPP5 205
#define ID_OPTIONAPP6 206

static HINSTANCE g_hInstance = NULL;
static HWND g_hButton = NULL;
static HWND g2_hButton = NULL;
static HWND g3_hButton = NULL;
static HWND g4_hButton = NULL;
static HWND g5_hButton = NULL;
static HWND g_hPopupWindow = NULL;
static HWND g_hListBox = NULL;

const char *firefoxhtml = "FirefoxHTML-308046B0AF4A39CB";
const char *firefoxurl  = "FirefoxURL-308046B0AF4A39CB";
const char *chrometype  = "ChromeHTML";
const char *Edgetype = "MSEdgeHTM";
const char *AcrobatTypePDF = "Acrobat.Document.DC";
const char *AcrobatTypeFDF = "Acrobat.FDFDoc";
const char *AcrobatTypeXDP = "Acrobat.XDPDoc";
const char *AcrobatTypeXFDF = "Acrobat.XFDFDoc";
const char *VLCTypeMP3 = "VLC.mp3";
const char *VLCTypeMP4 = "VLC.mp4";
const char *VLCTypeAVI = "VLC.avi";
const char *VLCTypeMKV = "VLC.mkv";
const char *VLCTypeWAV = "VLC.wav";
const char *VLCTypeFLAC = "VLC.flac";
const char *VLCTypeMOV = "VLC.mov";
const char *VLCTypeWMV = "VLC.wmv";
const char *VLCTypeFLV = "VLC.flv";
const char *VLCTypeOGG = "VLC.ogg";
const char *VLCTypeM4A = "VLC.m4a";
const char *OnlyOfficeDocument = "ONLYOFFICE.Document";
const char *OnlyOfficeSpreadsheet = "ONLYOFFICE.Spreadsheet";
const char *OnlyOfficePresentation = "ONLYOFFICE.Presentation";

const char *type = "";
const char *app  = "";
const char *app_name = "";

int g_exit_code = -1;

const char *allextensions[] = {
    ".html", ".htm", ".xhtml", ".xml", ".svg", ".mhtml",
    ".txt", ".csv", ".json", ".md", ".log",
    ".js", ".css", ".py", ".java", ".c", ".cpp", ".php", ".sh",
    ".yml", ".yaml", ".ini", ".conf",
    ".wasm", ".webmanifest", ".map", ".rdf",
    ".jpg", ".jpeg", ".png", ".gif", ".webp", ".avif", ".bmp", ".ico",
    ".mp4", ".webm", ".ogv", ".m4v", ".mov", ".3gp",
    ".avi", ".wmv", ".mkv", ".flv",
    ".mp3", ".aac", ".m4a", ".wav", ".ogg", ".oga", ".flac", ".opus",
    ".pdf", ".fdf", ".xdp", ".xfdf",
    ".doc", ".docx", ".rtf", ".odt",
    ".xls", ".xlsx", ".ods",
    ".ppt", ".pptx", ".odp",
    ".crt", ".pem", ".cer", ".der"
};

const char *extensionsfirefox[] = {
    ".html",".htm",".xhtml",".xml",".svg",".mhtml",".jpg",".jpeg",".png",".gif",".webp",".avif",
    ".bmp",".ico",".mp4",".webm",".ogv",".m4v",".mov",".3gp",".mp3",".aac",".m4a",".wav",".ogg",".oga",
    ".flac",".opus",".pdf",".txt",".csv",".json",".md",".log",".js",".css",".py",".java",".c",".cpp",
    ".php",".sh",".yml",".yaml",".ini",".conf",".wasm",".webmanifest",".map",".rdf",".crt",".pem",".cer",".der",
};
const int extensionsfirefox_count = sizeof(extensionsfirefox) / sizeof(extensionsfirefox[0]);

const char *extensionschrome[] = {
    ".html",".htm",".xhtml",".xml",".svg",".mhtml",".jpg",".jpeg",".png",".gif",".webp",".avif",
    ".bmp",".ico",".mp4",".webm",".ogv",".m4v",".mov",".3gp",".mp3",".aac",".m4a",".wav",".ogg",".oga",
    ".flac",".opus",".pdf",".txt",".csv",".json",".md",".log",".js",".css",".py",".java",".c",".cpp",
    ".php",".sh",".yml",".yaml",".ini",".conf",".wasm",".webmanifest",".map",".rdf",".crt",".pem",".cer",".der",
};
const int extensionschrome_count = sizeof(extensionschrome) / sizeof(extensionschrome[0]);

const char *extensionsedge[] = {
    ".html",".htm",".xhtml",".xml",".svg",".mhtml",".jpg",".jpeg",".png",".gif",".webp",".avif",
    ".bmp",".ico",".mp4",".webm",".ogv",".m4v",".mov",".3gp",".mp3",".aac",".m4a",".wav",".ogg",".oga",
    ".flac",".opus",".pdf",".txt",".csv",".json",".md",".log",".js",".css",".py",".java",".c",".cpp",
    ".php",".sh",".yml",".yaml",".ini", ".conf", ".wasm", ".webmanifest", ".map", ".rdf", ".crt", ".pem", ".cer", ".der",
};

const int extensionsedge_count = sizeof(extensionsedge) / sizeof(extensionsedge[0]);

const char *extensionsvlc[] = {
    ".mp4", ".avi", ".mov", ".wmv", ".mkv", ".flv", ".mp3", ".wav", ".m4a", ".flac", ".ogg"
};

const int extensionsvlc_count = sizeof(extensionsvlc) / sizeof(extensionsvlc[0]);

const char *extensionsonlyofficedocument[] = {
    ".doc", ".docx",".txt", ".rtf", ".odt", ".pdf",
};

const int extensionsonlyofficedocument_count = sizeof(extensionsonlyofficedocument) / sizeof(extensionsonlyofficedocument[0]);

const char *extensionsonlyofficespreadsheet[] = {
    ".xls", ".xlsx", ".csv", ".ods",
};

const int extensionsonlyofficespreadsheet_count = sizeof(extensionsonlyofficespreadsheet) / sizeof(extensionsonlyofficespreadsheet[0]);

const char *extensionsonlyofficepresentation[] = {
    ".ppt", ".pptx", ".odp",
};

const int extensionsonlyofficepresentation_count = sizeof(extensionsonlyofficepresentation) / sizeof(extensionsonlyofficepresentation[0]);

int is_extension_supported(const char *ext, const char *app_name) {
    if (strcmp(app_name, "Firefox") == 0) {
        for (int i = 0; i < extensionsfirefox_count; i++) {
            if (strcmp(ext, extensionsfirefox[i]) == 0) return 1;
        }
    } else if (strcmp(app_name, "Chrome") == 0) {
        for (int i = 0; i < extensionschrome_count; i++) {
            if (strcmp(ext, extensionschrome[i]) == 0) return 1;
        }
    } else if (strcmp(app_name, "Edge") == 0) {
        for (int i = 0; i < extensionsedge_count; i++) {
            if (strcmp(ext, extensionsedge[i]) == 0) return 1;
        }
    } else if (strcmp(app_name, "VLC Media Player") == 0) {
        for (int i = 0; i < extensionsvlc_count; i++) {
            if (strcmp(ext, extensionsvlc[i]) == 0) return 1;
        }
    } else if (strcmp(app_name, "OnlyOffice") == 0) {
        for (int i = 0; i < extensionsonlyofficedocument_count; i++) {
            if (strcmp(ext, extensionsonlyofficedocument[i]) == 0) return 1;
        }
        for (int i = 0; i < extensionsonlyofficespreadsheet_count; i++) {
            if (strcmp(ext, extensionsonlyofficespreadsheet[i]) == 0) return 1;
        }
        for (int i = 0; i < extensionsonlyofficepresentation_count; i++) {
            if (strcmp(ext, extensionsonlyofficepresentation[i]) == 0) return 1;
        }
    } else if (strcmp(app_name, "Adobe Acrobat Reader") == 0) {
        if (strcmp(ext, ".pdf") == 0 || strcmp(ext, ".fdf") == 0 ||
            strcmp(ext, ".xdp") == 0 || strcmp(ext, ".xfdf") == 0)
            return 1;
    }
    return 0;
}

LRESULT CALLBACK PopupWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == 4 && HIWORD(wParam) == LBN_SELCHANGE) {
                int sel = (int)SendMessageW(g_hListBox, LB_GETCURSEL, 0, 0);
                if (sel != LB_ERR) {
                    int ext_index = (int)SendMessageW(g_hListBox, LB_GETITEMDATA, sel, 0);
                    const char *selected_ext = allextensions[ext_index];

                    if (strcmp(app_name, "") != 0 && !is_extension_supported(selected_ext, app_name)) {
                        wchar_t msg[256];
                        swprintf(msg, 256, L"L'extension '%hs' n'est pas supportée par %hs", selected_ext, app_name);
                        MessageBoxW(hwnd, msg, L"Extension non supportée", MB_OK | MB_ICONWARNING);
                        return 0;
                    }

                    type = selected_ext;
                    wchar_t wbuf[256];
                    size_t converted = 0;
                    mbstowcs_s(&converted, wbuf, 256, selected_ext, _TRUNCATE);
                    SetWindowTextW(g_hButton, wbuf);

                    DestroyWindow(hwnd);
                    g_hPopupWindow = NULL;
                }
            }
            break;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}



DWORD WINAPI RunVerif(LPVOID lpParam) {
    system("powershell -ExecutionPolicy Bypass -File \"UCPD_HashRotation\\Verif Protection.ps1\"");
    return 0;
}


// Fenêtre principale
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            g_hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

            g_hButton = CreateWindowW(L"BUTTON", L"Type",
                                      WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                      20, 100, 120, 40,
                                      hwnd, (HMENU)1, g_hInstance, NULL);

            g2_hButton = CreateWindowW(L"BUTTON", L"App",
                                       WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                       300, 100, 120, 40,
                                       hwnd, (HMENU)2, g_hInstance, NULL);

            g3_hButton = CreateWindowW(L"BUTTON", L"Associate",
                                       WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                       150, 200, 120, 40,
                                       hwnd, (HMENU)3, g_hInstance, NULL);
            g4_hButton = CreateWindowW(L"BUTTON", L"Disable UCPD",
                                       WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                       300, 300, 120, 40,
                                       hwnd, (HMENU)4, g_hInstance, NULL);
            g5_hButton = CreateWindowW(L"BUTTON", L"Disable HashRotation",
                                       WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                       280, 400, 160, 40,
                                       hwnd, (HMENU)5, g_hInstance, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) { 
                if (g_hPopupWindow != NULL) DestroyWindow(g_hPopupWindow);

                WNDCLASSW wc_popup = {0};
                wc_popup.lpfnWndProc   = PopupWindowProc;
                wc_popup.hInstance     = g_hInstance;
                wc_popup.lpszClassName = L"PopupMenu";
                wc_popup.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                RegisterClassW(&wc_popup);

                RECT rect;
                GetWindowRect(g_hButton, &rect);

                g_hPopupWindow = CreateWindowExW(WS_EX_TOPMOST, L"PopupMenu", L"",
                                                 WS_POPUP | WS_BORDER | WS_VISIBLE,
                                                 rect.left, rect.bottom, 200, 200,
                                                 hwnd, NULL, g_hInstance, NULL);

                g_hListBox = CreateWindowW(L"LISTBOX", L"",
                                           WS_VISIBLE | WS_CHILD | WS_VSCROLL | LBS_STANDARD | LBS_NOTIFY,
                                           0, 0, 200, 200,
                                           g_hPopupWindow, (HMENU)4, g_hInstance, NULL);

                int allextensions_count = sizeof(allextensions)/sizeof(allextensions[0]);
                for (int i = 0; i < allextensions_count; i++) {
                    wchar_t wbuf[256];
                    size_t converted = 0;
                    mbstowcs_s(&converted, wbuf, 256, allextensions[i], _TRUNCATE);
                    int index = (int)SendMessageW(g_hListBox, LB_ADDSTRING, 0, (LPARAM)wbuf);
                    SendMessageW(g_hListBox, LB_SETITEMDATA, index, i);
                }

                SetFocus(g_hPopupWindow);

            } else if (LOWORD(wParam) == 2) {
                HMENU hMenu = CreatePopupMenu();
                AppendMenuW(hMenu, MF_STRING, ID_OPTIONAPP1, L"Firefox");
                AppendMenuW(hMenu, MF_STRING, ID_OPTIONAPP2, L"Chrome");
                AppendMenuW(hMenu, MF_STRING, ID_OPTIONAPP3, L"Edge");
                AppendMenuW(hMenu, MF_STRING, ID_OPTIONAPP4, L"Adobe Acrobat Reader");
                AppendMenuW(hMenu, MF_STRING, ID_OPTIONAPP5, L"VLC Media Player");
                AppendMenuW(hMenu, MF_STRING, ID_OPTIONAPP6, L"OnlyOffice");

                RECT rect;
                GetWindowRect(g2_hButton, &rect);

                UINT cmd = TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_NONOTIFY,
                                          rect.left, rect.bottom, 0, hwnd, NULL);

                if (cmd == ID_OPTIONAPP1) {
                    int isSupported = 0;
                    for (int i = 0; i < extensionsfirefox_count; i++) {
                        if (strcmp(type, extensionsfirefox[i]) == 0) {
                            isSupported = 1;
                            break;
                        }
                    }
                    if (strcmp(type, "http") == 0 || strcmp(type, "https") == 0) isSupported = 1;

                    if (isSupported) {
                        SetWindowTextW(g2_hButton, L"Firefox");
                        app = (strcmp(type, "http") == 0 || strcmp(type, "https") == 0) ? firefoxurl : firefoxhtml;
                        app_name = "Firefox";
                    } else {
                        wchar_t wmsg[256];
                        swprintf(wmsg, 256, L"Firefox n'est pas disponible pour ce type '%hs'", type);
                        MessageBoxW(hwnd, wmsg, L"Erreur", MB_OK | MB_ICONWARNING);
                        type = "";
                        SetWindowTextW(g_hButton, L"Type");
                        app_name = "";
                    }
                } else if (cmd == ID_OPTIONAPP2) {
                    int isSupported = 0;
                    for (int i = 0; i < extensionschrome_count; i++) {
                        if (strcmp(type, extensionschrome[i]) == 0) {
                            isSupported = 1;
                            break;
                        }
                    }
                    if (isSupported) {
                        SetWindowTextW(g2_hButton, L"Chrome");
                        app = chrometype;
                        app_name = "Chrome";
                    } else {
                        wchar_t wmsg[256];
                        swprintf(wmsg, 256, L"Chrome n'est pas disponible pour ce type '%hs'", type);
                        MessageBoxW(hwnd, wmsg, L"Erreur", MB_OK | MB_ICONWARNING);
                        type = "";
                        SetWindowTextW(g_hButton, L"Type");
                        app_name = "";
                    }
                } else if (cmd == ID_OPTIONAPP3) {
                    int isSupported = 0;
                    for (int i = 0; i < extensionsedge_count; i++) {
                        if (strcmp(type, extensionsedge[i]) == 0) {
                            isSupported = 1;
                            break;
                        }
                    }
                    if (isSupported) {
                        SetWindowTextW(g2_hButton, L"Edge");
                        app = Edgetype;
                        app_name = "Edge";
                    } else {
                        wchar_t wmsg[256];
                        swprintf(wmsg, 256, L"Edge n'est pas disponible pour ce type '%hs'", type);
                        MessageBoxW(hwnd, wmsg, L"Erreur", MB_OK | MB_ICONWARNING);
                        type = "";
                        SetWindowTextW(g_hButton, L"Type");
                        app_name = "";
                    }
                } else if (cmd == ID_OPTIONAPP4) {
                    int isSupported = 0;
                    if (strcmp(type, ".pdf") == 0) {
                        isSupported = 1;
                        app = AcrobatTypePDF;
                    } else if (strcmp(type, ".fdf") == 0) {
                        isSupported = 1;
                        app = AcrobatTypeFDF;
                    } else if (strcmp(type, ".xdp") == 0) {
                        isSupported = 1;
                        app = AcrobatTypeXDP;
                    } else if (strcmp(type, ".xfdf") == 0) {
                        isSupported = 1;
                        app = AcrobatTypeXFDF;
                    }

                    if (isSupported) {
                        SetWindowTextW(g2_hButton, L"Adobe Acrobat Reader");
                        app_name = "Adobe Acrobat Reader";
                    } else {
                        wchar_t wmsg[256];
                        swprintf(wmsg, 256, L"Adobe Acrobat Reader n'est pas disponible pour ce type '%hs'", type);
                        MessageBoxW(hwnd, wmsg, L"Erreur", MB_OK | MB_ICONWARNING);
                        type = "";
                        SetWindowTextW(g_hButton, L"Type");
                        app_name = "";
                    }
                } else if (cmd == ID_OPTIONAPP5) {
                    int isSupported = 0;
                    for (int i = 0; i < extensionsvlc_count; i++) {
                        if (strcmp(type, extensionsvlc[i]) == 0) {
                            isSupported = 1;
                            break;
                        }
                    }
                    if (isSupported) {
                        SetWindowTextW(g2_hButton, L"VLC Media Player");
                        if (strcmp(type, ".mp4") == 0) {
                            app = VLCTypeMP4;
                        } else if (strcmp(type, ".avi") == 0) {
                            app = VLCTypeAVI;
                        } else if (strcmp(type, ".mov") == 0) {
                            app = VLCTypeMOV;
                        } else if (strcmp(type, ".wmv") == 0) {
                            app = VLCTypeWMV;
                        } else if (strcmp(type, ".mp3") == 0) {
                            app = VLCTypeMP3;
                        } else if (strcmp(type, ".wav") == 0) {
                            app = VLCTypeWAV;
                        } else if (strcmp(type, ".m4a") == 0) {
                            app = VLCTypeM4A;
                        } else if (strcmp(type, ".flac") == 0) {
                            app = VLCTypeFLAC;
                        } else if (strcmp(type, ".ogg") == 0) {
                            app = VLCTypeOGG;
                        } else if (strcmp(type, ".flv") == 0) {
                            app = VLCTypeFLV;
                        }
                        app_name = "VLC Media Player";
                    } else {
                        wchar_t wmsg[256];
                        swprintf(wmsg, 256, L"VLC Media Player n'est pas disponible pour ce type '%hs'", type);
                        MessageBoxW(hwnd, wmsg, L"Erreur", MB_OK | MB_ICONWARNING);
                        type = "";
                        SetWindowTextW(g_hButton, L"Type");
                        app_name = "";
                    }
                } else if (cmd == ID_OPTIONAPP6) {
                    int isSupported = 0;
                    for (int i = 0; i < extensionsonlyofficedocument_count; i++) {
                        if (strcmp(type, extensionsonlyofficedocument[i]) == 0) {
                            isSupported = 1;
                            app = OnlyOfficeDocument;
                            break;
                        }
                    }
                    for (int i = 0; i < extensionsonlyofficespreadsheet_count; i++) {
                        if (strcmp(type, extensionsonlyofficespreadsheet[i]) == 0) {
                            isSupported = 1;
                            app = OnlyOfficeSpreadsheet;
                            break;
                        }
                    }
                    for (int i = 0; i < extensionsonlyofficepresentation_count; i++) {
                        if (strcmp(type, extensionsonlyofficepresentation[i]) == 0) {
                            isSupported = 1;
                            app = OnlyOfficePresentation;
                            break;
                        }
                    }

                    if (isSupported) {
                        SetWindowTextW(g2_hButton, L"OnlyOffice");
                        app_name = "OnlyOffice";
                    } else {
                        wchar_t wmsg[256];
                        swprintf(wmsg, 256, L"OnlyOffice n'est pas disponible pour ce type '%hs'", type);
                        MessageBoxW(hwnd, wmsg, L"Erreur", MB_OK | MB_ICONWARNING);
                        type = "";
                        SetWindowTextW(g_hButton, L"Type");
                        app_name = "";
                    }
                }

                DestroyMenu(hMenu);

            } else if (LOWORD(wParam) == 3) {
                if (type == "" && app == "") {
                    MessageBoxW(hwnd, L"Veuillez sélectionner un type et une application avant d'associer.", L"Erreur", MB_OK | MB_ICONWARNING);
                    return 0;
                } else if (type == "") {
                    MessageBoxW(hwnd, L"Veuillez sélectionner un type avant d'associer.", L"Erreur", MB_OK | MB_ICONWARNING);
                    return 0;
                } else if (app == "") {
                    MessageBoxW(hwnd, L"Veuillez sélectionner une application avant d'associer.", L"Erreur", MB_OK | MB_ICONWARNING);
                    return 0;
                } else{
                    printf("Vérification de la protection UCPD et HashRotation, veuillez patienter...\n");
                    int exit_code = system("powershell -ExecutionPolicy Bypass -File \"UCPD_HashRotation\\Verif Protection.ps1\"");
                    printf("Exit code: %d\n", exit_code);

                    if (exit_code == 0) {
                        char buffer[256];
                        sprintf(buffer, "SetUserFTA.exe %s %s", type, app);
                        system(buffer);
                    } else if (exit_code == 1 || exit_code == 5 || exit_code == 6) {
                        MessageBoxW(hwnd, L"Veuillez désactiver la rotation de hash via le bouton disponible avant d'associer un type à une application.", L"Protection active", MB_OK | MB_ICONWARNING);
                        return 0;
                    } else if (exit_code == 10) {
                        MessageBoxW(hwnd, L"Veuillez arrêter le service UCPD via le bouton disponible avant d'associer un type à une application.", L"Service actif", MB_OK | MB_ICONWARNING);
                        return 0;
                    } else if (exit_code == 11 || exit_code == 15 || exit_code == 16) {
                        MessageBoxW(hwnd, L"Veuillez désactiver la rotation de hash et arrêter le service UCPD via les boutons disponibles avant d'associer un type à une application.", L"Protection active", MB_OK | MB_ICONWARNING);
                        return 0;
                    } else {
                        MessageBoxW(hwnd, L"Une erreur inconnue est survenue lors de la vérification de la protection. Assurez-vous d'avoir lancé l'application en tant qu'administrateur et réessayez.", L"Erreur", MB_OK | MB_ICONERROR);
                        exit(1);
                    }
                }

                
            } else if (LOWORD(wParam) == 4) {
                printf("Assurez vous d'avoir lancé l'application en tant qu'administrateur pour que cette action fonctionne.\n");
                system("powershell -ExecutionPolicy Bypass -File \"UCPD_HashRotation\\UCPD.ps1\"");
            } else if (LOWORD(wParam) == 5) {
                printf("Assurez vous d'avoir lancé l'application en tant qu'administrateur pour que cette action fonctionne.\n");
                system("powershell -ExecutionPolicy Bypass -File \"UCPD_HashRotation\\HashRotation.ps1\"");
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const wchar_t CLASS_NAME[] = L"File Type Association";

    WNDCLASSW wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"File Type Association",
                                WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                450, 600,
                                NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}