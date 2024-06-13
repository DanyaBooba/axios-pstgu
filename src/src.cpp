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

bool strEqual(char from[], char to[], int len) {
	for(int i = 0; i < len; i++) if(from[i] != to[i]) return false;
	return true;
}

bool isSubStringNotNull(string str) {
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] != ' ' && str[i] != '\n') return true;
        i += 1;
    }
    return false;
}

int min(int a, int b) { if(a < b) return a; return b; }

int max(int a, int b) { if(a > b) return a; return b; }

int subStringStudentInfoValue(string str) {
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == '+') return 1;
        else if(str[i] == '-') return -1;
        i += 1;
    }

    return 0;
}

int getLengthStudentName(string name) {
    int i = 0;
    int count = 0;
    int fullCount = 0;
    while(name[i] != '\0') {
        if(name[i] == ' ') fullCount += 1;
        count += 1;
        i += 1;
    }
    return ((int) (count / 2)) + fullCount;
}

double setValueProcent(int A, int B) {
    return ((double) A / B) * 100;
}

void printSpacesOfUserLength(int currentLength) {
    int countSpaces = max(0, (MAX_LENGTH_STUDENT_NAME - currentLength));
    for(int i = 0; i < countSpaces; i++) {
        cout << " ";
    }
}

void stringClearSpacesAround(string * str) {
    while(str->at(0) == ' ') {
        str->erase(0, 1);
    }

    while(str->at(str->size() - 1) == ' ') {
        str->erase(str->size() - 1, 1);
    }
}

void printStudentInfoBlock(string text, int count, int procent) {
    cout << " [" << text << ":";
    printf("%3d", count);
    cout << ", ";
    printf("%3d%%", procent);
    cout << "] ";
}

void setValueCompleteTasks(vector<int> tasks, int * complete, int * completeAll) {
    for(int i = 0; i < tasks.size(); i++) {
        if(tasks[i] == 1 || tasks[i] == -1) *completeAll += 1;
        if(tasks[i] == 1) *complete += 1;
    }
}

void printStudentInfo(string studentName, vector<int> tasks) {
    int nameLengthStudent = getLengthStudentName(studentName);
    printSpacesOfUserLength(nameLengthStudent);

    cout << studentName << ": ";
    int countCompleteAll = 0;
    int countComplete = 0;
    int countTasks = tasks.size();
    setValueCompleteTasks(tasks, &countComplete, &countCompleteAll);

    double procentAll = setValueProcent(countCompleteAll, countTasks);
    double procent = setValueProcent(countComplete, countTasks);
    printf("%17s, ", (countCompleteAll == countTasks ? "допущен" : "не допущен"));
    if(countCompleteAll == countTasks) printf("%17s", (procent >= PROCENT_MAX_LIMIT ? "вовремя" : "не вовремя"));
    else printf("%10s", "");

    printStudentInfoBlock("вовремя", countComplete, (int) procent);
    printStudentInfoBlock("сдано всего", countCompleteAll, (int) procentAll);
    cout << endl;
}

void printAllStudents(vector<student> students) {
    int countTasks = students[0].tasks.size();
    cout << "Всего заданий: " << countTasks << endl;
    cout << "Верхняя планка: " << PROCENT_MAX_LIMIT << "%" << endl;
    for(int i = 0; i < students.size(); i++) {
        student thisStudent = students[i];
        vector<int> tasksThisStudent = thisStudent.tasks;
        string nameThisStudent = thisStudent.name;
        printStudentInfo(nameThisStudent, tasksThisStudent);
    }
}

void printListTasks(vector<string> tasks) {
    for(int i = 0; i < tasks.size(); i++) {
        cout << "- " << tasks[i] << endl;
    }
}

void printHelp() {
    printf("\n=-=-=-=-=-=-=- АКСИОС - ПРОГРАММА ДЛЯ ПРЕПОДАВАТЕЛЯ -=-=-=-=-=-=-=\n\nАксиос - программа, которая берет информацию из markdown таблицы,\nсохраняет задания, информацию о студенте и выводит ее на экран.\n\nЕсть возможность передать параметры:\n\n- [-p] <count> - задает \"верхнюю планку\"\n- <filename> - позволяет указать конкретный файл(-ы)\n  для данных (по умолчанию - \"data.txt\")\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-= АКСИОС =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
}

int main(int argc, char * argv[]) {
    string filename;
    vector<string> jobs;
    vector<student> allStudents;

    string line;
    int row = 0;
    size_t pos = 0;
    bool needHelp = false;

    for(int i = 0; i < argc; i++) {
        if(strEqual(argv[i], "-p", 2) && (i + 1) < argc) {
            PROCENT_MAX_LIMIT = min(max(atoi(argv[i+1]), 100), 0);
        }
        else {
            if(argc > 1 && i > 0) filename = argv[i];
            else if(argc <= 1) filename = "data.txt";
            if(filename == "") continue;

            ifstream file(filename);

            if (!file.is_open()) {
                cout << "Не удалось открыть файл " << filename << endl;
                needHelp = true;
                continue;
            }

            while (getline(file, line)) {
                string subString = line.substr(0, line.find(delimiter));
                bool thisSubStringIsName = true;
                bool isThisPersonStudent = false;
                string nameOfStudent;
                vector<int> localStudentTasks;
                while ((pos = line.find(delimiter)) != string::npos) {
                    subString = line.substr(0, pos);

                    if(row == 0 && isSubStringNotNull(subString)) {
                        //
                        // Названия заданий
                        //
                        stringClearSpacesAround(&subString);
                        bool jobAlreadyHasName = false;
                        for(int i = 0; i < jobs.size(); i++) if(jobs[i] == subString) jobAlreadyHasName = true;
                        if(jobAlreadyHasName == false) jobs.push_back(subString);
                    }
                    else if(row > 1) {
                        //
                        // Информация о учениках
                        //
                        if(thisSubStringIsName && isSubStringNotNull(subString)) {
                            stringClearSpacesAround(&subString);
                            isThisPersonStudent = (subString[0] != '@');
                            if(isThisPersonStudent) {
                                nameOfStudent = subString;
                                MAX_LENGTH_STUDENT_NAME = max(MAX_LENGTH_STUDENT_NAME, getLengthStudentName(nameOfStudent));
                            }
                            thisSubStringIsName = false;
                        }
                        else if(thisSubStringIsName == false && isThisPersonStudent) {
                            int studentInfo = subStringStudentInfoValue(subString);
                            localStudentTasks.push_back(studentInfo);
                        }
                    }
                    line.erase(0, pos + delimiter.length());
                }

                if(isThisPersonStudent) {
                    int indexStudentInVector = -1;
                    for(int i = 0; i < allStudents.size(); i++) {
                        student thisStudent = allStudents[i];
                        if(thisStudent.name == nameOfStudent) {
                            indexStudentInVector = i;
                            break;
                        }
                    }

                    if(indexStudentInVector == -1) {
                        student localStudent = {
                            nameOfStudent,
                            localStudentTasks
                        };

                        allStudents.push_back(localStudent);
                    }
                    else {
                        student localStudent = allStudents[indexStudentInVector];
                        vector<int> alreadyTasks = localStudent.tasks;
                        for(int i = 0; i < localStudentTasks.size(); i++) {
                            alreadyTasks.push_back(localStudentTasks[i]);
                        }
                        student newStudent = {
                            localStudent.name,
                            alreadyTasks
                        };

                        allStudents.at(indexStudentInVector) = newStudent;
                    }
                }

                isThisPersonStudent = false;
                row += 1;
            }

            file.close();
            row = 0;
        }
    }

    if(needHelp) printHelp();

    cout << "Задания: " << endl;
    printListTasks(jobs);

    cout << endl << "Результаты учеников: " << endl;
    printAllStudents(allStudents);

    return 0;
}
