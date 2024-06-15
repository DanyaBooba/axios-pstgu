bool strEqual(char from[], char to[], int len) {
	for(int i = 0; i < len; i++) if(from[i] != to[i]) return false;
	return true;
}

bool isSubStringNotNull(std::string str) {
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] != ' ' && str[i] != '\n') return true;
        i += 1;
    }
    return false;
}

int min(int a, int b) { if(a < b) return a; return b; }

int max(int a, int b) { if(a > b) return a; return b; }

int subStringStudentInfoValue(std::string str) {
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == '+') return 1;
        else if(str[i] == '-') return -1;
        i += 1;
    }

    return 0;
}

int getLengthStudentName(std::string name) {
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

void stringClearSpacesAround(std::string * str) {
    while(str->at(0) == ' ') {
        str->erase(0, 1);
    }

    while(str->at(str->size() - 1) == ' ') {
        str->erase(str->size() - 1, 1);
    }
}

void printSpacesOfUserLength(int currentLength) {
    int countSpaces = max(0, (MAX_LENGTH_STUDENT_NAME - currentLength));
    for(int i = 0; i < countSpaces; i++) {
        std::cout << " ";
    }
}

void printHelp() {
    printf("\n=-=-=-=-=-=-=- АКСИОС - ПРОГРАММА ДЛЯ ПРЕПОДАВАТЕЛЯ -=-=-=-=-=-=-=\n\nАксиос - программа, которая берет информацию из markdown таблицы,\nсохраняет задания, информацию о студенте и выводит ее на экран.\n\nЕсть возможность передать параметры:\n\n- [-p] <count> - задает \"верхнюю планку\"\n- <filename> - позволяет указать конкретный файл(-ы)\n  для данных (по умолчанию - \"data.txt\")\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-= АКСИОС =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
}

void printStudentInfoBlock(std::string text, int count, int procent) {
    std::cout << " [" << text << ":";
    printf("%3d", count);
    std::cout << ", ";
    printf("%3d%%", procent);
    std::cout << "] ";
}

void setValueCompleteTasks(std::vector<int> tasks, int * complete, int * completeAll) {
    for(int i = 0; i < tasks.size(); i++) {
        if(tasks[i] == 1 || tasks[i] == -1) *completeAll += 1;
        if(tasks[i] == 1) *complete += 1;
    }
}

void printStudentInfo(std::string studentName, std::vector<int> tasks) {
    int nameLengthStudent = getLengthStudentName(studentName);
    printSpacesOfUserLength(nameLengthStudent);

    std::cout << studentName << ": ";
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

    std::cout << std::endl;
}

void printAllStudents(std::vector<student> students) {
    int countTasks = students[0].tasks.size();
    std::cout << "Всего заданий: " << countTasks << std::endl;
    std::cout << "Верхняя планка: " << PROCENT_MAX_LIMIT << "%" << std::endl << std::endl;
    for(int i = 0; i < students.size(); i++) {
        student thisStudent = students[i];
        std::vector<int> tasksThisStudent = thisStudent.tasks;
        std::string nameThisStudent = thisStudent.name;
        printStudentInfo(nameThisStudent, tasksThisStudent);
    }
}

void printListTasks(std::vector<std::string> tasks) {
    int numberOfTask = 1;
    int tasksCount = tasks.size();
    for(int i = 0; i < tasksCount; i++) {
        if(tasksCount > 10 &&tasksCount < 100) printf("%2d", numberOfTask);
        else printf("%d", numberOfTask);
        std::cout << ". " << tasks[i] << std::endl;
        numberOfTask += 1;
    }
}
