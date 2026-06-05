#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

string toLower(string s)
{
    for (int i = 0; i < (int)s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}

// ============================================================
//  BASE CLASS  (already existed)
// ============================================================
class Base
{
public:
    virtual void display() = 0;
    virtual void inputData() = 0;
    virtual ~Base() {}
};

// ============================================================
//  BASE CLASS 2: EmployeeRecord
//  AttendanceRecord, PayrollRecord, LeaveRecord all share
//  employeeID / employeeName and file I/O -> put them here
// ============================================================
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
// ============================================================
//  BASE CLASS 3: Manager
//  Every *Manager class has showMenu() -> put it here
// ============================================================
class Manager
{
public:
    virtual void showMenu() = 0;
    virtual ~Manager() {}
};

// ============================================================
//  CLASS: department  (inherits Base - same as before)
// ============================================================
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
        cout << "Enter Department ID: ";
        cin >> DepartmentId;
        cin.ignore();
        cout << "Enter Department Name: ";
        getline(cin, DepartmentName);
        DepartmentName = toLower(DepartmentName);
        cout << "Enter Number of Employees: ";
        cin >> num_employees;
        cin.ignore();
        cout << "Enter Name of the Head of Department: ";
        getline(cin, head_of_department);
        head_of_department = toLower(head_of_department);
        cout << "\nDepartment Added Successfully!" << endl;
    }

    void display() override
    {
        cout << left
             << setw(5) << DepartmentId
             << setw(28) << DepartmentName
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

// ============================================================
//  CLASS: employee  (inherits Base - same as before)
// ============================================================
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
        cout << "Enter Employee ID: ";
        cin >> employeeID;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        name = toLower(name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Gender: ";
        getline(cin, gender);
        cout << "Enter Phone Number: ";
        getline(cin, phoneNumber);
        cout << "Enter Qualifications: ";
        getline(cin, qualifications);
        cout << "Enter Designation: ";
        getline(cin, designation);
        cout << "Enter Department: ";
        getline(cin, Employeedepartment);
        Employeedepartment = toLower(Employeedepartment);
        cout << "Enter Experience (years): ";
        cin >> experience;
        cin.ignore();
        cout << "Enter Salary: ";
        getline(cin, salary);
        cout << "Enter Joining Year: ";
        getline(cin, joiningYear);

        netCalculatedSalary = stoi(salary);
        presentCount = 0;
        absentCount = 0;
        bonusAmount = 0.0;
        taxDeduction = 0.0;
        leaveApplied = false;
        leaveStatus = "No Request";

        cout << "\nEmployee Added Successfully!" << endl;
    }

    void display() override
    {
        cout << left
             << setw(5) << employeeID
             << setw(15) << name
             << setw(5) << age
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
            cout << "Error opening file for writing!\n";
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

// ============================================================
//  Global arrays & counters  (same as before)
// ============================================================
employee emp[100];
department dept[100];
int deptCount = 0;
int empCount = 0;
int attCount = 0;
int payCount = 0;
int leaveCount = 0;

// ============================================================
//  CLASS: AttendanceRecord
//  NOW inherits EmployeeRecord  <-- INHERITANCE ADDED
// ============================================================
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
            cout << "Error opening attendance.txt for writing!\n";
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
            cout << "No existing attendance data found.\n";
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

// ============================================================
//  CLASS: PayrollRecord
//  NOW inherits EmployeeRecord  <-- INHERITANCE ADDED
// ============================================================
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
            cout << "Error opening payroll.txt for writing!\n";
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
            cout << "No existing payroll data found.\n";
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

// ============================================================
//  CLASS: LeaveRecord
//  NOW inherits EmployeeRecord  <-- INHERITANCE ADDED
// ============================================================
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
            cout << "Error opening leave.txt for writing!\n";
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
            cout << "No existing leave data found.\n";
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

//  Global record arrays
AttendanceRecord att[100];
PayrollRecord pay[100];
LeaveRecord leave[100];

//  CLASS: EmployeeManager
class EmployeeManager : public Manager
{
public:
    void printheader()
    {
        cout << "===========================================================================================================\n";
        cout << "                                         Employee Details:\n";
        cout << "===========================================================================================================\n";
        cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(5) << "Age"
             << setw(10) << "Gender" << setw(12) << "Phone" << setw(25) << "Department"
             << setw(25) << "Designation" << setw(10) << "Salary" << setw(10) << "Year"
             << endl
             << endl;
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
        cout << "Enter Employee ID to Update: ";
        cin >> id;
        cin.ignore();
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                cout << "\nCurrent Employee Details:\n";
                emp[i].display();
                int choice;
                do
                {
                    cout << "\nWhat do you want to update?\n";
                    cout << "1. Name\n2. Age\n3. Gender\n4. Phone Number\n";
                    cout << "5. Qualifications\n6. Designation\n7. Department\n";
                    cout << "8. Experience\n9. Salary\n10. Done\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cin.ignore();
                    string tmp;
                    int itmp;
                    switch (choice)
                    {
                    case 1:
                        cout << "New Name: ";
                        getline(cin, tmp);
                        emp[i].setName(tmp);
                        cout << "Updated.\n";
                        break;
                    case 2:
                        cout << "New Age: ";
                        cin >> itmp;
                        cin.ignore();
                        emp[i].setAge(itmp);
                        cout << "Updated.\n";
                        break;
                    case 3:
                        cout << "New Gender: ";
                        getline(cin, tmp);
                        emp[i].setGender(tmp);
                        cout << "Updated.\n";
                        break;
                    case 4:
                        cout << "New Phone: ";
                        getline(cin, tmp);
                        emp[i].setPhone(tmp);
                        cout << "Updated.\n";
                        break;
                    case 5:
                        cout << "New Qualifications: ";
                        getline(cin, tmp);
                        emp[i].setQualifications(tmp);
                        cout << "Updated.\n";
                        break;
                    case 6:
                        cout << "New Designation: ";
                        getline(cin, tmp);
                        emp[i].setDesignation(tmp);
                        cout << "Updated.\n";
                        break;
                    case 7:
                        cout << "New Department: ";
                        getline(cin, tmp);
                        emp[i].setDepartment(tmp);
                        cout << "Updated.\n";
                        break;
                    case 8:
                        cout << "New Experience: ";
                        cin >> itmp;
                        cin.ignore();
                        emp[i].setExperience(itmp);
                        cout << "Updated.\n";
                        break;
                    case 9:
                        cout << "New Salary: ";
                        getline(cin, tmp);
                        emp[i].setSalary(tmp);
                        cout << "Updated.\n";
                        break;
                    case 10:
                        break;
                    default:
                        cout << "Invalid choice.\n";
                        break;
                    }
                } while (choice != 10);
            }
        }
        if (!found)
            cout << "Employee not found.\n";
        emp[0].saveToFile(emp, empCount);
        system("pause");
    }

    void searchEmployee()
    {
        int id;
        cout << "Enter Employee ID to Search: ";
        cin >> id;
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
            cout << "Employee not found.\n";
        system("pause");
    }

    void deleteEmployee()
    {
        int id;
        cout << "Enter Employee ID to Delete: ";
        cin >> id;
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
                cout << "\nEmployee Deleted Successfully!\n";
                break;
            }
        }
        if (!found)
            cout << "Employee not found.\n";
        emp[0].saveToFile(emp, empCount);
        system("pause");
    }

    // Override showMenu() from Manager base
    void showMenu() override
    {
        int choice;
        do
        {
            cout << "\n===================================" << endl;
            cout << "        Employee Management" << endl;
            cout << "===================================" << endl;
            cout << "1. Add Employee" << endl;
            cout << "2. View All Employees" << endl;
            cout << "3. Update Employee" << endl;
            cout << "4. Search Employee" << endl;
            cout << "5. Delete Employee" << endl;
            cout << "6. Back to Main Menu" << endl;
            cout << "\nEnter Your Choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                addEmployee();
                break;
            case 2:
                viewAllEmployees();
                break;
            case 3:
                updateEmployee();
                break;
            case 4:
                searchEmployee();
                break;
            case 5:
                deleteEmployee();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice.\n";
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
        cout << "======================================================================\n";
        cout << "                        Departments List:\n";
        cout << "======================================================================\n";
        cout << left << setw(5) << "ID" << setw(28) << "Department Name"
             << setw(20) << "Employees" << setw(25) << "Head of Department" << endl;
        for (int i = 0; i < deptCount; i++)
            dept[i].display();
        cout << endl;
        system("pause");
    }

    void updateDepartment()
    {
        string deptname;
        cout << "Enter Department Name to Update: ";
        cin.ignore();
        getline(cin, deptname);
        deptname = toLower(deptname);
        bool found = false;
        for (int i = 0; i < deptCount; i++)
        {
            if (dept[i].get_department_name() == deptname)
            {
                found = true;
                cout << "\nCurrent Details:\n";
                dept[i].display();
                cin.ignore();
                string tmp;
                int itmp;
                cout << "\nWhat do you want to update?\n";
                cout << "1. Department Name\n2. Number of Employees\n3. Head of Department\n4. Done\n";
                int choice;
                cin >> choice;
                cin.ignore();
                switch (choice)
                {
                case 1:
                    cout << "New Department Name: ";
                    getline(cin, tmp);
                    dept[i].setName(toLower(tmp));
                    cout << "Updated.\n";
                    break;
                case 2:
                    cout << "New Number of Employees: ";
                    cin >> itmp;
                    cin.ignore();
                    dept[i].setNumEmployees(itmp);
                    cout << "Updated.\n";
                    break;
                case 3:
                    cout << "New Head of Department: ";
                    getline(cin, tmp);
                    dept[i].setHOD(toLower(tmp));
                    cout << "Updated.\n";
                    break;
                case 4:
                    break;
                default:
                    cout << "Invalid choice.\n";
                }
            }
        }
        if (!found)
            cout << "Department not found.\n";
        dept[0].saveToFile(dept, deptCount);
        system("pause");
    }

    void deleteDepartment()
    {
        string deptName;
        cout << "Enter Department Name to Delete: ";
        cin.ignore();
        getline(cin, deptName);
        deptName = toLower(deptName);
        bool found = false;
        for (int i = 0; i < deptCount; i++)
        {
            if (dept[i].get_department_name() == deptName)
            {
                found = true;
                cout << "\nCurrent Department Details:\n";
                dept[i].display();
                for (int j = i; j < deptCount - 1; j++)
                    dept[j] = dept[j + 1];
                deptCount--;
                cout << "\nDepartment Deleted Successfully!\n";
                break;
            }
        }
        if (!found)
            cout << "Department not found.\n";
        dept[0].saveToFile(dept, deptCount);
        system("pause");
    }

    void searchDepartment()
    {
        string deptName;
        cout << "Enter Department Name to Search: ";
        cin.ignore();
        getline(cin, deptName);
        deptName = toLower(deptName);
        bool found = false;
        for (int i = 0; i < deptCount; i++)
        {
            if (dept[i].get_department_name() == deptName)
            {
                found = true;
                cout << "\nDepartment Details:\n";
                dept[i].display();
                break;
            }
        }
        if (!found)
            cout << "Department not found.\n";
        system("pause");
    }

    void showMenu() override
    {
        int choice;
        do
        {
            cout << "\n========================================" << endl;
            cout << "         Department Management" << endl;
            cout << "========================================" << endl;
            cout << "1. Add Department" << endl;
            cout << "2. View All Departments" << endl;
            cout << "3. Update Department" << endl;
            cout << "4. Delete Department" << endl;
            cout << "5. Search Department" << endl;
            cout << "6. Back to Main Menu" << endl;
            cout << "\nEnter Your Choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                addDepartment();
                break;
            case 2:
                viewAllDepartments();
                break;
            case 3:
                updateDepartment();
                break;
            case 4:
                deleteDepartment();
                break;
            case 5:
                searchDepartment();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice.\n";
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
        cout << "Enter Employee ID to Mark Attendance: ";
        cin >> id;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                int status;
                cout << "1. Present\n2. Absent\nSelect Status: ";
                cin >> status;
                if (status == 1)
                {
                    emp[i].set_present_count(emp[i].get_present_count() + 1);
                    cout << "Marked Present successfully.\n";
                }
                else if (status == 2)
                {
                    emp[i].set_absent_count(emp[i].get_absent_count() + 1);
                    cout << "Marked Absent successfully.\n";
                }
                else
                    cout << "Invalid choice.\n";
                emp[0].saveToFile(emp, empCount);
                syncRecords();
                att[0].saveToFile(att, attCount);
                break;
            }
        }
        if (!found)
            cout << "Employee ID not found.\n";
        system("pause");
    }

    void viewAttendance()
    {
        int id;
        cout << "Enter Employee ID to View Attendance: ";
        cin >> id;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                cout << "\nEmployee: " << emp[i].get_employee_name()
                     << " | Present: " << emp[i].get_present_count()
                     << " | Absent: " << emp[i].get_absent_count() << "\n";
                break;
            }
        }
        if (!found)
            cout << "Employee ID not found.\n";
        system("pause");
    }

    void monthlyReport()
    {
        cout << "========================================================\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name"
             << setw(12) << "Present" << setw(12) << "Absent" << endl;
        cout << "========================================================\n";
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
        cout << "\nHighly Absent Employees (Absents > 3):\n";
        cout << "========================================================\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(12) << "Absents" << endl;
        cout << "========================================================\n";
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
            cout << "No employees with high absence rates.\n";
        system("pause");
    }

    // Override showMenu() from Manager base  <-- INHERITANCE USED
    void showMenu() override
    {
        int choice;
        do
        {
            cout << "\n================ Attendance Management ================" << endl;
            cout << "1. Mark Attendance" << endl;
            cout << "2. View Attendance" << endl;
            cout << "3. Attendance Report" << endl;
            cout << "4. View Highly Absent Employees" << endl;
            cout << "5. Back" << endl;
            cout << "\nEnter Your Choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                markAttendance();
                break;
            case 2:
                viewAttendance();
                break;
            case 3:
                monthlyReport();
                break;
            case 4:
                absentEmployees();
                break;
            case 5:
                return;
            default:
                cout << "Invalid selection.\n";
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
        cout << "Enter Employee ID to generate salary: ";
        cin >> id;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                double net = stoi(emp[i].get_employee_salary()) + emp[i].get_bonus() - emp[i].get_tax();
                emp[i].set_net_salary(net);
                cout << "Net salary updated for " << emp[i].get_employee_name()
                     << " ($" << net << ")\n";
                emp[0].saveToFile(emp, empCount);
                syncRecords();
                pay[0].saveToFile(pay, payCount);
                break;
            }
        }
        if (!found)
            cout << "Employee not found.\n";
        system("pause");
    }

    void viewSalarySlip()
    {
        int id;
        cout << "Enter Employee ID: ";
        cin >> id;
        bool found = false;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                found = true;
                cout << "\n--- SALARY SLIP ---\n";
                cout << "ID: " << emp[i].get_employee_id() << "\n";
                cout << "Name: " << emp[i].get_employee_name() << "\n";
                cout << "Base Salary:   $" << emp[i].get_employee_salary() << "\n";
                cout << "Bonus:        +$" << emp[i].get_bonus() << "\n";
                cout << "Tax:          -$" << emp[i].get_tax() << "\n";
                cout << "-------------------\n";
                cout << "Net Payable:   $" << emp[i].get_net_salary() << "\n";
                break;
            }
        }
        if (!found)
            cout << "Employee not found.\n";
        system("pause");
    }

    void addBonus()
    {
        int id;
        double bonus;
        cout << "Enter Employee ID: ";
        cin >> id;
        cout << "Enter Bonus Amount: ";
        cin >> bonus;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                emp[i].set_bonus(bonus);
                double base = stoi(emp[i].get_employee_salary());
                emp[i].set_net_salary(base + emp[i].get_bonus() - emp[i].get_tax());
                cout << "Bonus allocated successfully.\n";
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
        cout << "Enter Employee ID: ";
        cin >> id;
        cout << "Enter Tax Amount: ";
        cin >> tax;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                emp[i].set_tax(tax);
                double base = stoi(emp[i].get_employee_salary());
                emp[i].set_net_salary(base + emp[i].get_bonus() - emp[i].get_tax());
                cout << "Tax deducted successfully.\n";
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
        cout << "========================================================================\n";
        cout << left << setw(8) << "ID" << setw(15) << "Name" << setw(12) << "Base"
             << setw(10) << "Bonus" << setw(10) << "Tax" << setw(12) << "Net Salary" << endl;
        cout << "========================================================================\n";
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
            cout << "\n================ Payroll Management ================" << endl;
            cout << "1. Generate Salary" << endl;
            cout << "2. View Salary Slip" << endl;
            cout << "3. Add Bonus" << endl;
            cout << "4. Deduct Tax" << endl;
            cout << "5. Payroll Report" << endl;
            cout << "6. Back" << endl;
            cout << "\nEnter Your Choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                generateSalary();
                break;
            case 2:
                viewSalarySlip();
                break;
            case 3:
                addBonus();
                break;
            case 4:
                deductTax();
                break;
            case 5:
                payrollReport();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice.\n";
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
        cout << "Enter your Employee ID: ";
        cin >> id;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                emp[i].set_leave_request(true, "Pending Approval");
                cout << "Leave request submitted.\n";
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
        cout << "Enter Employee ID: ";
        cin >> id;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == id)
            {
                cout << "Leave Status: " << emp[i].get_leave_status() << "\n";
                break;
            }
        }
        system("pause");
    }

    void manageLeave()
    {
        cout << "\nPending Leave Requests:\n";
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].has_applied_leave())
                cout << "ID: " << emp[i].get_employee_id()
                     << " | Name: " << emp[i].get_employee_name()
                     << " | Status: " << emp[i].get_leave_status() << "\n";
        }
        int targetId;
        cout << "\nEnter Employee ID to act upon: ";
        cin >> targetId;
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_id() == targetId)
            {
                int decision;
                cout << "1. Approve\n2. Reject\nChoice: ";
                cin >> decision;
                if (decision == 1)
                    emp[i].set_leave_request(true, "Approved");
                else if (decision == 2)
                    emp[i].set_leave_request(false, "Rejected");
                cout << "Decision recorded.\n";
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
            cout << "\n================ Leave Management ================" << endl;
            cout << "1. Apply Leave" << endl;
            cout << "2. View Leave Status" << endl;
            cout << "3. Manage Leave (Approve/Reject)" << endl;
            cout << "4. Back" << endl;
            cout << "\nEnter Your Choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                applyLeave();
                break;
            case 2:
                viewLeaveStatus();
                break;
            case 3:
                manageLeave();
                break;
            case 4:
                return;
            default:
                cout << "Unknown selection.\n";
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
        cout << "========================================================================================================\n";
        cout << "                                         Employee Details:\n";
        cout << "========================================================================================================\n";
        cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(5) << "Age"
             << setw(10) << "Gender" << setw(15) << "Phone" << setw(28) << "Department"
             << setw(15) << "Designation" << setw(10) << "Salary" << setw(10) << "Year"
             << endl
             << endl;
    }

public:
    void searchByID()
    {
        int id;
        cout << "\nEnter Employee ID: ";
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
            cout << "\nEmployee not found.\n";
        system("pause");
    }

    void searchByName()
    {
        string name;
        bool found = false;
        cin.ignore();
        cout << "\nEnter Employee Name: ";
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
            cout << "\nEmployee not found.\n";
        system("pause");
    }

    void departmentReport()
    {
        string deptName;
        bool found = false;
        cin.ignore();
        cout << "\nEnter Department Name: ";
        getline(cin, deptName);
        deptName = toLower(deptName);
        cout << "\nEmployees in " << deptName << " Department:\n";
        for (int i = 0; i < empCount; i++)
        {
            if (emp[i].get_employee_department() == deptName)
            {
                cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(5) << "Age"
             << setw(10) << "Gender" << setw(12) << "Phone" << setw(25) << "Department"
             << setw(25) << "Designation" << setw(10) << "Salary" << setw(10) << "Year"
             << endl
             << endl;
                emp[i].view_employee();
                found = true;
            }
        }
        if (!found)
            cout << "\nNo employees found in this department.\n";
        system("pause");
    }

    void highestPaidEmployee()
    {
        if (empCount == 0)
        {
            cout << "\nNo employees available.\n";
            return;
        }
        int maxIdx = 0;
        for (int i = 1; i < empCount; i++)
        {
            if (stoi(emp[i].get_employee_salary()) > stoi(emp[maxIdx].get_employee_salary()))
                maxIdx = i;
        }
        cout << "\nHighest Paid Employee:\n";
        emp[maxIdx].view_employee();
        system("pause");
    }

    void totalEmployees()
    {
        cout << "\nTotal Employees: " << empCount << endl;
        system("pause");
    }

    // Override showMenu() from Manager base  <-- INHERITANCE USED
    void showMenu() override
    {
        int choice;
        do
        {
            cout << "\n================ Reports & Search ================" << endl;
            cout << "1. Search Employee by ID" << endl;
            cout << "2. Search Employee by Name" << endl;
            cout << "3. Department Report" << endl;
            cout << "4. Highest Paid Employee" << endl;
            cout << "5. Total Employees" << endl;
            cout << "6. Back" << endl;
            cout << "\nEnter Your Choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                searchByID();
                break;
            case 2:
                searchByName();
                break;
            case 3:
                departmentReport();
                break;
            case 4:
                highestPaidEmployee();
                break;
            case 5:
                totalEmployees();
                break;
            case 6:
                return;
            default:
                cout << "\nInvalid Choice.\n";
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
        adminUsername = "waleed";
        adminPassword = "1234";
        isLoggedIn = false;
    }

    bool login()
    {
        string username, password;
        int choice;
        do
        {
            cout << "\n================ Admin Login ================" << endl;
            cout << "1. Login" << endl;
            cout << "2. Exit" << endl;
            cout << "Enter Your Choice: ";
            cin >> choice;

            if (choice == 1)
            {
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;

                if (username != adminUsername)
                    cout << "\nInvalid Username.\n";
                else if (password != adminPassword)
                    cout << "\nInvalid Password.\n";
                else
                {
                    isLoggedIn = true;
                    cout << "\nLogin Successful!\n";
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
            cout << "\n=======================================" << endl;
            cout << "      Employee Management System" << endl;
            cout << "=======================================" << endl;
            cout << "1. Employee Management" << endl;
            cout << "2. Department Management" << endl;
            cout << "3. Attendance Management" << endl;
            cout << "4. Payroll Management" << endl;
            cout << "5. Leave Management" << endl;
            cout << "6. Reports & Search" << endl;
            cout << "7. Exit" << endl;
            cout << "\nPlease select an option: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                empMgr.showMenu();
                break;
            case 2:
                deptMgr.showMenu();
                break;
            case 3:
                attnMgr.showMenu();
                break;
            case 4:
                payMgr.showMenu();
                break;
            case 5:
                leaveMgr.showMenu();
                break;
            case 6:
                reportMgr.showMenu();
                break;
            case 7:
                cout << "Exiting!\n";
                exit(0);
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 7);
    }
};

int main()
{
    MenuSystem system;
    system.run();
    return 0;
}