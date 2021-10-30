#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <unistd.h>
/**
 * problem with this approach is that alot of read & write required
 */
using namespace std;

class TodoApp {
public:
    TodoApp() : task(""),done(false),maxlen(1){}
    void addTask();
    void TaskList();
    void deleteTask();

private: 
    string task;
    int maxlen;
    char done;// vary from 0 to 1
};

void TodoApp::deleteTask() {

    TaskList();
    int number;

    cout << "\nEnter a task number , that you want to delete:\n";
    cin >> number;

    string s;
    vector<string> v;

    ifstream task_list;
    task_list.open("TODO.txt");

    while (getline(task_list, s)) {
        v.push_back(s);
    }

    task_list.close();
    if (number > v.size() || number < 1) {
        cout << "Task " << number << " does not exist!" << endl;
    }
    else {
        ofstream write;
        write.open("TODO.txt");
        for (int i = 0; i < v.size(); i++) {
            if (i != number - 1)
                write << v[i] << endl;
        }
        cout << "Deleted task " << number << endl;

        write.close();
    }
}

void TodoApp::TaskList() {
    /**
     * to display Task | Date | status
     */
    string s;
    vector<string> Task_List;

    ifstream readList;
    readList.open("TODO.txt");

    while (getline(readList, s)) {
        Task_List.push_back(s);
    }


    for (string s : Task_List) {
        int indx1;
        for(indx1=0; s[indx1]!=';'; indx1++);
        if(maxlen < indx1)
            maxlen = indx1;
    }

    readList.close();

    if (Task_List.size() == 0) {
        cout << "There are no pending task ✅👍\n";
    }
    else {
        cout << "YOUR PENDING TASKS \n";
        cout<<"+---------------------------------+\n";
        cout << "| ID |" << setw(maxlen) << " Task |" << setw(14) <<" Date | "<< setw(5) << "status |" << endl;
        for (int i = Task_List.size() - 1; i >= 0; i--) {
            s = Task_List.back();
            int indx1;
            for(indx1=0; s[indx1]!=';'; indx1++);
            int indx2;
            for(indx2=indx1+1; s[indx2]!=';'; indx2++);


            Task_List.pop_back();
            cout << "| " << setw(2) << (i + 1) << " |"
                 << " " << setw(maxlen) << s.substr(0,indx1) << " | " << setw(10) << s.substr(indx1+1, indx2-indx1-1) 
                 << " | " << setw(6) <<((s.at(s.length()-1) == '0') ? "❌" : "✅") << "  |" << endl;
        }
        cout<<"+---------------------------------+\n";
    }
}

void TodoApp::addTask() {
    string temp;
    cout << "Enter your task:\n";
    getline(cin >> ws, task); // extracts all white space characters after cin

    vector<string> tempStorage;

    ifstream read;
    read.open("TODO.txt");

    // loading the data from the TODO.txt into a vector<String> type var.
    while (getline(read, temp)) {
        tempStorage.push_back(temp);
    }

    read.close();


    // current date
    time_t now = time(0);
    tm *current_date = localtime(&now);

    string year, month, day;

    year = to_string((1900 + current_date->tm_year));
    month = to_string((1 + current_date->tm_mon));
    day = to_string(current_date->tm_mday);

    task += ";" ;

    /**
     * we could use ";" as a seperator
     * hide it from user
     */
    int indx1, indx2;// saving the last stored one index of ';'
    for(indx1=0; task.at(indx1)!=';'; indx1++);
    done = '0';

    for (int i = 0; i < tempStorage.size(); i++) {
        for(indx2=0; tempStorage[i].at(indx2)!=';'; indx2++);
        if ((task.substr(0,indx1)).compare(tempStorage[i].substr(0,indx2)) == 0) {
            done = '1';
            break;
        }
    }
    task += day + "-" + month + "-" + year + ";" + done ;


    if (done == '0') {
        fstream write;
        write.open("TODO.txt", ios::app);
        write << task << endl;
        cout << "Added Task : "
             << "\"" << task << "\"" << endl;
        write.close();
    } else {
        ofstream write;
        write.open("TODO.txt");

        for (int i = 0; i < tempStorage.size(); i++) {
            if ((task.substr(0,indx1)).compare(tempStorage[i].substr(0,indx2)) != 0) {
                write << tempStorage[i] << endl;
            }
        }

        write << task << endl;
        cout << "Added Task : "
             << "\"" << task<< "\"" << endl;
        write.close();
    }
}

void Appmanual() {
    cout << "\n\n\t+----------------+";
    cout << "\n\t|     MENU\t |";
    cout << "\n\t+----------------+";
    cout << "\n\t| 1. Add Task\t |";
    cout << "\n\t| 2. Delete Task |";
    cout << "\n\t| 3. See Tasks\t |";
    cout << "\n\t| 4. Exit\t |";
    cout << "\n\t+----------------+";
}
int main(int argc, char const *argv[]) {
    system("clear");
    TodoApp user;

    int ch;
    do {
        Appmanual();
        try {
            cout << "\n\nWhat is your Choice (1/2/3/4) ";
            cin >> ch;

            if (ch < 1 || ch > 4) {
                throw ch;
            }
        }
        catch (int ch) {
            cerr << "^~~~ Invalid Entry!\n";
            continue;
        }

        switch (ch) {
            case 1:
                user.addTask();
                break;
            case 2:
                user.deleteTask();
                break;
            case 3:
                user.TaskList();
                break;
        }

    } while (ch!=4);

    return 0;
}