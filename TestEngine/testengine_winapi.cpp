// Copyright © 2020 Mikhail Korobkov. All rights reserved.

#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <fstream>
#include <thread>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>

using namespace std;

vector<string> split(string str, string delimiter)
{
    vector<string> ans;
    auto p = str.find(delimiter);
    auto p1 = 0;
    while (p != string::npos)
    {
        ans.push_back(str.substr(p1, p - p1));
        p1 = p + delimiter.length();
        p = str.find(delimiter, p + delimiter.length());
    }
    ans.push_back(str.substr(p1, str.length() - p1));
    return ans;
}

bool str_endswith(string str, string _end)
{
    for (int i = _end.length() - 1, j = str.length() - 1; i >= 0; --i, --j)
    {
        if (_end[i] != str[j])
            return false;
    }
    return true;
}

void run_test(string prog_path, string test_archive_path, string input_file, bool &test_running)
{
    test_running = true;
    system((prog_path+" <"+test_archive_path+"/"+input_file+" >out.txt").c_str());
    test_running = false;
}

HANDLE GetProcessByName(string name)
{
    DWORD pid = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    if (Process32First(snapshot, &process))
    {
        do
        {
            if (string(process.szExeFile) == string(name))
            {
               pid = process.th32ProcessID;
               break;
            }
        } while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);

    if (pid != 0)
         return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    return NULL;
}

int main(int argc, char *argv[])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD defaultTextAttribute = csbi.wAttributes;
    const WORD RED = csbi.wAttributes / 16 * 16 + 4;
    const WORD GREEN = csbi.wAttributes / 16 * 16 + 2;

    if (argc <= 1 || strcmp(argv[1], "help") == 0)
    {
        cout << "Console applications testing service TestEngine."                                                                                          << endl <<
                "Created by Michael Korobkov (c) 2020. All rights reserved"                                                                                 << endl <<
                                                                                                                                                               endl <<
                "To test the .exe console application you need to specify a path for .exe file, path for the test archive and time and memory limits."      << endl <<
                "The applications output should not be redirected to the file, all the output you want to test must be on the screen"                       << endl <<
                "Test archive is a folder with files for the program input and it's expected output."                                                       << endl <<
                "There should be 2 files for each test set, one with the input data, the other with the expected output"                                    << endl <<
                "For example, file name with input data for test set #1 should be \"1\" or \"1.txt\" with no quotes."                                       << endl <<
                "The file with the expected output for this test set should be named \"1_a\" or \"1_a.txt\" with no quotes"                                 << endl <<
                "Time limit is a real number, which sets maximum execution time for a program in seconds"                                                   << endl <<
                "Memory limit is an integer, which sets maximum memory usage for a program in Mbytes"                                                       << endl <<
                                                                                                                                                               endl <<
                "For example, testing a program named \"prog.exe\" with a test archive \"prog_tests\" with time limit 1 second and memory limit 16 Mbytes:" << endl <<
                "testengine.exe prog.exe prog_tests 1 16"                                                                                                   << endl <<
                                                                                                                                                               endl <<
                "Each test set will be reported by one of the abbreviations:"                                                                               << endl;

        SetConsoleTextAttribute(hConsole, GREEN);
        cout << "OK";
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        cout << " - the test was passed successfully" << endl;

        SetConsoleTextAttribute(hConsole, RED);
        cout << "WA";
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        cout << " - program's output differs from the expected" << endl;

        SetConsoleTextAttribute(hConsole, RED);
        cout << "TL";
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        cout << " - program is working too long" << endl;

        SetConsoleTextAttribute(hConsole, RED);
        cout << "ML";
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        cout << " - program is using too much RAM" << endl;

        return 0;
    }

    if (argc <= 2)
    {
        cout << "No parameter <test-archive-path>. Type \"testengine.exe help\" for more instructions." << endl;
        return 0;
    }

    if (argc <= 3)
    {
        cout << "No parameter <time-limit>. Type \"testengine.exe help\" for more instructions." << endl;
        return 0;
    }

    if (argc <= 4)
    {
        cout << "No parameter <memory-limit>. Type \"testengine.exe help\" for more instructions." << endl;
        return 0;
    }

    string prog_path = argv[1];
    string test_archive_path = argv[2];
    double time_limit = atof(argv[3]);
    size_t mem_limit = atoi(argv[4]);
    time_limit *= 1000;
    mem_limit *= 1024;

    if (!str_endswith(prog_path, ".exe"))
    {
        cout << "First argument is not a path to program. Type \"testengine.exe help\" for more instructions." << endl;
        return 0;
    }

    if (mem_limit == 0)
    {
        cout << "Incorrect value for memory limit value. Type \"testengine.exe help\" for more instructions." << endl;
        return 0;
    }

    if (time_limit == 0)
    {
        cout << "Incorrect value for time limit value. Type \"testengine.exe help\" for more instructions." << endl;
        return 0;
    }

    ifstream open_test(prog_path);
    if (!open_test.is_open())
    {
        cout << "Incorrect path to program. Type \"testengine.exe help\" for more instructions." << endl;
        return 0;
    }
    open_test.close();

    string prog_name = split(prog_path, "/").back();

    size_t correct_test_counter = 0;
    size_t test_quantity = 0;
    for (int i = 1; true; ++i)
    {
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        string input_filename;
        ifstream open_test(test_archive_path+"/"+to_string(i));
        if (open_test.is_open())
            input_filename = to_string(i);
        else
        {
            open_test.open(test_archive_path+"/"+to_string(i)+".txt");
            if (open_test.is_open())
                input_filename = to_string(i)+".txt";
        }
        open_test.close();

        if (input_filename == "")
        {
            break;
        }
        ++test_quantity;
        string ans_filename;
        open_test.open(test_archive_path+"/"+to_string(i)+"_a");
        if (open_test.is_open())
            ans_filename = to_string(i)+"_a";
        else
        {
            open_test.open(test_archive_path+"/"+to_string(i)+"_a.txt");
            if (open_test.is_open())
                ans_filename = to_string(i)+"_a.txt";
        }
        open_test.close();

        if (ans_filename == "")
        {
            cout << "Expected output file for test #" << i << " not found, skipping test set" << endl;
            continue;
        }

        bool test_running = false;
        thread th(run_test, prog_path, test_archive_path, input_filename, ref(test_running));
        while (!test_running){}
        bool TL = false, ML = false;
        auto start_time = chrono::high_resolution_clock::now();
        while (!TL && !ML)
        {
            if (!test_running)
                break;
            if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() > time_limit)
            {
                TL = true;
                break;
            }
            if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() > 300)
            {
                PROCESS_MEMORY_COUNTERS pmc;
                GetProcessMemoryInfo(GetProcessByName(prog_name), &pmc, sizeof(pmc));
                double memory = static_cast<double>(pmc.WorkingSetSize) / 1024.0;
                if (memory > mem_limit)
                {
                    ML = true;
                    break;
                }
            }
        }
        chrono::duration<size_t, std::milli> execution_time = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time);

        if (TL)
            system(("taskkill /f /IM "+prog_name+" >NUL").c_str());

        th.join();

        system(("fc out.txt "+test_archive_path+"/"+ans_filename+" >NUL && echo OK >"+"comp.txt || echo WA >"+"comp.txt").c_str());
        ifstream fin("comp.txt");
        string comp;
        fin >> comp;
        fin.close();
        system("del /f comp.txt");
        system("del /f out.txt");

        cout << "Test #" << i << ": ";
        SetConsoleTextAttribute(hConsole, GREEN);

        if (TL)
        {
            SetConsoleTextAttribute(hConsole, RED);
            cout << "Time limit exceeded";
        }

        else if (ML)
        {
            SetConsoleTextAttribute(hConsole, RED);
            cout << "Memory limit exceeded";
        }

        else if (comp == "WA")
        {
            SetConsoleTextAttribute(hConsole, RED);
            cout << "Wrong answer";
        }
        else
        {
            cout << "OK";
            ++correct_test_counter;
        }
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        cout << " (execution time: " << execution_time.count() / 1000.0 << " seconds)" << endl;
    }
    if (test_quantity == 0)
    {
        cout << "Incorrect path to test archive. Type \"testengine.exe help\" for more instructions." << endl;
        return 0;
    }
    cout << "Passed " << correct_test_counter << " tests from " << test_quantity << " (" << floor(correct_test_counter / static_cast<double>(test_quantity) * 1000) / 10.0 << "% passed tests)" << endl;
    return 0;
}
