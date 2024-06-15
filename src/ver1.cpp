#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int PROCENT_MAX_LIMIT = 80;
int MAX_LENGTH_STUDENT_NAME = 0;
const string delimiter = "|";

struct student {
    string name;
    vector<int> tasks;
};

#include "import.h"
#include "readfile.h"

int main(int argc, char * argv[]) {
    string filename;
    vector<string> jobs;
    vector<student> allStudents;
    bool needHelp = false;

    for(int i = 0; i < argc; i++) {
        if(strEqual(argv[i], "-p", 2) && (i + 1) < argc) {
            PROCENT_MAX_LIMIT = min(max(atoi(argv[i+1]), 100), 0);
        }
        else {
            if(argc > 1 && i > 0) { filename = argv[i]; }
            else if(argc <= 1)    { needHelp = true; continue; }
            if(filename == "")    { continue; }

            ifstream file(filename);

            if (!file.is_open()) { cout << "Не удалось открыть файл " << filename << endl; needHelp = true; continue; }

            readFile(file, allStudents, jobs);

            file.close();
        }
    }

    if(needHelp) {
        printHelp();
    }

    if(jobs.size() > 0) {
        cout << "Задания: " << endl;
        printListTasks(jobs);
    }

    if(allStudents.size() > 0) {
        cout << endl << "Результаты учеников: " << endl << endl;
        printAllStudents(allStudents);
    }

    return 0;
}
