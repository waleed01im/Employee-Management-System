#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "colors.h"
using namespace std;

string toLower(string s)
{
    for (int i = 0; i < (int)s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}

//  BASE CLASS 
class Base
{
public:
    virtual void display() = 0; // Pure virtual
    virtual void inputData() = 0; 
    virtual ~Base() {}
};

//  BASE CLASS 2: EmployeeRecord
class EmployeeRecord
{
protected:
    int employeeID;
    string employeeName;

public:
    EmployeeRecord()
    {
        employeeID = 0;
        employeeName = "";
    }

    int getEmployeeID() { return employeeID; }
    string getEmployeeName() { return employeeName; }

    // Setters so Manager classes can assign the common fields
    void setEmployeeID(int id) { employeeID = id; }
    void setEmployeeName(string name) { employeeName = name; }

    // Pure virtual file operations every record must implement
    virtual void saveToFile(EmployeeRecord *records[], int count) = 0;
    virtual void loadFromFile(EmployeeRecord *records[], int &count) = 0;
    virtual ~EmployeeRecord() {}
};

//  BASE CLASS 3: Manager
class Manager
{
public:
    virtual void showMenu() = 0;
    virtual ~Manager() {}
};

//  Derived Class : department from Base
class department : public Base
{
private:
    int DepartmentId;
    string DepartmentName;
    int num_employees;
    string head_of_department;

public:
    department()
    {
        DepartmentId = 0;
        num_employees = 0;
        DepartmentName = "";
        head_of_department = "";
    }
    department(int id, const char *deptName, int numEmp, const char *hod)
    {
        DepartmentId = id;
        DepartmentName = deptName;
        num_employees = numEmp;
        head_of_department = hod;
    }

    void inputData() override
    {
        cout << PROMPT_C "Enter Department ID: " RESET;
        cin >> DepartmentId;
        cin.ignore();
        cout << PROMPT_C "Enter Department Name: " RESET;
        getline(cin, DepartmentName);
        DepartmentName = toLower(DepartmentName);
        cout << PROMPT_C "Enter Number of Employees: " RESET;
        cin >> num_employees;
        cin.ignore();
        cout << PROMPT_C "Enter Name of the Head of Department: " RESET;
        getline(cin, head_of_department);
        head_of_department = toLower(head_of_department);
        cout << SUCCESS "\nDepartment Added Successfully!\n" RESET;
    }

    void display() override
    {
        cout << left
             << setw(5)  << DepartmentId
             << CYAN     << setw(28) << DepartmentName << RESET
             << setw(20) << num_employees
             << setw(25) << head_of_department 
             << endl;
    }

    string get_department_name() { return DepartmentName; }
    int get_department_id() { return DepartmentId; }
    int get_num_employees() { return num_employees; }
    string get_head_of_department() { return head_of_department; }

    void setName(string n) { DepartmentName = n; }
    void setNumEmployees(int n) { num_employees = n; }
    void setHOD(string h) { head_of_department = h; }

    void saveToFile(department dept[], int count)
    {
        ofstream File("departments.txt");
        if (!File)
        {
            cout << "Error opening file for writing!\n";
            return;
        }
        for (int i = 0; i < count; i++)
        {
            File << dept[i].DepartmentId << ","
                 << dept[i].DepartmentName << ","
                 << dept[i].num_employees << ","
                 << dept[i].head_of_department << endl;
        }
        File.close();
    }

    void loadFromFile(department dept[], int &count)
    {
        ifstream File("departments.txt");
        if (!File) { return; }
        count = 0;
        while (File >> dept[count].DepartmentId)
        {
            File.ignore();
            getline(File, dept[count].DepartmentName, ',');
            File >> dept[count].num_employees;
            File.ignore();
            getline(File, dept[count].head_of_department);
            count++;
        }
        File.close();
    }
};

//  Derived CLASS: employee from Base
class employee : public Base
{
private:
    int employeeID;
    string name;
    int age;
    string gender;
    string phoneNumber;
    string qualifications;
    string designation;
    string Employeedepartment;
    int experience;
    string salary;
    string joiningYear;

    int presentCount;
    int absentCount;
    double bonusAmount;
    double taxDeduction;
    double netCalculatedSalary;
    bool leaveApplied;
    string leaveStatus;

public:
    employee()
    {
        employeeID = 0;
        age = 0;
        experience = 0;
        presentCount = 0;
        absentCount = 0;
        bonusAmount = 0.0;
        taxDeduction = 0.0;
        netCalculatedSalary = 0.0;
        leaveApplied = false;
        name = gender = phoneNumber = qualifications = "";
        designation = Employeedepartment = joiningYear = "";
        salary = "0";
        leaveStatus = "No Request";
    }

    employee(int id, const char *empName, int empAge, const char *empGender,
             const char *empPhone, const char *empQual,
             const char *empDesig, const char *empDept,
             int empExp, const char *empSal, const char *empYear)
    {
        employeeID = id;
        name = empName;
        age = empAge;
        gender = empGender;
        phoneNumber = empPhone;
        qualifications = empQual;
        designation = empDesig;
        Employeedepartment = empDept;
        experience = empExp;
        salary = empSal;
        joiningYear = empYear;
        presentCount = 0;
        absentCount = 0;
        bonusAmount = 0.0;
        taxDeduction = 0.0;
        leaveApplied = false;
        leaveStatus = "No Request";
        netCalculatedSalary = stoi(salary);
    }

    void inputData() override
    {
        cout << PROMPT_C "Enter Employee ID: " RESET;
        cin >> employeeID;
        cin.ignore();
        cout << PROMPT_C "Enter Name: " RESET;
        getline(cin, name);
        name = toLower(name);
        cout << PROMPT_C "Enter Age: " RESET;
        cin >> age;
        cin.ignore();
        cout << PROMPT_C "Enter Gender: " RESET;
        getline(cin, gender);
        cout << PROMPT_C "Enter Phone Number: " RESET;
        getline(cin, phoneNumber);
        cout << PROMPT_C "Enter Qualifications: " RESET;
        getline(cin, qualifications);
        cout << PROMPT_C "Enter Designation: " RESET;
        getline(cin, designation);
        cout << PROMPT_C "Enter Department: " RESET;
        getline(cin, Employeedepartment);
        Employeedepartment = toLower(Employeedepartment);
        cout << PROMPT_C "Enter Experience (years): " RESET;
        cin >> experience;
        cin.ignore();
        cout << PROMPT_C "Enter Salary: " RESET;
        getline(cin, salary);
        cout << PROMPT_C "Enter Joining Year: " RESET;
        getline(cin, joiningYear);

        netCalculatedSalary = stoi(salary);
        presentCount = 0;
        absentCount = 0;
        bonusAmount = 0.0;
        taxDeduction = 0.0;
        leaveApplied = false;
        leaveStatus = "No Request";

        cout << SUCCESS "\nEmployee Added Successfully!\n" RESET;
    }

    void display() override
    {
        cout << left
             << setw(5)  << employeeID
             << CYAN     << setw(15) << name    << RESET
             << setw(5)  << age
             << setw(10) << gender
             << setw(12) << phoneNumber
             << setw(25) << Employeedepartment
             << setw(25) << designation        
             << setw(10) << salary             
             << setw(10) << joiningYear
             << endl;
    }

    void add_employee() { inputData(); }
    void view_employee() { display(); }

    // Getters
    int get_employee_id() { return employeeID; }
    string get_employee_name() { return name; }
    string get_employee_department() { return Employeedepartment; }
    string get_employee_salary() { return salary; }
    int get_present_count() { return presentCount; }
    int get_absent_count() { return absentCount; }
    double get_bonus() { return bonusAmount; }
    double get_tax() { return taxDeduction; }
    double get_net_salary() { return netCalculatedSalary; }
    bool has_applied_leave() { return leaveApplied; }
    string get_leave_status() { return leaveStatus; }

    // Setters
    void set_present_count(int p) { presentCount = p; }
    void set_absent_count(int a) { absentCount = a; }
    void set_bonus(double b) { bonusAmount = b; }
    void set_tax(double t) { taxDeduction = t; }
    void set_net_salary(double s) { netCalculatedSalary = s; }
    void set_leave_request(bool state, string status)
    {
        leaveApplied = state;
        leaveStatus = status;
    }

    void setName(string n) { name = toLower(n); }
    void setAge(int a) { age = a; }
    void setGender(string g) { gender = g; }
    void setPhone(string p) { phoneNumber = p; }
    void setQualifications(string q) { qualifications = q; }
    void setDesignation(string d) { designation = d; }
    void setDepartment(string d) { Employeedepartment = toLower(d); }
    void setExperience(int e) { experience = e; }
    void setSalary(string s)
    {
        salary = s;
        netCalculatedSalary = stoi(s);
    }

    void saveToFile(employee emp[], int count)
    {
        ofstream outFile("employees.txt");
        if (!outFile)
        {
            cout << ERROR_C << "Error opening file for writing!\n" << RESET;
            return;
        }
        for (int i = 0; i < count; i++)
        {
            outFile << emp[i].employeeID << ","
                    << emp[i].name << ","
                    << emp[i].age << ","
                    << emp[i].gender << ","
                    << emp[i].phoneNumber << ","
                    << emp[i].qualifications << ","
                    << emp[i].designation << ","
                    << emp[i].Employeedepartment << ","
                    << emp[i].experience << ","
                    << emp[i].salary << ","
                    << emp[i].joiningYear 
                    << endl;
        }
        outFile.close();
    }

    void loadFromFile(employee emp[], int &count)
    {
        ifstream inFile("employees.txt");
        if (!inFile) { return; }
        count = 0;
        while (inFile >> emp[count].employeeID)
        {
            inFile.ignore();
            getline(inFile, emp[count].name, ',');
            inFile >> emp[count].age;
            inFile.ignore();
            getline(inFile, emp[count].gender, ',');
            getline(inFile, emp[count].phoneNumber, ',');
            getline(inFile, emp[count].qualifications, ',');
            getline(inFile, emp[count].designation, ',');
            getline(inFile, emp[count].Employeedepartment, ',');
            inFile >> emp[count].experience;
            inFile.ignore();
            getline(inFile, emp[count].salary, ',');
            getline(inFile, emp[count].joiningYear, ',');
            count++;
        }
        inFile.close();
    }
};

//  Global arrays objects & counters
employee emp[100];
department dept[100];
int deptCount = 0;
int empCount = 0;
int attCount = 0;
int payCount = 0;
int leaveCount = 0;

//  Derived CLASS: AttendanceRecord from EmployeeRecord
class AttendanceRecord : public EmployeeRecord
{
public:
    int presentCount;
    int absentCount;

    AttendanceRecord()
    {
        // employeeID and employeeName are in EmployeeRecord base
        presentCount = 0;
        absentCount = 0;
    }

    void saveToFile(EmployeeRecord *records[], int count) override {}
    void loadFromFile(EmployeeRecord *records[], int &count) override {}

    void saveToFile(AttendanceRecord records[], int count)
    {
        ofstream File("attendance.txt");
        if (!File)
        {
            cout << ERROR_C << "Error opening attendance.txt for writing!\n" << RESET;
            return;
        }
        for (int i = 0; i < count; i++)
        {
            File << records[i].employeeID << ","
                 << records[i].employeeName << ","
                 << records[i].presentCount << ","
                 << records[i].absentCount << "\n";
        }
        File.close();
    }

    void loadFromFile(AttendanceRecord records[], int &count)
    {
        ifstream File("attendance.txt");
        if (!File)
        {
            cout << ERROR_C << "No existing attendance data found.\n" << RESET;
            return;
        }
        count = 0;
        while (File >> records[count].employeeID)
        {
            File.ignore();
            getline(File, records[count].employeeName, ',');
            File >> records[count].presentCount;
            File.ignore();
            File >> records[count].absentCount;
            File.ignore();
            count++;
        }
        File.close();
    }
};

//  Derived CLASS: PayrollRecord from EmployeeRecord
class PayrollRecord : public EmployeeRecord
{
public:
    string baseSalary;
    double bonusAmount;
    double taxDeduction;
    double netSalary;

    PayrollRecord()
    {
        // employeeID and employeeName are in EmployeeRecord base
        baseSalary = "0";
        bonusAmount = 0.0;
        taxDeduction = 0.0;
        netSalary = 0.0;
    }

    void saveToFile(EmployeeRecord *records[], int count) override {}
    void loadFromFile(EmployeeRecord *records[], int &count) override {}

    void saveToFile(PayrollRecord records[], int count)
    {
        ofstream File("payroll.txt");
        if (!File)
        {
            cout << ERROR_C << "Error opening payroll.txt for writing!\n" << RESET;
            return;
        }
        for (int i = 0; i < count; i++)
        {
            File << records[i].employeeID << ","
                 << records[i].employeeName << ","
                 << records[i].baseSalary << ","
                 << records[i].bonusAmount << ","
                 << records[i].taxDeduction << ","
                 << records[i].netSalary << "\n";
        }
        File.close();
    }

    void loadFromFile(PayrollRecord records[], int &count)
    {
        ifstream File("payroll.txt");
        if (!File)
        {
            cout << ERROR_C << "No existing payroll data found.\n" << RESET;
            return;
        }
        count = 0;
        while (File >> records[count].employeeID)
        {
            File.ignore();
            getline(File, records[count].employeeName, ',');
            getline(File, records[count].baseSalary, ',');
            File >> records[count].bonusAmount;
            File.ignore();
            File >> records[count].taxDeduction;
            File.ignore();
            File >> records[count].netSalary;
            File.ignore();
            count++;
        }
        File.close();
    }
};

//  Derived CLASS: LeaveRecord from EmployeeRecord
class LeaveRecord : public EmployeeRecord
{
public:
    bool leaveApplied;
    string leaveStatus;

    LeaveRecord()
    {
        // employeeID and employeeName are in EmployeeRecord base
        leaveApplied = false;
        leaveStatus = "No Request";
    }

    void saveToFile(EmployeeRecord *records[], int count) override {}
    void loadFromFile(EmployeeRecord *records[], int &count) override {}

    void saveToFile(LeaveRecord records[], int count)
    {
        ofstream File("leave.txt");
        if (!File)
        {
            cout << ERROR_C << "Error opening leave.txt for writing!\n" << RESET;
            return;
        }
        for (int i = 0; i < count; i++)
        {
            File << records[i].employeeID << ","
                 << records[i].employeeName << ","
                 << records[i].leaveApplied << ","
                 << records[i].leaveStatus << "\n";
        }
        File.close();
    }

    void loadFromFile(LeaveRecord records[], int &count)
    {
        ifstream File("leave.txt");
        if (!File)
        {
            cout << ERROR_C << "No existing leave data found.\n" << RESET;
            return;
        }
        count = 0;
        while (File >> records[count].employeeID)
        {
            File.ignore();
            getline(File, records[count].employeeName, ',');
            File >> records[count].leaveApplied;
            File.ignore();
            getline(File, records[count].leaveStatus);
            count++;
        }
        File.close();
    }
};

//  Global record arrays objects
AttendanceRecord att[100];
PayrollRecord pay[100];
LeaveRecord leave[100];

//  Derived CLASS: EmployeeManager from Manager
class EmployeeManager : public Manager
{
public:
    void printheader()
    {
        cout << HEADER_C "===========================================================================================================\n"
             << BOLD     "                                         Employee Details:\n" RESET
             << HEADER_C "===========================================================================================================\n" RESET
             << GREEN    << left << setw(5) << "ID" << setw(15) << "Name" << setw(5) << "Age"
             << setw(10) << "Gender" << setw(12) << "Phone" << setw(25) << "Department"
             << setw(25) << "Designation" << setw(10) << "Salary" << setw(10) << "Year"
             << RESET << endl << endl;
    }

    void addEmployee()
    {
        emp[empCount].add_employee();
        empCount++;
        emp[0].saveToFile(emp, empCount);
        system("pause");
    }

    void viewAllEmployees()
    {
        if (empCount == 0)
        {
            cout << "\nNo employees added yet.\n";
            return;
        }
        printheader();
        for (int i = 0; i < empCount; i++)
            emp[i].display();
        system("pause");
    }

    void updateEmployee()
    {
        int id;
        cout << PROMPT_C << "Enter Employee ID to Update: " << RESET;
        cin >> id;
        cin.ignore();
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                cout << MENU_C << "\nCurrent Employee Details:\n" << RESET;
                emp[i].display();
                int choice;
                do
                {
                    cout << PROMPT_C << "\nWhat do you want to update?\n" << RESET;
                    cout << "1. Name\n2. Age\n3. Gender\n4. Phone Number\n";
                    cout << "5. Qualifications\n6. Designation\n7. Department\n";
                    cout << "8. Experience\n9. Salary\n10. Done\n";
                    cout << PROMPT_C << "Enter your choice: " << RESET;
                    cin >> choice;
                    cin.ignore();
                    string tmp;
                    int itmp;
                    switch (choice)
                    {
                    case 1:
                    cout << PROMPT_C << "New Name: " << RESET;
                        getline(cin, tmp);
                        emp[i].setName(tmp);
                        cout << SUCCESS << "Updated.\n" << RESET;
                        break;
                    case 2:
                        cout << PROMPT_C << "New Age: " << RESET;
                        cin >> itmp;
                        cin.ignore();
                        emp[i].setAge(itmp);
                        cout << SUCCESS << "Updated.\n" << RESET;
                        break;
                    case 3:
                        cout << PROMPT_C << "New Gender: " << RESET;
                        getline(cin, tmp);
                        emp[i].setGender(tmp);
                        cout << SUCCESS << "Updated.\n" << RESET;
                        break;
                    case 4:
                        cout << PROMPT_C << "New Phone: " << RESET;
                        getline(cin, tmp);
                        emp[i].setPhone(tmp);
                        cout << SUCCESS << "Updated.\n" << RESET;
                        break;
                    case 5:
                        cout << PROMPT_C << "New Qualifications: " << RESET;
                        getline(cin, tmp);
                        emp[i].setQualifications(tmp);
                        cout << SUCCESS << "Updated.\n" << RESET;
                        break;
                    case 6:
                        cout << PROMPT_C << "New Designation: " << RESET;
                        getline(cin, tmp);
                        emp[i].setDesignation(tmp);
                        cout << SUCCESS << "Updated.\n" << RESET;
                        break;
                    case 7:
                        cout << PROMPT_C << "New Department: " << RESET;
                        getline(cin, tmp);
                        emp[i].setDepartment(tmp);
                        cout << SUCCESS << "Updated.\n" << RESET;
                        break;
                    case 8:
                        cout << PROMPT_C << "New Experience: " << RESET;
                        cin >> itmp;
                        cin.ignore();
                        emp[i].setExperience(itmp);
                        cout << SUCCESS << "Updated.\n" << RESET;
                        break;
                    case 9:
                        cout << PROMPT_C << "New Salary: " << RESET;
                        getline(cin, tmp);
                        emp[i].setSalary(tmp);
                        cout << SUCCESS << "Updated.\n" << RESET;
                        break;
                    case 10:
                        break;
                    default:
                        cout << ERROR_C << "Invalid choice.\n" << RESET;
                        break;
                    }
                } while (choice != 10);
            }
        }
        if (!found)
            cout << ERROR_C << "Employee not found.\n" << RESET;
        emp[0].saveToFile(emp, empCount);
        system("pause");
    }

    void searchEmployee()
    {
        int id;
        cout << PROMPT_C << "Enter Employee ID to Search: " << RESET;
        cin >> id;
        cin.ignore(); // Clear the newline character from the buffer
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                printheader();
                emp[i].display();
                break;
            }
        }
        if (!found)
            cout << ERROR_C << "Employee not found.\n" << RESET;
        system("pause");
    }

    void deleteEmployee()
    {
        int id;
        cout << PROMPT_C << "Enter Employee ID to Delete: " << RESET;
        cin >> id;
        cin.ignore(); // Clear the newline character from the buffer
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                printheader();
                emp[i].display();
                for (int j = i; j < empCount - 1; j++)
                    emp[j] = emp[j + 1];
                empCount--;
                cout << SUCCESS << "\nEmployee Deleted Successfully!\n" << RESET;
                break;
            }
        }
        if (!found)
            cout << ERROR_C << "Employee not found.\n" << RESET;
        emp[0].saveToFile(emp, empCount);
        system("pause");
    }

    // Override showMenu() from Manager base
    void showMenu() override
    {
        int choice;
        do
        {
            cout << MENU_C "\n================ Employee Management ================" RESET << endl;
            cout << "1. Add Employee"        << endl;
            cout << "2. View All Employees"  << endl;
            cout << "3. Update Employee"     << endl;
            cout << "4. Search Employee"     << endl;
            cout << "5. Delete Employee"     << endl;
            cout << "6. Back to Main Menu"   << endl;
            cout << PROMPT_C "\nEnter Your Choice: " RESET;
            cin >> choice;
            switch (choice)
            {
            case 1: addEmployee();    break;
            case 2: viewAllEmployees(); break;
            case 3: updateEmployee(); break;
            case 4: searchEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: return;
            default: cout << RED "Invalid choice.\n" RESET;
            }
        } while (choice != 6);
    }
};

//  CLASS: DepartmentManager
class DepartmentManager : public Manager
{
public:
    void addDepartment()
    {
        dept[deptCount].inputData();
        deptCount++;
        dept[0].saveToFile(dept, deptCount);
        system("pause");
    }

    void viewAllDepartments()
    {
        if (deptCount == 0)
        {
            cout << "No departments available.\n";
            return;
        }
        cout << HEADER_C "======================================================================\n" RESET;
        cout << BOLD << "                        Departments List:\n" << RESET;
        cout << HEADER_C "======================================================================\n" RESET;
        cout << RESET << left 
             << GREEN << setw(5) << "ID" << setw(28) << "Department Name" << RESET
             << GREEN << setw(20) << "Employees" << setw(25) << "Head of Department" << RESET << endl;
        for (int i = 0; i < deptCount; i++)
            dept[i].display();
        cout << endl;
        system("pause");
    }

    void updateDepartment()
    {
        string deptname;
        cout << PROMPT_C << "Enter Department Name to Update: " << RESET;
        cin.ignore();
        getline(cin, deptname);
        deptname = toLower(deptname);
        bool found = false;
        for (int i = 0; i < deptCount; i++)
        {
            if (dept[i].get_department_name() == deptname)
            {
                found = true;
                cout << GREEN << "\nCurrent Details:\n" << RESET;
                dept[i].display();
                cin.ignore();
                string tmp;
                int itmp;
                cout << PROMPT_C << "\nWhat do you want to update?\n" << RESET;
                cout << "1. Department Name\n2. Number of Employees\n3. Head of Department\n4. Done\n";
                int choice;
                cin >> choice;
                cin.ignore();
                switch (choice)
                {
                case 1:
                    cout << PROMPT_C << "New Department Name: " << RESET;
                    getline(cin, tmp);
                    dept[i].setName(toLower(tmp));
                    cout << SUCCESS << "Updated.\n" << RESET;
                    break;
                case 2:
                    cout << PROMPT_C << "New Number of Employees: " << RESET;
                    cin >> itmp;
                    cin.ignore();
                    dept[i].setNumEmployees(itmp);
                    cout << SUCCESS << "Updated.\n" << RESET;
                    break;
                case 3:
                    cout << PROMPT_C << "New Head of Department: " << RESET;
                    getline(cin, tmp);
                    dept[i].setHOD(toLower(tmp));
                    cout << SUCCESS << "Updated.\n" << RESET;
                    break;
                case 4:
                    break;
                default:
                    cout << ERROR_C << "Invalid choice.\n" << RESET;
                }
            }
        }
        if (!found)
            cout << ERROR_C << "Department not found.\n" << RESET;
        dept[0].saveToFile(dept, deptCount);
        system("pause");
    }

    void deleteDepartment()
    {
        string deptName;
        cout << PROMPT_C << "Enter Department Name to Delete: " << RESET;
        cin.ignore();
        getline(cin, deptName);
        deptName = toLower(deptName);
        bool found = false;
        for (int i = 0; i < deptCount; i++)
        {
            if (dept[i].get_department_name() == deptName)
            {
                found = true;
                cout << GREEN << "\nCurrent Department Details:\n" << RESET;
                dept[i].display();
                for (int j = i; j < deptCount - 1; j++)
                    dept[j] = dept[j + 1];
                deptCount--;
                cout << SUCCESS << "\nDepartment Deleted Successfully!\n" << RESET;
                break;
            }
        }
        if (!found)
            cout << ERROR_C << "Department not found.\n" << RESET;
        dept[0].saveToFile(dept, deptCount);
        system("pause");
    }

    void searchDepartment()
    {
        string deptName;
        cout << PROMPT_C << "Enter Department Name to Search: " << RESET;
        cin.ignore();
        getline(cin, deptName);
        deptName = toLower(deptName);
        bool found = false;
        for (int i = 0; i < deptCount; i++)
        {
            if (dept[i].get_department_name() == deptName)
            {
                found = true;
                cout << GREEN << "\nDepartment Details:\n" << RESET;
                dept[i].display();
                break;
            }
        }
        if (!found)
            cout << ERROR_C << "Department not found.\n" << RESET;
        system("pause");
    }

    void showMenu() override
    {
        int choice;
        do
        {
            cout << MENU_C "\n================ Department Management ================" RESET << endl;
            cout << "1. Add Department"      << endl;
            cout << "2. View All Departments"<< endl;
            cout << "3. Update Department"   << endl;
            cout << "4. Delete Department"   << endl;
            cout << "5. Search Department"   << endl;
            cout << "6. Back to Main Menu"   << endl;
            cout << PROMPT_C "\nEnter Your Choice: " RESET;
            cin >> choice;
            switch (choice)
            {
            case 1: addDepartment();    break;
            case 2: viewAllDepartments(); break;
            case 3: updateDepartment(); break;
            case 4: deleteDepartment(); break;
            case 5: searchDepartment(); break;
            case 6: return;
            default: cout << ERROR_C << "Invalid choice.\n" << RESET;
            }
        } while (choice != 6);
    }
};

//  CLASS: AttendanceManager
class AttendanceManager : public Manager
{
private:
    void syncRecords()
    {
        attCount = 0;
        for (int i = 0; i < empCount; i++)
        {
            // employeeID and employeeName come from EmployeeRecord base
            att[attCount].setEmployeeID(emp[i].get_employee_id());
            att[attCount].setEmployeeName(emp[i].get_employee_name());
            att[attCount].presentCount = emp[i].get_present_count();
            att[attCount].absentCount = emp[i].get_absent_count();
            attCount++;
        }
    }

public:
    void markAttendance()
    {
        int id;
        cout << PROMPT_C << "Enter Employee ID to Mark Attendance: " << RESET;
        cin >> id;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                int status;
                cout << PROMPT_C << "1. Present\n2. Absent\nSelect Status: " << RESET;
                cin >> status;
                if (status == 1)
                {
                    emp[i].set_present_count(emp[i].get_present_count() + 1);
                    cout << SUCCESS << "Marked Present successfully.\n" << RESET;
                }
                else if (status == 2)
                {
                    emp[i].set_absent_count(emp[i].get_absent_count() + 1);
                    cout << SUCCESS << "Marked Absent successfully.\n" << RESET;
                }
                else
                    cout << ERROR_C << "Invalid choice.\n" << RESET;
                emp[0].saveToFile(emp, empCount);
                syncRecords();
                att[0].saveToFile(att, attCount);
                break;
            }
        }
        if (!found)
            cout << ERROR_C << "Employee ID not found.\n" << RESET;
        system("pause");
    }

    void viewAttendance()
    {
        int id;
        cout << PROMPT_C << "Enter Employee ID to View Attendance: " << RESET;
        cin >> id;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                cout << GREEN <<"\nEmployee: " << RESET << emp[i].get_employee_name()
                     << " | Present: " << emp[i].get_present_count()
                     << " | Absent: " << emp[i].get_absent_count() << "\n";
                break;
            }
        }
        if (!found)
            cout << ERROR_C << "Employee ID not found.\n" << RESET;
        system("pause");
    }

    void monthlyReport()
    {
        cout << HEADER_C << "========================================================\n" << RESET;
        cout << BOLD << left << setw(10) << "ID" << setw(20) << "Name"
             << setw(12) << "Present" << setw(12) << "Absent" << endl  << RESET;
        cout << HEADER_C << "========================================================\n" << RESET;
        for (int i = 0; i < empCount; i++)
        {
            cout << left << setw(10) << emp[i].get_employee_id()
                 << setw(20) << emp[i].get_employee_name()
                 << setw(12) << emp[i].get_present_count()
                 << setw(12) << emp[i].get_absent_count() << endl;
        }
        system("pause");
    }

    void absentEmployees()
    {
        cout << GREEN << "\nHighly Absent Employees (Absents > 3):\n" << RESET;
        cout << HEADER_C << "========================================================\n" << RESET;
        cout << BOLD << left << setw(10) << "ID" << setw(20) << "Name" << setw(12) << "Absents" << endl << RESET;
        cout << HEADER_C << "========================================================\n" << RESET;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_absent_count() > 3)
            {
                cout << left << setw(10) << emp[i].get_employee_id()
                     << setw(20) << emp[i].get_employee_name()
                     << setw(12) << emp[i].get_absent_count() << endl;
                found = true;
            }
        }
        if (!found)
            cout << ERROR_C << "No employees with high absence rates.\n" << RESET;
        system("pause");
    }

    // Override showMenu() from Manager base  <-- INHERITANCE USED
    void showMenu() override
    {
        int choice;
        do
        {
            cout << MENU_C "\n================ Attendance Management ================" RESET << endl;
            cout << "1. Mark Attendance"             << endl;
            cout << "2. View Attendance"             << endl;
            cout << "3. Attendance Report"           << endl;
            cout << "4. View Highly Absent Employees"<< endl;
            cout << "5. Back"                        << endl;
            cout << PROMPT_C "\nEnter Your Choice: " RESET;
            cin >> choice;
            switch (choice)
            {
            case 1: markAttendance(); break;
            case 2: viewAttendance(); break;
            case 3: monthlyReport();  break;
            case 4: absentEmployees();break;
            case 5: return;
            default: cout << ERROR_C << "Invalid selection.\n" << RESET;
            }
        } while (choice != 5);
    }
};

//  CLASS: PayrollManager
class PayrollManager : public Manager
{
private:
    void syncRecords()
    {
        payCount = 0;
        for (int i = 0; i < empCount; i++)
        {
            // employeeID and employeeName come from EmployeeRecord base
            pay[payCount].setEmployeeID(emp[i].get_employee_id());
            pay[payCount].setEmployeeName(emp[i].get_employee_name());
            pay[payCount].baseSalary = emp[i].get_employee_salary();
            pay[payCount].bonusAmount = emp[i].get_bonus();
            pay[payCount].taxDeduction = emp[i].get_tax();
            pay[payCount].netSalary = emp[i].get_net_salary();
            payCount++;
        }
    }

public:
    void generateSalary()
    {
        int id;
        cout << PROMPT_C << "Enter Employee ID to generate salary: " << RESET;
        cin >> id;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                double net = stoi(emp[i].get_employee_salary()) + emp[i].get_bonus() - emp[i].get_tax();
                emp[i].set_net_salary(net);
                cout << SUCCESS << "Net salary updated for " << emp[i].get_employee_name()
                     << " ($" << net << ")\n";
                emp[0].saveToFile(emp, empCount);
                syncRecords();
                pay[0].saveToFile(pay, payCount);
                break;
            }
        }
        if (!found)
            cout << ERROR_C << "Employee not found.\n" << RESET;
        system("pause");
    }

    void viewSalarySlip()
    {
        int id;
        cout << PROMPT_C << "Enter Employee ID: " << RESET;
        cin >> id;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                cout << TABLE_C << "\n--- SALARY SLIP ---\n" << RESET;
                cout << "ID: " << emp[i].get_employee_id() << "\n";
                cout << "Name: " << emp[i].get_employee_name() << "\n";
                cout << "Base Salary:   $" << emp[i].get_employee_salary() << "\n";
                cout << "Bonus:        +$" << emp[i].get_bonus() << "\n";
                cout << "Tax:          -$" << emp[i].get_tax() << "\n";
                cout << YELLOW << "-------------------\n" << RESET;
                cout << "Net Payable:   $" << emp[i].get_net_salary() << "\n";
                break;
            }
        }
        if (!found)
            cout << ERROR_C << "Employee not found.\n" << RESET;
        system("pause");
    }

    void addBonus()
    {
        int id;
        double bonus;
        cout << PROMPT_C << "Enter Employee ID: " << RESET;
        cin >> id;
        cout << PROMPT_C << "Enter Bonus Amount: " << RESET;
        cin >> bonus;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                emp[i].set_bonus(bonus);
                double base = stoi(emp[i].get_employee_salary());
                emp[i].set_net_salary(base + emp[i].get_bonus() - emp[i].get_tax());
                cout << SUCCESS << "Bonus allocated successfully.\n" << RESET;
                emp[0].saveToFile(emp, empCount);
                syncRecords();
                pay[0].saveToFile(pay, payCount);
                break;
            }
        }
        system("pause");
    }

    void deductTax()
    {
        int id;
        double tax;
        cout << PROMPT_C << "Enter Employee ID: " << RESET;
        cin >> id;
        cout << PROMPT_C << "Enter Tax Amount: " << RESET;
        cin >> tax;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                emp[i].set_tax(tax);
                double base = stoi(emp[i].get_employee_salary());
                emp[i].set_net_salary(base + emp[i].get_bonus() - emp[i].get_tax());
                cout << SUCCESS << "Tax deducted successfully.\n" << RESET;
                emp[0].saveToFile(emp, empCount);
                syncRecords();
                pay[0].saveToFile(pay, payCount);
                break;
            }
        }
        system("pause");
    }

    void payrollReport()
    {
        cout << HEADER_C << "========================================================================\n" << RESET;
        cout << BOLD << left << setw(8) << "ID" << setw(15) << "Name" << setw(12) << "Base"
             << setw(10) << "Bonus" << setw(10) << "Tax" << setw(12) << "Net Salary" << endl << RESET;
        cout << HEADER_C << "========================================================================\n" << RESET;
        for (int i = 0; i < empCount; i++)
        {
            cout << left << setw(8) << emp[i].get_employee_id()
                 << setw(15) << emp[i].get_employee_name()
                 << setw(12) << emp[i].get_employee_salary()
                 << setw(10) << emp[i].get_bonus()
                 << setw(10) << emp[i].get_tax()
                 << setw(12) << emp[i].get_net_salary() << endl;
        }
        system("pause");
    }

    void showMenu() override
    {
        int choice;
        do
        {
            cout << MENU_C "\n================ Payroll Management ================" RESET << endl;
            cout << "1. Generate Salary" << endl;
            cout << "2. View Salary Slip" << endl;
            cout << "3. Add Bonus"        << endl;
            cout << "4. Deduct Tax"       << endl;
            cout << "5. Payroll Report"   << endl;
            cout << "6. Back"             << endl;
            cout << PROMPT_C "\nEnter Your Choice: " RESET;
            cin >> choice;
            switch (choice)
            {
            case 1: generateSalary(); break;
            case 2: viewSalarySlip(); break;
            case 3: addBonus();       break;
            case 4: deductTax();      break;
            case 5: payrollReport();  break;
            case 6: return;
            default: cout << RED "Invalid choice.\n" RESET;
            }
        } while (choice != 6);
    }
};

//  CLASS: LeaveManager
class LeaveManager : public Manager
{
private:
    void syncRecords()
    {
        leaveCount = 0;
        for (int i = 0; i < empCount; i++)
        {
            // employeeID and employeeName come from EmployeeRecord base
            leave[leaveCount].setEmployeeID(emp[i].get_employee_id());
            leave[leaveCount].setEmployeeName(emp[i].get_employee_name());
            leave[leaveCount].leaveApplied = emp[i].has_applied_leave();
            leave[leaveCount].leaveStatus = emp[i].get_leave_status();
            leaveCount++;
        }
    }

public:
    void applyLeave()
    {
        int id;
        cout << PROMPT_C << "Enter your Employee ID: " << RESET;
        cin >> id;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                emp[i].set_leave_request(true, "Pending Approval");
                cout << SUCCESS << "Leave request submitted.\n" << RESET;
                emp[0].saveToFile(emp, empCount);
                syncRecords();
                leave[0].saveToFile(leave, leaveCount);
                break;
            }
        }
        system("pause");
    }

    void viewLeaveStatus()
    {
        int id;
        cout << PROMPT_C << "Enter Employee ID: " << RESET;
        cin >> id;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                cout << GREEN << "Leave Status: " << RESET << emp[i].get_leave_status() << "\n";
                break;
            }
        }
        system("pause");
    }

    void manageLeave()
    {
        cout << TABLE_C << "\nPending Leave Requests:\n" << RESET;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].has_applied_leave())
                cout << "ID: " << emp[i].get_employee_id()
                     << " | Name: " << emp[i].get_employee_name()
                     << " | Status: " << emp[i].get_leave_status() << "\n";
        }
        int targetId;
        cout << PROMPT_C << "\nEnter Employee ID to act upon: " << RESET;
        cin >> targetId;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == targetId)
            {
                int decision;
                cout << PROMPT_C << "1. Approve\n2. Reject\nChoice: " << RESET;
                cin >> decision;
                if (decision == 1)
                    emp[i].set_leave_request(true, "Approved");
                else if (decision == 2)
                    emp[i].set_leave_request(false, "Rejected");
                cout << SUCCESS << "Decision recorded.\n" << RESET;
                emp[0].saveToFile(emp, empCount);
                syncRecords();
                leave[0].saveToFile(leave, leaveCount);
                break;
            }
        }
        system("pause");
    }

    // Override showMenu() from Manager base  <-- INHERITANCE USED
    void showMenu() override
    {
        int choice;
        do
        {
            cout << MENU_C "\n================ Leave Management ================" RESET << endl;
            cout << "1. Apply Leave"                    << endl;
            cout << "2. View Leave Status"              << endl;
            cout << "3. Manage Leave (Approve/Reject)"  << endl;
            cout << "4. Back"                           << endl;
            cout << PROMPT_C "\nEnter Your Choice: " RESET;
            cin >> choice;
            switch (choice)
            {
            case 1: applyLeave();    break;
            case 2: viewLeaveStatus(); break;
            case 3: manageLeave();   break;
            case 4: return;
            default: cout << ERROR_C "Unknown selection.\n" << RESET;
            }
        } while (choice != 4);
    }
};

//  CLASS: ReportManager
class ReportManager : public Manager
{
private:
    void printheader()
    {
        cout << HEADER_C "========================================================================================================\n"
             << BOLD     "                                         Employee Details:\n" RESET
             << HEADER_C "========================================================================================================\n" RESET
             << GREEN << left << setw(5) << "ID" << setw(15) << "Name" << setw(5) << "Age"
             << setw(10) << "Gender" << setw(15) << "Phone" << setw(28) << "Department"
             << setw(15) << "Designation" << setw(10) << "Salary" << setw(10) << "Year"
             << RESET << endl << endl;
    }

public:
    void searchByID()
    {
        int id;
        cout << PROMPT_C "\nEnter Employee ID: " RESET;
        cin >> id;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                printheader();
                emp[i].view_employee();
                found = true;
            }
        }
        if (!found)
            cout << RED "\nEmployee not found.\n" RESET;
        system("pause");
    }

    void searchByName()
    {
        string name;
        bool found = false;
        cin.ignore();
        cout << PROMPT_C "\nEnter Employee Name: " RESET;
        getline(cin, name);
        name = toLower(name);
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_name() == name)
            {
                printheader();
                emp[i].view_employee();
                found = true;
            }
        }
        if (!found)
            cout << RED "\nEmployee not found.\n" RESET;
        system("pause");
    }

    void departmentReport()
    {
        string deptName;
        bool found = false;
        cin.ignore();
        cout << PROMPT_C "\nEnter Department Name: " RESET;
        getline(cin, deptName);
        deptName = toLower(deptName);
        cout <<"\nEmployees in " << CYAN << deptName << " "<< RESET << "Department:\n" ;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_department() == deptName)
            {
                cout << GREEN << left << setw(5) << "ID" << setw(15) << "Name" << setw(5) << "Age"
                     << setw(10) << "Gender" << setw(12) << "Phone" << setw(25) << "Department"
                     << setw(25) << "Designation" << setw(10) << "Salary" << setw(10) << "Year"
                     << RESET << endl << endl;
                emp[i].view_employee();
                found = true;
            }
        }
        if (!found)
            cout << RED "\nNo employees found in this department.\n" RESET;
        system("pause");
    }

    void highestPaidEmployee()
    {
        if (empCount == 0)
        {
            cout << RED "\nNo employees available.\n" RESET;
            return;
        }
        int maxIdx = 0;
        for (int i = 1; i < empCount; i++)
        {
            if (stoi(emp[i].get_employee_salary()) > stoi(emp[maxIdx].get_employee_salary()))
                maxIdx = i;
        }
        cout << YELLOW "\nHighest Paid Employee:\n" RESET;
            cout << GREEN << left << setw(5) << "ID" << setw(15) << "Name" << setw(5) << "Age"
                     << setw(10) << "Gender" << setw(12) << "Phone" << setw(25) << "Department"
                     << setw(25) << "Designation" << setw(10) << "Salary" << setw(10) << "Year"
                     << RESET << endl << endl;
        emp[maxIdx].view_employee();
        system("pause");
    }

    void totalEmployees()
    {
        cout <<"\nTotal Employees: "  << CYAN  << empCount  << RESET << endl;
        system("pause");
    }

    // Override showMenu() from Manager base  <-- INHERITANCE USED
    void showMenu() override
    {
        int choice;
        do
        {
            cout << MENU_C "\n================ Reports & Search ================" RESET << endl;
            cout << "1. Search Employee by ID"   << endl;
            cout << "2. Search Employee by Name" << endl;
            cout << "3. Department Report"        << endl;
            cout << "4. Highest Paid Employee"    << endl;
            cout << "5. Total Employees"          << endl;
            cout << "6. Back"                     << endl;
            cout << PROMPT_C "\nEnter Your Choice: " RESET;
            cin >> choice;
            switch (choice)
            {
            case 1: searchByID();          break;
            case 2: searchByName();        break;
            case 3: departmentReport();    break;
            case 4: highestPaidEmployee(); break;
            case 5: totalEmployees();      break;
            case 6: return;
            default: cout << ERROR_C "\nInvalid Choice.\n" RESET;
            }
        } while (choice != 6);
    }
};

//  CLASS: AuthManager
class AuthManager
{
private:
    string adminUsername;
    string adminPassword;
    bool isLoggedIn;

public:
    AuthManager()
    {
        adminUsername = "admin";
        adminPassword = "1234";
        isLoggedIn = false;
    }

    bool login()
    {
        string username, password;
        int choice;
        do
        {
            cout << MENU_C "\n================ Admin Login ================" RESET << endl;
            cout << "1. Login" << endl;
            cout << "2. Exit"  << endl;
            cout << PROMPT_C "Enter Your Choice: " RESET;
            cin >> choice;

            if (choice == 1)
            {
                cout << PROMPT_C "Enter Username: " RESET;
                cin >> username;
                cout << PROMPT_C "Enter Password: " RESET;
                cin >> password;

                if (username != adminUsername)
                    cout << ERROR_C "\nInvalid Username.\n" RESET;
                else if (password != adminPassword)
                    cout << ERROR_C "\nInvalid Password.\n" RESET;
                else
                {
                    isLoggedIn = true;
                    cout << SUCCESS "\nLogin Successful!\n" RESET;
                    system("pause");
                    return true;
                }
            }
            else
                exit(0);
        } while (choice != 1);
        return false;
    }

    bool loggedIn() const { return isLoggedIn; }
};

//  CLASS: MenuSystem
class MenuSystem
{
private:
    EmployeeManager empMgr;
    DepartmentManager deptMgr;
    AttendanceManager attnMgr;
    PayrollManager payMgr;
    LeaveManager leaveMgr;
    ReportManager reportMgr;
    AuthManager auth;

public:
    void run()
    {
        emp[0].loadFromFile(emp, empCount);
        dept[0].loadFromFile(dept, deptCount);
        if (empCount > 0)
        {
            att[0].loadFromFile(att, attCount);
            pay[0].loadFromFile(pay, payCount);
            leave[0].loadFromFile(leave, leaveCount);
        }

        do
        {
            if (auth.login())
                mainMenu();
        } while (!auth.loggedIn());
    }

private:
    void mainMenu()
    {
        int choice;
        do
        {
            cout << MENU_C "\n=======================================" RESET << endl;
            cout << MENU_C << BOLD   "      Employee Management System"       RESET << endl;
            cout << MENU_C "=======================================" RESET << endl;
            cout << "1. Employee Management"   << endl;
            cout << "2. Department Management" << endl;
            cout << "3. Attendance Management" << endl;
            cout << "4. Payroll Management"    << endl;
            cout << "5. Leave Management"      << endl;
            cout << "6. Reports & Search"      << endl;
            cout << "7. Exit"                  << endl;
            cout << PROMPT_C "\nPlease select an option: " RESET;
            cin >> choice;
            switch (choice)
            {
            case 1: empMgr.showMenu();    break;
            case 2: deptMgr.showMenu();   break;
            case 3: attnMgr.showMenu();   break;
            case 4: payMgr.showMenu();    break;
            case 5: leaveMgr.showMenu();  break;
            case 6: reportMgr.showMenu(); break;
            case 7:
                cout << YELLOW "Exiting!\n" RESET;
                exit(0);
            default:
                cout << RED "Invalid choice.\n" RESET;
            }
        } while (choice != 7);
    }
};

int main()
{
    enableColors();
    MenuSystem system;
    system.run();
    return 0;
}