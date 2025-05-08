#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>

using namespace std;

class Employee
{
public:
    string name;
    string designation;
    int punctuality;
    int taskCompletion;
    int teamwork;
    int innovation;
    int communication;
    string feedback;
    int daysAbsent;
    int daysOnLeave;
    int totalWorkingDays;

    Employee(string n, string desig, int punc, int task, int team, int innov, int comm, string f = "", int a = 0, int l = 0, int twd = 0)
        : name(n), punctuality(punc), taskCompletion(task), teamwork(team),
          innovation(innov), communication(comm), feedback(f), daysAbsent(a), daysOnLeave(l), totalWorkingDays(twd) {}

    float getPerformanceScore() const
    {
        float total = punctuality + taskCompletion + teamwork + innovation + communication;
        return total / 5.0f;
    }

    string getPerformanceLevel() const
    {
        float score = getPerformanceScore();
        if (score < 4)
            return "poor";
        else if (score < 6.5)
            return "average";
        else if (score < 8.5)
            return "good";
        else
            return "excellent";
    }

    float getAttendancePercentage() const
    {
        if (totalWorkingDays == 0)
            return 0;
        int attended = totalWorkingDays - daysAbsent - daysOnLeave;
        return (attended * 100.0f) / totalWorkingDays;
    }

    string getAttendanceGrade() const
    {
        float perc = getAttendancePercentage();
        if (perc < 60)
            return "poor";
        else if (perc < 75)
            return "average";
        else if (perc < 90)
            return "good";
        else
            return "excellent";
    }
};

vector<Employee> employees;

map<string, string> knowledgeBase = {
    {"poor", "Provide training and mentorship."},
    {"average", "Set clear goals and expectations."},
    {"good", "Recognize and reward achievements."},
    {"excellent", "Promote and provide growth opportunities."}};

void evaluatePerformance()
{
    string name, designation, feedback;
    int punc, task, team, innov, comm, totalDays;

    cout << "Enter the employee's name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter the employee's designation (HR, Manager, Employee, Accountancy): ";
    getline(cin, designation);

    cout << "Rate the following from 1 to 10:\n";
    cout << "Punctuality: ";
    cin >> punc;
    cout << "Task Completion: ";
    cin >> task;
    cout << "Teamwork: ";
    cin >> team;
    cout << "Innovation: ";
    cin >> innov;
    cout << "Communication: ";
    cin >> comm;
    cout << "Enter total working days for this period: ";
    cin >> totalDays;

    // Role-specific questions
    if (designation == "HR") {
        int conflictResolution, recruitmentSkills;
        cout << "Rate Conflict Resolution skills (1 to 10): ";
        cin >> conflictResolution;
        cout << "Rate Recruitment and Staffing skills (1 to 10): ";
        cin >> recruitmentSkills;
    } else if (designation == "Manager") {
        int leadershipSkills, decisionMaking;
        cout << "Rate Leadership skills (1 to 10): ";
        cin >> leadershipSkills;
        cout << "Rate Decision Making ability (1 to 10): ";
        cin >> decisionMaking;
    } else if (designation == "Accountancy") {
        int financialAccuracy, budgetManagement;
        cout << "Rate Financial Accuracy (1 to 10): ";
        cin >> financialAccuracy;
        cout << "Rate Budget Management skills (1 to 10): ";
        cin >> budgetManagement;
    } else if (designation == "Employee") {
        int workEthic, taskManagement;
        cout << "Rate Work Ethic (1 to 10): ";
        cin >> workEthic;
        cout << "Rate Task Management skills (1 to 10): ";
        cin >> taskManagement;
    }

    cout << "Enter any additional feedback: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, feedback);

    employees.push_back(Employee(name, designation, punc, task, team, innov, comm, feedback, 0, 0, totalDays));
    cout << "Performance evaluation completed.\n";
}



void displayFeedback()
{
    if (employees.empty())
    {
        cout << "No performance evaluations available.\n";
        return;
    }
   



    cout << "\nEmployee Performance Feedback:\n";
    for (const Employee &e : employees)
    {
        cout << "\nName: " << e.name << "\n";
        cout << "Designation: " << e.designation << "\n";
        cout << "Performance Score: " << e.getPerformanceScore() << " (" << e.getPerformanceLevel() << ")\n";
        cout << "Punctuality: " << e.punctuality << "\n";
        cout << "Task Completion: " << e.taskCompletion << "\n";
        cout << "Teamwork: " << e.teamwork << "\n";
        cout << "Innovation: " << e.innovation << "\n";
        cout << "Communication: " << e.communication << "\n";
        cout << "Feedback: " << e.feedback << "\n";
        cout << "Days Absent: " << e.daysAbsent << "\n";
        cout << "Days on Leave: " << e.daysOnLeave << "\n";
        cout << "Total Working Days: " << e.totalWorkingDays << "\n";
        cout << "Attendance Percentage: " << e.getAttendancePercentage() << "% (" << e.getAttendanceGrade() << ")\n";
        cout << "Suggested Action: " << knowledgeBase[e.getPerformanceLevel()] << "\n";
    }
}

void addAbsenteeOrLeaveRecord()
{
    string name;
    cout << "Enter the employee's name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    bool found = false;
    for (Employee &e : employees)
    {
        if (e.name == name)
        {
            found = true;
            int absent, leave;
            cout << "Enter number of days absent: ";
            cin >> absent;
            cout << "Enter number of days on leave: ";
            cin >> leave;

            e.daysAbsent += absent;
            e.daysOnLeave += leave;

            cout << "Absentee/Leave record updated.\n";
            break;
        }
    }

    if (!found)
    {
        cout << "Employee not found.\n";
    }
}

int main()
{
    int choice;
    while (true)
    {
        cout << "\nEmployee Performance Evaluation System\n";
        cout << "1. Evaluate Performance\n";
        cout << "2. Display Feedback\n";
        cout << "3. Exit\n";
        cout << "4. Add Absentee/Leave Record\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            evaluatePerformance();
            break;
        case 2:
            displayFeedback();
            break;
        case 3:
            cout << "Exiting the program.\n";
            return 0;
        case 4:
            addAbsenteeOrLeaveRecord();
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}

