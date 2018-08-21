//
// Created by Jie on 2018/8/10.
//

#ifndef UNTITLED_CONSOLE_H
#define UNTITLED_CONSOLE_H

#include "Object.h"

#include <imgui.h>

class ConsoleEditor : public Object {
public:
    ConsoleEditor();
    ~ConsoleEditor();

    void ClearLog();
    void AddLog(const char *fmt, ...);
    void Draw(const char *title, bool *p_open);

private:
    bool LuaMode = false;
    char InputBuf[256];
    ImVector<char *> Items;
    bool ScrollToBottom;
    ImVector<char *> History;
    int HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImVector<const char *> Commands;

    void ExecCommand(const char *command_line);
    int TextEditCallback(ImGuiTextEditCallbackData *data);


    // Portable helpers
    static int Stricmp(const char *str1, const char *str2) {
        int d;
        while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) {
            str1++;
            str2++;
        }
        return d;
    }

    static int Strnicmp(const char *str1, const char *str2, int n) {
        int d = 0;
        while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) {
            str1++;
            str2++;
            n--;
        }
        return d;
    }

    static char *Strdup(const char *str) {
        size_t len = strlen(str) + 1;
        void *buff = malloc(len);
        return (char *) memcpy(buff, (const void *) str, len);
    }

    static void Strtrim(char *str) {
        char *str_end = str + strlen(str);
        while (str_end > str && str_end[-1] == ' ') str_end--;
        *str_end = 0;
    }

    static int TextEditCallbackStub(ImGuiTextEditCallbackData *data) {
        ConsoleEditor *console = (ConsoleEditor *) data->UserData;
        return console->TextEditCallback(data);
    }
};

#endif //UNTITLED_CONSOLE_H
