#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// ===================== Assignment Class =====================
class Assignment 
{
private:
    string name;
    string subject;
    string dueDate;
    int priority;
    bool completed;
    double grade;

public:
    Assignment() 
    {
        name = "";
        subject = "";
        dueDate = "";
        priority = 0;
        completed = false;
        grade = -1;
    }

    Assignment(string n, string s, string d, int p)
    {
        name = n;
        subject = s;
        dueDate = d;
        priority = p;
        completed = false;
        grade = -1;
    }

    void markComplete()
    {
        completed = true;
    }

    void setGrade(double g) 
    {
        grade = g;
    }

    string getName() { return name; }
    string getSubject() { return subject; }
    string getDueDate() { return dueDate; }
    int getPriority() { return priority; }
    bool isCompleted() { return completed; }
    double getGrade() { return grade; }

    void display(int index)
    {
        cout << "\n[" << index << "] "
            << name << " | " << subject
            << " | Due: " << dueDate
            << " | Priority: " << priority
            << " | Status: " << (completed ? "Done" : "Pending");

        if (grade >= 0)
            cout << " | Grade: " << grade;

        cout << endl;
    }

    // Save format
    string toFileString() 
    {
        return name + "," + subject + "," + dueDate + "," +
            to_string(priority) + "," +
            to_string(completed) + "," +
            to_string(grade);
    }

    // Load from file
    void fromFileString(string line) {
        int pos = 0;
        string token;

        vector<string> parts;

        while ((pos = line.find(',')) != string::npos) {
            token = line.substr(0, pos);
            parts.push_back(token);
            line.erase(0, pos + 1);
        }
        parts.push_back(line);

        name = parts[0];
        subject = parts[1];
        dueDate = parts[2];
        priority = stoi(parts[3]);
        completed = stoi(parts[4]);
        grade = stod(parts[5]);
    }
};

// ===================== Manager Class =====================
class Manager
{
private:
    vector<Assignment> assignments;

public:
    void addAssignment()
    {
        string name, subject, dueDate;
        int priority;

        cin.ignore();

        cout << "Enter assignment name: ";
        getline(cin, name);

        cout << "Enter subject: ";
        getline(cin, subject);

        cout << "Enter due date: ";
        getline(cin, dueDate);

        cout << "Enter priority (1-5): ";
        cin >> priority;

        assignments.push_back(Assignment(name, subject, dueDate, priority));

        cout << "Assignment added!\n";
    }

    void viewAssignments() 
    {
        if (assignments.empty()) {
            cout << "No assignments found.\n";
            return;
        }

        for (int i = 0; i < assignments.size(); i++) {
            assignments[i].display(i);
        }
    }

    void deleteAssignment() {
        int index;
        viewAssignments();

        cout << "\nEnter index to delete: ";
        cin >> index;

        if (index >= 0 && index < assignments.size()) {
            assignments.erase(assignments.begin() + index);
            cout << "Deleted successfully.\n";
        }
        else {
            cout << "Invalid index.\n";
        }
    }

    void markComplete() {
        int index;
        viewAssignments();

        cout << "\nEnter index to mark complete: ";
        cin >> index;

        if (index >= 0 && index < assignments.size()) {
            assignments[index].markComplete();

            double grade;
            cout << "Enter grade: ";
            cin >> grade;
            assignments[index].setGrade(grade);

            cout << "Marked complete!\n";
        }
        else
        {
            cout << "Invalid index.\n";
        }
    }

    void calculateGPA() {
        double total = 0;
        int count = 0;

        for (auto& a : assignments) {
            if (a.isCompleted() && a.getGrade() >= 0) {
                total += a.getGrade();
                count++;
            }
        }

        if (count == 0) {
            cout << "No graded assignments.\n";
            return;
        }

        cout << "Average GPA: " << (total / count) << endl;
    }

    void saveToFile() {
        ofstream file("assignments.txt");

        for (auto& a : assignments) {
            file << a.toFileString() << endl;
        }

        file.close();
        cout << "Data saved.\n";
    }

    void loadFromFile() {
        ifstream file("assignments.txt");

        if (!file) {
            cout << "No save file found.\n";
            return;
        }

        assignments.clear();
        string line;

        while (getline(file, line)) {
            Assignment a;
            a.fromFileString(line);
            assignments.push_back(a);
        }

        file.close();
        cout << "Data loaded.\n";
    }
};

// ===================== Main =====================
int main()
{
    Manager manager;
    int choice;

    do
    {
        cout << "\n===== Student Assignment Manager =====\n";
        cout << "1. Add Assignment\n";
        cout << "2. View Assignments\n";
        cout << "3. Delete Assignment\n";
        cout << "4. Mark Complete\n";
        cout << "5. Calculate GPA\n";
        cout << "6. Save Data\n";
        cout << "7. Load Data\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: manager.addAssignment(); break;
        case 2: manager.viewAssignments(); break;
        case 3: manager.deleteAssignment(); break;
        case 4: manager.markComplete(); break;
        case 5: manager.calculateGPA(); break;
        case 6: manager.saveToFile(); break;
        case 7: manager.loadFromFile(); break;
        case 0: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}