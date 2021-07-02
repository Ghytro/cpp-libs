#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <chrono>
#include <windows.h>
#include <QtCore/QProcess>

std::vector<std::string> split(const std::string &str, const std::string &delimiter)
{
    std::vector<std::string> ans;
    auto p = str.find(delimiter);
    auto p1 = 0;
    while (p != std::string::npos)
    {
        ans.push_back(str.substr(p1, p - p1));
        p1 = p + delimiter.length();
        p = str.find(delimiter, p + delimiter.length());
    }
    ans.push_back(str.substr(p1, str.length() - p1));
    return ans;
}

bool str_endswith(const std::string &str, const std::string &_end)
{
    for (int i = _end.length() - 1, j = str.length() - 1; i >= 0; --i, --j)
    {
        if (_end[i] != str[j])
            return false;
    }
    return true;
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
        std::cout << "Console applications testing service TestEngine."                                                                                          << std::endl <<
                "Created by Michael Korobkov (c) 2020. All rights reserved"                                                                                 << std::endl <<
                                                                                                                                                               std::endl <<
                "To test the .exe console application you need to specify a path for .exe file, path for the test archive and time and memory limits."      << std::endl <<
                "The applications output should not be redirected to the file, all the output you want to test must be on the screen"                       << std::endl <<
                "Test archive is a folder with files for the program input and it's expected output."                                                       << std::endl <<
                "There should be 2 files for each test set, one with the input data, the other with the expected output"                                    << std::endl <<
                "For example, file name with input data for test set #1 should be \"1\" or \"1.txt\" with no quotes."                                       << std::endl <<
                "The file with the expected output for this test set should be named \"1_a\" or \"1_a.txt\" with no quotes"                                 << std::endl <<
                "Time limit is a real number, which sets maximum execution time for a program in seconds"                                                   << std::endl <<
                "Memory limit is an integer, which sets maximum memory usage for a program in Mbytes"                                                       << std::endl <<
                                                                                                                                                               std::endl <<
                "For example, testing a program named \"prog.exe\" with a test archive \"prog_tests\" with time limit 1 second and memory limit 16 Mbytes:" << std::endl <<
                "testengine.exe prog.exe prog_tests 1 16"                                                                                                   << std::endl <<
                                                                                                                                                               std::endl <<
                "Each test set will be reported by one of the abbreviations:"                                                                               << std::endl;

        SetConsoleTextAttribute(hConsole, GREEN);
        std::cout << "OK";
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        std::cout << " - the test was passed successfully" << std::endl;

        SetConsoleTextAttribute(hConsole, RED);
        std::cout << "WA";
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        std::cout << " - program's output differs from the expected" << std::endl;

        SetConsoleTextAttribute(hConsole, RED);
        std::cout << "TL";
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        std::cout << " - program is working too long" << std::endl;

        SetConsoleTextAttribute(hConsole, RED);
        std::cout << "ML";
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        std::cout << " - program is using too much RAM" << std::endl;

        return 0;
    }

    if (argc <= 2)
    {
        std::cout << "No parameter <test-archive-path>. Type \"testengine.exe help\" for more instructions." << std::endl;
        return 0;
    }

    if (argc <= 3)
    {
        std::cout << "No parameter <time-limit>. Type \"testengine.exe help\" for more instructions." << std::endl;
        return 0;
    }

    if (argc <= 4)
    {
        std::cout << "No parameter <memory-limit>. Type \"testengine.exe help\" for more instructions." << std::endl;
        return 0;
    }

    std::string prog_path(argv[1]);
    std::string test_archive_path(argv[2]);
    double time_limit = atof(argv[3]);
    size_t mem_limit = atoi(argv[4]);
    time_limit *= 1000;
    mem_limit *= 1024;

    if (!str_endswith(prog_path, ".exe"))
    {
        std::cout << "First argument is not a path to program. Type \"testengine.exe help\" for more instructions." << std::endl;
        return 0;
    }

    if (mem_limit == 0)
    {
        std::cout << "Incorrect value for memory limit value. Type \"testengine.exe help\" for more instructions." << std::endl;
        return 0;
    }

    if (time_limit == 0)
    {
        std::cout << "Incorrect value for time limit value. Type \"testengine.exe help\" for more instructions." << std::endl;
        return 0;
    }

    std::ifstream open_test(prog_path);
    if (!open_test.is_open())
    {
        std::cout << "Incorrect path to program. Type \"testengine.exe help\" for more instructions." << std::endl;
        return 0;
    }
    open_test.close();

    std::string prog_name = split(prog_path, "/").back();

    size_t correct_test_counter = 0;
    size_t test_quantity = 0;
    for (int i = 1; true; ++i)
    {
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        std::string input_filename;
        std::ifstream open_test(test_archive_path+"/"+std::to_string(i));
        if (open_test.is_open())
            input_filename = std::to_string(i);
        else
        {
            open_test.open(test_archive_path+"/"+std::to_string(i)+".txt");
            if (open_test.is_open())
                input_filename = std::to_string(i)+".txt";
        }
        open_test.close();

        if (input_filename == "")
        {
            break;
        }
        ++test_quantity;
        std::string ans_filename;
        open_test.open(test_archive_path+"/"+std::to_string(i)+"_a");
        if (open_test.is_open())
            ans_filename = std::to_string(i)+"_a";
        else
        {
            open_test.open(test_archive_path+"/"+std::to_string(i)+"_a.txt");
            if (open_test.is_open())
                ans_filename = std::to_string(i)+"_a.txt";
        }
        open_test.close();

        if (ans_filename == "")
        {
            std::cout << "Expected output file for test #" << i << " not found, skipping test set" << std::endl;
            continue;
        }
        QProcess process;
        process.setProgram(QString(prog_path.c_str()));
        process.setStandardInputFile(QString((test_archive_path+"/"+input_filename).c_str()));
        process.setStandardOutputFile(QString("out.txt"));
        process.start();
        process.waitForStarted();
        auto start_time = std::chrono::high_resolution_clock::now();
        bool TL = !process.waitForFinished(static_cast<int>(time_limit));
        std::chrono::duration<size_t, std::milli> execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time);
        std::cout << "Test #" << i << ": ";
        SetConsoleTextAttribute(hConsole, RED);
        if (TL)
        {
            std::cout << "TL";
        }
        else if (process.exitCode() != 0)
        {
            std::cout << "RE";
        }
        else
        {
            system(("fc out.txt "+test_archive_path+"/"+ans_filename+" >NUL && echo OK >"+"comp.txt || echo WA >"+"comp.txt").c_str());
            std::ifstream fin("comp.txt");
            std::string comp;
            fin >> comp;
            fin.close();
            system("del /f comp.txt");
            system("del /f out.txt");
            if (comp == "WA")
            {
                std::cout << "WA";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, GREEN);
                std::cout << "OK";
                ++correct_test_counter;
            }
        }
        SetConsoleTextAttribute(hConsole, defaultTextAttribute);
        std::cout << " (execution time: " << execution_time.count() / 1000.0 << " seconds)" << std::endl;
        process.close();
    }
    if (test_quantity == 0)
    {
        std::cout << "Incorrect path to test archive. Type \"testengine.exe help\" for more instructions." << std::endl;
        return 0;
    }
    std::cout << "Passed " << correct_test_counter << " tests from " << test_quantity << " (" << std::floor(correct_test_counter / static_cast<double>(test_quantity) * 1000) / 10.0 << "% passed tests)" << std::endl;
    return 0;
}
