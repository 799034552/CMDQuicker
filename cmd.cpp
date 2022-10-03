#include "cmd.h"
#include <sys/stat.h>
#include<fcntl.h>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <windows.h>
#include <stdio.h>
#include <shellapi.h>
#include <stdlib.h>
#include <winnt.h>
using namespace std;

vector<vector<string>> file_data;
string file_path;

void str_replace(string &s, string target, string re)
{
    int p;
    while((p = s.find(target)) != string::npos)
    {
        s = s.substr(0, p) + re +s.substr(p + target.size());
    }

}
void cmdInit()
{
    char buff[500];
    getcwd(buff, 500);
    struct stat file_stat;
    strcat(buff, "\\data.conf");
    file_path.assign(buff);
    ifstream fstrm(buff);
    ofstream ofstrm;

    if (!fstrm.is_open()){
        ofstrm.open(buff, ofstream::app);
        ofstrm<<"测试连接&&&ping www.baidu.com";
        ofstrm.close();
    }
    else
    {
        string t;
        bool is_start=false;
         while(getline(fstrm, t))
         {
             if (t == "cmd start;")
             {
                 is_start = true;
                 file_data.push_back(vector<string>());
             }
             else if (t == "cmd end;" && is_start)
             {
                 is_start = false;

             }
             else if (is_start)
             {
                 file_data.back().push_back(t);
             }
         }
         for(const auto &x: file_data)
         {
             for(const auto &y: x)
             {
                qDebug()<<QString::fromUtf8(y);
             }
         }
    }


}

void parse_text(string &s)
{

}
void write_back()
{
    ofstream ofstrm(file_path, std::ios::out);
    if (ofstrm.is_open())
    {
        for(const auto &x: file_data)
        {
            ofstrm<<"cmd start;\n";
            for(const auto &y: x)
            {
                ofstrm << y << "\n";
            }
            ofstrm<< "cmd end;\n\n";
        }
        ofstrm.close();
    }
}

std::u16string UTF8ToUTF16(const std::string& source)
{
    #if defined(OS_WIN)
    #if _MSC_VER >= 1900
    std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> conv;
    auto begin_pos = reinterpret_cast<const int8_t*>(source.data());
    return (char16_t*)conv.from_bytes((char*)begin_pos, (char*)(begin_pos + source.size())).c_str();
    #else
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
    return conv.from_bytes(source);
    #endif
    #else
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
    return conv.from_bytes(source);
    #endif
}

void run_text(vector<string> &order, bool is_show)
{
    if (order.size() < 2) return;
    SECURITY_ATTRIBUTES sa;
      sa.nLength = sizeof(sa);
      sa.lpSecurityDescriptor = NULL;
      sa.bInheritHandle = TRUE;


      PROCESS_INFORMATION pi;
      STARTUPINFO si;
      BOOL ret = FALSE;

      DWORD flags = CREATE_NO_WINDOW;//CREATE_NEW_PROCESS_GROUP; //CREATE_NEW_CONSOLE;//CREATE_NO_WINDOW;
      if (is_show)
          flags = CREATE_NEW_CONSOLE;

      ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
      ZeroMemory(&si, sizeof(STARTUPINFO));
      si.cb = sizeof(STARTUPINFO);
      si.dwFlags |= STARTF_USESTDHANDLES;
      si.hStdInput = NULL;
      string code = "";
      for(int i = 1; i < order.size(); ++i)
          code += order[i] + " & ";
      code = "cmd.exe /k " + code;
    ret = CreateProcess(NULL,(LPWSTR)UTF8ToUTF16(code).c_str(), NULL, NULL, TRUE, flags, NULL, NULL, &si, &pi);

}
