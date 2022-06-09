
#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <time.h>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>


using namespace std;

class Function_pool
{

private:
    std::queue<std::function<void()>> m_function_queue;
    std::mutex m_lock;
    std::condition_variable m_data_condition;
    std::atomic<bool> m_accept_functions;

public:

    Function_pool();
    ~Function_pool();
    void push(std::function<void()> func);
    void done();
    void infinite_loop_func();
};


WIN32_FIND_DATA findfile,f;
HANDLE hfile;
LPCSTR file = "C:\\*";
string name = "s.txt";
string path = "C:\\", path2 = "*";


void logic(HANDLE rhfile) {
    

    while (FindNextFile(rhfile, &findfile))
    {
        Sleep(10);
        wcout << " " << findfile.cFileName << endl;
       
        path2 = findfile.cFileName;
        if (findfile.cFileName == name) {
            cout << "Find your file ";
            cout << path;
            wcout << findfile.cFileName << endl;
            return;
        }
    }
    
    path = "C:\\";
    path = path + path2;
    path = path + "\\*";
    cout << path << endl;
    rhfile = FindFirstFile((path + "*.*").c_str(), &findfile);

    while (FindNextFile(rhfile, &findfile))
    {
        Sleep(10);
        wcout << "-  " << findfile.cFileName << endl;

        path2 = findfile.cFileName;
  
        logic(rhfile);

    }
        
}
void find_file(string name1) {
    name = name1;
    hfile = FindFirstFile( file,&findfile);

    string path, path2;
    if (INVALID_HANDLE_VALUE == hfile)
    {
        cout << "error" << GetLastError() << endl;
        return ;
    }
    else {
          logic(hfile);
        }
    
    FindClose(hfile);

}
