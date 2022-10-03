#ifndef CMD_H
#define CMD_H
#include <string>
#include  <direct.h>
#include  <stdio.h>
#include <sys/stat.h>
#include <vector>
using std::string;
using std::vector;

void cmdInit();
void parse_text(string &s);
void str_replace(string &s, string target, string re);
void write_back();
void run_text(vector<string> &order, bool is_show=true);
extern vector<vector<string>> file_data;
extern string file_path;

#endif // CMD_H
