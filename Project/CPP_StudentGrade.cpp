#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Structure to hold scores for each subject
struct SubjectScores {
    string name;
    char acronym; // M for Math, E for English, S for Science, F for Filipino
    vector<int> numItems; // Number of items for each quiz
    vector<double> quizzesScores;
    vector<int> numPerformanceTasks; // Number of performance tasks for each subject
    vector<double> performanceTaskScores;
    double attendanceScore;
    double examScore;
    double subjectGrade;
};

// Structure to hold student information and scores for multiple subjects
struct Student {
    string name;
    string section;
    vector<SubjectScores> subjects;
    double overallGrade;
};

class StudentDatabase {
private:
    vector<Student> students;

public:
    void addStudent(const string& name, const string& section) {
        students.push_back({name, section, {}, 0.0});
    }

    void removeStudent(size_t index) {
        if (index < students.size()) {
            students.erase(students.begin() + index);
            cout << "STUDENT REMOVED SUCCESSFULLY...\n";
        } else {
            cout << "INVALID INDEX.\n";
        }
    }

    void displayStudents() const {
        if (students.empty()) {
            cout << "UNAVAILABLE!.\n";
            return;
        }

        cout << left << setw(10) << "Index" << setw(15) << "Name" << setw(15) << "Section" << endl;
        cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;

        for (size_t i = 0; i < students.size(); ++i) {
            cout << setw(10) << i << setw(15) << students[i].name << setw(10) << students[i].section << endl;
        }
    }

    void addSubjectsAndScores(size_t studentIndex) {
        if (studentIndex < students.size()) {
            Student& student = students[studentIndex];

            cout << "ENTER DETAILS FOR STUDENT " << student.name << " (" << student.section << "):\n";

            while (true) {
                cout << "\nChoose a subject to add scores:";
                cout << "1. Math (M)\n";
                cout << "2. English (E)\n";
                cout << "3. Science (S)\n";
                cout << "4. Filipino (F)\n";
                cout << "5. Exit to main menu\n";
                cout << "Enter your choice (1-5): ";

                int subjectChoice;
                cin >> subjectChoice;

                if (subjectChoice == 5) {
                    break; // Exit to main menu
                }

                if (subjectChoice >= 1 && subjectChoice <= 4) {
                    SubjectScores subject;
                    switch (subjectChoice) {
                        case 1:
                            subject.acronym = 'M';
                            subject.name = "Math";
                            break;
                        case 2:
                            subject.acronym = 'E';
                            subject.name = "English";
                            break;
                        case 3:
                            subject.acronym = 'S';
                            subject.name = "Science";
                            break;
                        case 4:
                            subject.acronym = 'F';
                            subject.name = "Filipino";
                            break;
                    }

                    // Quizzes
                    cout << "Enter the total number of quizzes for " << subject.name << ": ";
                    int numQuizzes;
                    cin >> numQuizzes;

                    subject.numItems.resize(numQuizzes);
                    subject.quizzesScores.resize(numQuizzes);

                    for (int i = 0; i < numQuizzes; ++i) {
                        cout << "Enter the total number of items for Quiz " << i + 1 << ": ";
                        cin >> subject.numItems[i];

                        cout << "Enter score for Quiz " << i + 1 << ": ";
                        cin >> subject.quizzesScores[i];

                        // Check if the entered score is valid
                        while (subject.quizzesScores[i] < 0 || subject.quizzesScores[i] > subject.numItems[i]) {
                            cout << "Invalid score. Enter a score between 0 and " << subject.numItems[i] << ": ";
                            cin >> subject.quizzesScores[i];
                        }
                    }

                    // Performance Tasks
                    cout << "Enter the total number of performance tasks for " << subject.name << ": ";
                    int numPerformanceTasks;
                    cin >> numPerformanceTasks;

                    subject.numPerformanceTasks.resize(numPerformanceTasks);
                    subject.performanceTaskScores.resize(numPerformanceTasks);

                    for (int i = 0; i < numPerformanceTasks; ++i) {
                        cout << "Enter the total number of items for Performance Task " << i + 1 << ": ";
                        cin >> subject.numPerformanceTasks[i];

                        cout << "Enter score for Performance Task " << i + 1 << ": ";
                        cin >> subject.performanceTaskScores[i];

                        // Check if the entered score is valid
                        while (subject.performanceTaskScores[i] < 0 || subject.performanceTaskScores[i] > subject.numPerformanceTasks[i]) {
                            cout << "Invalid score. Enter a score between 0 and " << subject.numPerformanceTasks[i] << ": ";
                            cin >> subject.performanceTaskScores[i];
                        }
                    }
                    
                    // Exam
                    double examMaxScore;
                    cout << "Enter the total points for Exam for " << subject.name << ": ";
                    cin >> examMaxScore;

                    cout << "Enter score for Exam for " << subject.name << ": ";
                    cin >> subject.examScore;

                    // Check if the entered score is valid
                    while (subject.examScore < 0 || subject.examScore > examMaxScore) {
                    cout << "Invalid score. Enter a score between 0 and " << examMaxScore << ": ";
                    cin >> subject.examScore;
                    }

                    // Attendance
                    double attendanceMaxScore;
                    cout << "Enter the total points for Attendance for " << subject.name << ": ";
                    cin >> attendanceMaxScore;

                    cout << "Enter score for Attendance for " << subject.name << ": ";
                    cin >> subject.attendanceScore;

                    // Check if the entered score is valid
                    while (subject.attendanceScore < 0 || subject.attendanceScore > attendanceMaxScore) {
                    cout << "Invalid score. Enter a score between 0 and " << attendanceMaxScore << ": ";
                    cin >> subject.attendanceScore;
                    }

                    student.subjects.push_back(subject);
                    cout << "SCORES ADDED SUCCESSFULLY FOR " << student.name << "'s " << subject.name << "!\n";

                    // Ask if they want to add more subjects
                    cout << "Do you want to add more subjects? (1 for YES and 2 for NO): ";
                    int choice;
                    cin >> choice;

                    if (choice == 2) {
                        break; // Exit to main menu
                    }
                } else {
                    cout << "INVALID SUBJECT CHOICE!\n";
                }
            }
        } else {
            cout << "INVALID STUDENT INDEX!\n";
        }
    }

    void calculateOverallGrades() {
        for (auto& student : students) {
            double totalOverallGrade = 0.0;

            for (auto& subject : student.subjects) {
                double totalMaxScore = 0.0;
                double totalStudentScore = 0.0;

                for (int i = 0; i < subject.numItems.size(); ++i) {
                    totalMaxScore += subject.numItems[i];
                    totalStudentScore += subject.quizzesScores[i];
                }

                for (int i = 0; i < subject.numPerformanceTasks.size(); ++i) {
                    totalMaxScore += subject.numPerformanceTasks[i];
                    totalStudentScore += subject.performanceTaskScores[i];
                }

                // Maximum possible points for each component
                const double maxExamScore = 100.0;
                const double maxAttendanceScore = 10.0;

                // Weights for each component
                const double quizzesWeight = 0.2; // 20%
                const double performanceTasksWeight = 0.4; // 40%
                const double examWeight = 0.3; // 30%
                const double attendanceWeight = 0.1; // 10%

                // Calculate normalized scores
                double normalizedQuizzesScore = (totalStudentScore / totalMaxScore) * 100.0;
                double normalizedExamScore = (subject.examScore / maxExamScore) * 100.0;
                double normalizedAttendanceScore = (subject.attendanceScore / maxAttendanceScore) * 100.0;

                // Calculate subject grade
                subject.subjectGrade = (normalizedQuizzesScore * quizzesWeight) +
                                       (normalizedExamScore * examWeight) +
                                       (normalizedAttendanceScore * attendanceWeight);

                totalOverallGrade += subject.subjectGrade;
            }

            // Calculate overall grade for the student
            student.overallGrade = totalOverallGrade / student.subjects.size();
        }
    }

    void displayOverallGrades() const {
        if (students.empty()) {
            cout << "UNAVAILABLE!\n";
            return;
        }

        cout << left << setw(20) << "NAME" << setw(15) << "SECTION";

        for (char subjectAcronym : {'M', 'E', 'S', 'F'}) {
            cout << setw(15) << subjectAcronym;
        }

        cout << setw(15) << "AVERAGE GRADE" << endl;

        cout << setfill('-') << setw(70) << "" << setfill(' ') << endl;

        for (const auto& student : students) {
            cout << setw(20) << student.name << setw(15) << student.section;
            

            for (char subjectAcronym : {'M', 'E', 'S', 'F'}) {
                auto subjectIt = find_if(student.subjects.begin(), student.subjects.end(), [subjectAcronym](const SubjectScores& subject) {
                    return subject.acronym == subjectAcronym;
                });

                if (subjectIt != student.subjects.end()) {
                    cout << setw(15) << fixed << setprecision(2) << subjectIt->subjectGrade;
                } else {
                    cout << setw(15) << "N/A";
                }
            }

            cout << setw(15) << fixed << setprecision(2) << student.overallGrade << endl;
        }
    }

    void displayFinalAverage() const {
        if (students.empty()) {
            cout << "UNAVAILABLE!\n";
            return;
        }

        cout << left << setw(20) << "NAME" << setw(15) << "SECTION" << setw(15) << "FINAL AVERAGE GRADE" << endl;
        cout << setfill('-') << setw(50) << "" << setfill(' ') << endl;

        for (const auto& student : students) {
            double finalAverage = accumulate(student.subjects.begin(), student.subjects.end(), 0.0,
                                            [](double total, const SubjectScores& subject) {
                                                return total + subject.subjectGrade;
                                            }) / student.subjects.size();

            cout << setw(20) << student.name << setw(15) << student.section << setw(15) << fixed << setprecision(2) << finalAverage << endl;
        }
    }

    void displayRanks() const {
        if (students.empty()) {
            cout << "UNAVAILABLE!\n";
            return;
        }

        vector<pair<string, double>> studentAverages;

        for (const auto& student : students) {
            studentAverages.push_back({student.name, student.overallGrade});
        }

        sort(studentAverages.begin(), studentAverages.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        cout << "\nRANKS:\n";
        for (size_t i = 0; i < studentAverages.size(); ++i) {
            cout << "Rank " << i + 1 << ": " << studentAverages[i].first << "==" << fixed << setprecision(2) << studentAverages[i].second << endl;
        }
    }

};


int main() {
    StudentDatabase database;

    while (true) {
        // Display options
        int option;
        cout << "\n";
        cout << setfill('-') << setw(70) << "" << setfill(' ') << endl;
        cout << "\nOptions:\n";
        cout << "1. Add students\n";
        cout << "2. Remove students\n";
        cout << "3. View list of students\n";
        cout << "4. Choose subjects and scores\n";
        cout << "5. Display overall grades\n";
        cout << "6. Display final average\n";
        cout << "7. Display ranks\n";
        cout << "8. Exit\n";
        cout << "Enter your choice (1-8): ";
        cin >> option;

        system("cls"); // Clear the console

        switch (option) {
            case 1:
                // Add students
                {
                    int numStudents;
                    cout << "ENTER THE NUMBER OF STUDENTS TO ADD: ";
                    cin >> numStudents;

                    for (int i = 0; i < numStudents; ++i) {
                        string name;
                        string section;
                        cout << "\nEnter details for student " << i + 1 << ":\n";
                        cout << "Name: ";
                        cin.ignore();
                        getline(cin, name);

                        cout << "Section: ";
                        cin >> section;

                        database.addStudent(name, section);
                    }
                    cout << "\nSTUDENTS ADDED SUCCESSFULLY!\n";
                }
                break;

            case 2:
                // Remove students
                {
                    cout << "Enter the index of the student to remove:\n";
                    database.displayStudents();

                    size_t index;
                    cin >> index;

                    database.removeStudent(index);
                }
                break;

            case 3:
                // View list of students
                database.displayStudents();
                break;

            case 4:
                // Choose subjects and scores
                {
                    cout << "CHOOSE WHICH STUDENT:\n";
                    database.displayStudents();

                    size_t studentIndex;
                    cin >> studentIndex;

                    database.addSubjectsAndScores(studentIndex);
                }
                break;

            case 5:
                // Display overall grades
                database.calculateOverallGrades();
                database.displayOverallGrades();
                break;

            case 6:
                // Display final average
                database.calculateOverallGrades();
                database.displayFinalAverage();
                break;

            case 7:
                // Display ranks
                database.calculateOverallGrades();
                database.displayRanks();
                break;

            case 8:
                // Exit
                cout << "PROGRAM EXITING, THANK YOU GUYS AND FAREWELL!\n";
                return 0;

            default:
                cout << "INVALID OPTION PLS CHOOSE FROM THE OPTIONS...\n";
        }

        // Prompt for another action
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        system("cls"); // Clear the console
    }

    return 0;
}
    