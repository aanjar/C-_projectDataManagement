#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int getPositive() {
    int input;
    cin >> input;
    while (input < 0) {
        cout << "Invalid input. Please enter a positive number: ";
        cin >> input;
    }
    return input;
}

void addProject(string*& Name, int*& cost, int*& workers, int& p_exist, int p_add) {
    string* newName = new string[p_exist + p_add];
    int* newCost = new int[p_exist + p_add];
    int* newWorkers = new int[p_exist + p_add];

    for (int i = 0; i < p_exist; ++i) {
        newName[i] = Name[i];
        newCost[i] = cost[i];
        newWorkers[i] = workers[i];
    }

    for (int i = p_exist; i < p_exist + p_add; ++i) {
        cout << "Project " << i + 1 << " Name: ";
        cin.ignore();
        getline(cin, newName[i]);
        cout << "Project Budget: Rp. ";
        newCost[i] = getPositive();  

        cout << "Number of Workers: ";
        newWorkers[i] = getPositive();  
    }

    delete[] Name;
    delete[] cost;
    delete[] workers;

    Name = newName;
    cost = newCost;
    workers = newWorkers;

    p_exist += p_add;
    cout << p_add << " projects successfully added.\n";
}

void deleteProject(string*& Name, int*& cost, int*& workers, int& p_exist, int index) {
    if (index < 0 || index >= p_exist) {
        cout << "Invalid project index." << endl;
        return;
    }

    for (int i = index; i < p_exist - 1; ++i) {
        Name[i] = Name[i + 1];
        cost[i] = cost[i + 1];
        workers[i] = workers[i + 1];
    }

    string* newName = new string[p_exist - 1];
    int* newCost = new int[p_exist - 1];
    int* newWorkers = new int[p_exist - 1];

    for (int i = 0; i < p_exist - 1; ++i) {
        newName[i] = Name[i];
        newCost[i] = cost[i];
        newWorkers[i] = workers[i];
    }

    delete[] Name;
    delete[] cost;
    delete[] workers;

    Name = newName;
    cost = newCost;
    workers = newWorkers;

    p_exist--;
    cout << "Project successfully deleted." << endl;
}

void displayProjects(string* Name, int* cost, int* workers, int p_exist) {
    if (p_exist == 0) {
        cout << "No projects available.\n";
    } else {
        cout << setw(5) << left << "No."
            << setw(17) << left << "Name"
            << setw(10) << left << "Cost"
            << setw(10) << left << "Workers" << endl;
        cout << setfill('-') << setw(40) << '-' << endl;
        cout << setfill(' ');
        for (int i = 0; i < p_exist; i++) {
            cout << setw(5) << left << i + 1
            << setw(17) << left << Name[i]
            << setw(2) << left << "Rp " << setw(8) << cost[i]
            << setw(10) << left << workers[i] << endl;
        }
        cout << endl;
    }
}

void calculateTotalBudget(int* cost, int p_exist) {
    int totalBudget = 0;
    for (int i = 0; i < p_exist; ++i) {
        totalBudget += cost[i];
    }
    cout << "\nTotal Budget for All Projects: Rp. " << totalBudget << endl;
}

void calculateAverageWorkers(int* workers, int p_exist) {
    if (p_exist == 0) {
        cout << "\nNo projects to calculate average workers." << endl;
        return;
    }
    int totalWorkers = 0;
    for (int i = 0; i < p_exist; ++i) {
        totalWorkers += workers[i];
    }
    int averageWorkers = (int)totalWorkers / p_exist;
    cout << "\nAverage Number of Workers Per Project: " << averageWorkers << " people." << endl;
}

void largestBudgetProject(int* cost, string* Name, int p_exist) {
    if (p_exist == 0) {
        cout << "\nNo projects to find the largest budget." << endl;
        return;
    }

    int valueMax = 0;
    for (int i = 1; i < p_exist; ++i) {
        if (cost[i] > cost[valueMax]) {
            valueMax = i;
        }
    }

    cout << "\nProject with the Largest Budget: " << Name[valueMax] << ", Budget: Rp. " << cost[valueMax] << endl;
}

int main() {
    int p_exist = 0;

    cout << endl;
    cout << setfill('=') << setw(40) << '=' << endl;
    cout << setfill(' ');
    cout << "-------- PROJECT DATA MANAGEMENT -------"<< endl;
    cout << setfill('=') << setw(40) << '=' << endl;
    cout << setfill(' ');

    string* Name = nullptr;
    int* cost = nullptr;
    int* workers = nullptr;

    int choice;

    do {
        cout << endl;
        cout << setfill('=') << setw(40) << '=' << endl;
        cout << setfill(' ');
        cout << "----------------- MENU -----------------"<< endl;
        cout << setfill('=') << setw(40) << '=' << endl;
        cout << setfill(' ');

        cout << "1. Add Project\n";
        cout << "2. Delete Project\n";
        cout << "3. Display Project Data\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cout << setfill('-') << setw(40) << '-' << endl;
        cout << setfill(' ');

        switch (choice) {
            case 1: {
                cout << setfill('=') << setw(40) << '=' << endl;
                cout << setfill(' ');
                cout << "-------------- ADD PROJECT -------------"<< endl;
                cout << setfill('=') << setw(40) << '=' << endl;
                cout << setfill(' ');

                int p_add;
                cout << "Enter number of projects to be added: ";
                cin >> p_add;
                if (p_add <= 0) {
                    cout << "The number of projects to be added must be greater than 0.\n";
                    break;
                }
                addProject(Name, cost, workers, p_exist, p_add);
                break;
            }
            case 2: {
                cout << setfill('=') << setw(40) << '=' << endl;
                cout << setfill(' ');
                cout << "---------------- DELETE ----------------"<< endl;
                cout << setfill('=') << setw(40) << '=' << endl;
                cout << setfill(' ');

                if (p_exist == 0) {
                    cout << "No projects to delete.\n";
                    break;
                }

                displayProjects(Name, cost, workers, p_exist);

                int projectNumber;
                cout << "Enter the project number to delete (1 - " << p_exist << "): ";
                cin >> projectNumber;

                deleteProject(Name, cost, workers, p_exist, projectNumber - 1);
                break;
            }
            case 3: {
                cout << setfill('=') << setw(40) << '=' << endl;
                cout << setfill(' ');
                cout << "--------- DISPLAY PROJECT DATA ---------"<< endl;
                cout << setfill('=') << setw(40) << '=' << endl;
                cout << setfill(' ');

                displayProjects(Name, cost, workers, p_exist);
                calculateTotalBudget(cost, p_exist);
                calculateAverageWorkers(workers, p_exist);
                largestBudgetProject(cost, Name, p_exist);
                break;
            }
            case 4: {
                delete[] Name;
                delete[] cost;
                delete[] workers;

                cout << setfill('=') << setw(40) << '=' << endl;
                cout << setfill(' ');
                cout << "----------------- EXIT -----------------" << endl;
                cout << setfill('=') << setw(40) << '=' << endl;
                cout << setfill(' ');
                break;
            }
            default:
                cout << "Invalid choice. Please select again.\n";
        }
    } while (choice != 4);

    return 0;
}
