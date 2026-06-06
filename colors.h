#pragma once
#include <iostream>
#include <windows.h>
 
// In case older Windows SDK doesn't define this
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
 
// Enable ANSI escape codes on Windows 10+ terminal
inline void enableColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
 
// ── Text Colors ──────────────────────────────
#define RED        "\033[31m"
#define GREEN      "\033[32m"
#define YELLOW     "\033[33m"
#define BLUE       "\033[34m"
#define MAGENTA    "\033[30m"
#define CYAN       "\033[36m"
#define WHITE      "\033[37m"
#define BOLD       "\033[1m"
#define RESET      "\033[0m"
 
// ── Shortcuts ────────────────────────────────
#define SUCCESS    GREEN
#define ERROR_C    RED
#define HEADER_C   CYAN
#define PROMPT_C   YELLOW
#define MENU_C     MAGENTA
#define TABLE_C    BLUE
#define DATA_C     WHITE