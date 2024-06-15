void readFile(ifstream &file, vector<student> & allStudents, vector<string> & jobs) {
    int row = 0;
    string line;
    size_t pos = 0;
    int countLocalTasks = 0;

    while (getline(file, line)) {
        vector<int> localStudentTasks;
        string nameOfStudent;

        bool thisSubStringIsName = true;
        bool isThisPersonStudent = false;

        int indexTaskLocalStudent = 0;

        pos = line.find(delimiter);
        string subString = line.substr(0, line.find(delimiter));
        if(pos == string::npos) {
            row = -1;
            countLocalTasks = 0;
        }

        while (pos != string::npos) {
            pos = line.find(delimiter);
            subString = line.substr(0, pos);

            if(row == 0 && isSubStringNotNull(subString)) {

                //
                // Названия заданий
                //

                stringClearSpacesAround(&subString);
                jobs.push_back(subString);
                countLocalTasks += 1;
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
                    if(indexTaskLocalStudent != countLocalTasks) localStudentTasks.push_back(studentInfo);
                    indexTaskLocalStudent += 1;
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
}
