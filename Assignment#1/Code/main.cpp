#include <iostream>
#include <fstream>
#include <strstream>
#include <algorithm>
#include <cstring>
using namespace std;
char delimiter = '|';
string Key;
fstream employee;
string TDept_ID;
string Tdepartment_name;
string TDept_Manger;

struct Employee
{
    char Employee_ID[13]; //primary key
    char Dept_ID[30];//secondary key
    char Employee_Name[50];
    char Employee_Position[50];
};
struct PrimaryIndex_Employee
{
    int offset;
    char Employee_ID[10];
    bool operator<(const PrimaryIndex_Employee &r) const { // for the sort function
		return strcmp(Employee_ID, r.Employee_ID) < 0;}
};
struct SecondryIndex
{
    char Dept_ID[30];
    bool operator<(const SecondryIndex &r) const
    {
        // for the sort function
        if (strcmp(Dept_ID, r.Dept_ID) == 0)
        return strcmp(Dept_ID, r.Dept_ID) < 0;
    }
};


void  primarySortingEmployees(string filename)
{
    string statement;
    int size(0);
    int index[100];

    fstream file("primaryEmployees.txt",ios::in);
    file.seekg(0,ios::beg);

    while(getline(file,statement))
    {
        size++;
    }

    file.clear();
    file.seekg(0,ios::beg);

    for(int i=0; i<size; i++)
    {
        file>>index[i];
    }
    for(int a = 0; a < size; a++)
    {
        for(int b=a+1; b<size; b++)
        {
            if(index[b]<index[a])
            {
                int tmp;
                tmp=index[a];
                index[a]=index[b];
                index[b]=tmp;
            }
        }
    }
    file.close();

    file.open("primaryEmployees.txt",ios::out | ios::trunc);

    for(int i=0; i<size; i++)
    {
        file<<index[i]<<endl;
    }
    file.close();
}
void  primarySortingdepartments(string filename)
{
    string statement;
    int size(0);
    int index[100];
    fstream file("primaryDepartment.txt",ios::in);
    file.seekg(0,ios::beg);
    while(getline(file,statement))
    {
        size++;
    }
    file.clear();
    file.seekg(0,ios::beg);

    for(int i=0; i<size; i++)
    {
        file>>index[i];
    }
    for(int x = 0; x < size; x++)
    {
        for(int y=x+1; y<size; y++)
        {
            if(index[y]<index[x])
            {
                int tmp;
                tmp=index[x];
                index[x]=index[y];
                index[y]=tmp;
            }
        }
    }
    file.close();

    file.open("primaryDepartment.txt",ios::out | ios::trunc);

    for(int i=0; i<size; i++)
    {
        file<<index[i]<<endl;
    }

    file.close();
}
void sort_secondary(string filename)
{
    struct record
    {
        int primary_index;
        string secondary_index;
    } index[100];

    string statement;
    int size(0);
    fstream DPI(filename, ios::in);
    DPI.seekg(0, ios::beg);

    while (getline(DPI, statement))
    {
        size++;
    }

    DPI.clear();
    DPI.seekg(0, ios::beg);

    for (int i = 0; i < size; i++)
    {
        DPI >> index[i].primary_index >> index[i].secondary_index;
    }

    for (int x = 0; x < size; x++)
    {
        for (int y = x + 1; y < size; y++)
        {
            if (index[y].primary_index < index[x].primary_index)
            {
                int tmp1;
                string	tmp2;

                tmp1 = index[x].primary_index;
                tmp2 = index[x].secondary_index;

                index[x].primary_index = index[y].primary_index;
                index[x].secondary_index = index[y].secondary_index;

                index[y].primary_index = tmp1;
                index[y].secondary_index = tmp2;
            }
        }
    }

    DPI.close();

    DPI.open(filename, ios::out | ios::trunc);

    for (int i = 0; i < size; i++)
    {
        DPI << index[i].primary_index << "	" << index[i].secondary_index << endl;
    }

    DPI.close();
}
void addEmployee()
{
    fstream employeeFstream;
    employeeFstream.open("employee.txt", ios::out | ios::app);
    Employee e;
    int lengthIndicator=0;
    cout << "enter employee Name: \n";
    cin>>e.Employee_Name;
    int sum=0;
    for(int i=0; sum<50 ; i++)
    {
        if(e.Employee_Name[i]!='\0')
        {
            sum++;
        }
        else
        {
            break;
        }
    }
    lengthIndicator =lengthIndicator+sum;
    sum=0;

    cout << "enter employee ID:\n";
    cin>>e.Employee_ID;
    for(int i=0; sum<13 ; i++)
    {
        if(e.Employee_ID[i]!='\0')
        {
            sum++;
        }
        else
        {
            break;
        }
    }
    lengthIndicator=lengthIndicator+sum;
    sum =0;
    string x =(string)e.Employee_ID;
    for(int i=0; sum<50 ; i++)
    {
        if(e.Dept_ID[i]!='\0')
        {
            sum++;
        }
        else
        {
            break;
        }
    }
    lengthIndicator=lengthIndicator+sum;
    sum =0;
    cout << "enter Department Id \n";
    cin>>e.Dept_ID;
    for(int i=0; sum<50 ; i++)
    {
        if(e.Dept_ID[i]!='\0')
        {
            sum++;
        }
        else
        {
            break;
        }
    }
    lengthIndicator=lengthIndicator+sum;
    sum =0;

    cout << "enter employee position \n";
    cin>>e.Employee_Position;
    for(int i=0; sum<50 ; i++)
    {
        if(e.Employee_Position[i]!='\0')
        {
            sum++;
        }
        else
        {
            break;
        }
    }
    employee.open("employee.txt",ios::in);
    int offset;
    employee.seekg(0,ios::end);
    int check =employee.tellg() ;
    if(check==0)
    {
        offset=0;
    }
    else
    {
        employee.seekg(0,ios::end);
        offset=employee.tellg();

    }
    lengthIndicator=lengthIndicator+sum;
    lengthIndicator=lengthIndicator+4;
    sum =0;
    employeeFstream<<lengthIndicator;
    employeeFstream<<e.Employee_ID<<delimiter;
    employeeFstream<<e.Employee_Name<<delimiter;
    employeeFstream<<e.Dept_ID<<delimiter;
    employeeFstream<<e.Employee_Position<<delimiter;
    employeeFstream.close();

    // add employee in primary index table
    fstream primaryEmp("primaryEmployees.txt", ios::out  | ios::app );
    primaryEmp<<e.Employee_ID<<'|'<<offset<<'|'<<endl;
    primaryEmp.close();
    primarySortingEmployees("primaryEmployees.txt");
    // add employee in secondary index table
    cout<< "Employee Added successfully \n\n";
}

struct Department
{
    string Key;

    char Dept_ID[30];
    char department_name[50];
    char department_manager[50];
};
void addDepartment()
{
    Department d;
    int lengthIndicator=0;
    cout<<"enter your department id"<<endl;
    cin>>d.Dept_ID;
    int sum=0;
    for(int i=0; sum<50 ; i++)
    {
        if(d.Dept_ID[i]!='\0')
        {
            sum++;
        }
        else
        {
            break;
        }
    }
    lengthIndicator =lengthIndicator+sum;
    sum=0;
    cout<<"enter your department name"<<endl;
    cin>>d.department_name;
    for(int i=0; sum<50 ; i++)
    {
        if(d.department_name[i]!='\0')
        {
            sum++;
        }
        else
        {
            break;
        }
    }
    lengthIndicator =lengthIndicator+sum;
    sum=0;
    cout<<"enter your department manager"<<endl;
    cin>>d.department_manager;
    for(int i=0; sum<50 ; i++)
    {
        if(d.department_manager[i]!='\0')
        {
            sum++;
        }
        else
        {
            break;
        }
    }
    lengthIndicator +=sum;
    lengthIndicator+=3;
    sum=0;

    fstream dept;
    dept.open("department.txt",ios::out | ios::app);
    dept<<lengthIndicator<<d.Dept_ID<<delimiter<<d.department_name<<delimiter<<d.department_manager<<delimiter;
    dept.close();
    // adding department in primary index table
    fstream primaryEmp("primaryDepartment.txt", ios::out  | ios::app );
    primaryEmp<<d.Dept_ID<<lengthIndicator<<endl;
    primaryEmp.close();
    primarySortingdepartments("primaryDepartment.txt");
    // adding department in secondary index table
    cout<<"department added successfully"<<endl;
}

void deleteEmployee()
{
    fstream file;
    Employee e;
    string input;
    file.open("employee.text", ios::in | ios :: out);
    file.seekp(2, ios::beg);
    cout << "please enter the id of the employee : " << endl;
    cin >> input;
    if (input != e.Employee_ID)
    {
        file.put('*');
        cout<<"recored of employee "<<input<<" is deleted"<<endl;
    }
}
void deleteDepartment()
{
    fstream file;
    Employee e;
    string input;
    file.open("department.txt", ios::in | ios :: out);
    file.seekp(2, ios::beg);
    cout << "please enter the id of the department : " << endl;
    cin >> input;
    if (input != e.Employee_ID)
    {
        file.put('*');
        cout<<"recored of department "<<input<<" is deleted"<<endl;
    }
}
void PrintEmployee_id(fstream& stream, Employee& b, string Employee_ID)
{
	stream.seekg(4, ios::beg);
	while (!stream.eof()) {
		char buffer[100];
		stream.read(buffer, 100);
		istrstream strbuf(buffer);
		strbuf.getline(b.Employee_ID, 13, '|'); strbuf.getline(b.Dept_ID, 30, '|');
		strbuf.getline(b.Employee_Name, 31, '|'); strbuf.getline(b.Employee_Position, 50, '|');
		if (b.Employee_ID == Employee_ID) {
			cout << "----------------------------------------\n";
			cout << "EMPLOYEE ID		: " << b.Employee_ID << "\n";
			cout << "DEPARTMENT ID		: " << b.Dept_ID << "\n";
			cout << "EMPLOYEE NAME		: " << b.Employee_Name << "\n";
			cout << "EMPLOYEE POSITION	: " << b.Employee_Position << "\n";
			cout << "----------------------------------------\n";
		}
	}
		cout << "not found" << endl;
		stream.seekg(0, ios::beg);
}
void PrintEmployee_Dept_ID(fstream& stream, Employee& b, string Dept_ID)
{  stream.seekg(4, ios::beg);
	while (!stream.eof()) {
		char buffer[100];
		stream.read(buffer, 100);
		istrstream strbuf(buffer);
		strbuf.getline(b.Employee_ID, 13, '|'); strbuf.getline(b.Dept_ID, 30, '|');
		strbuf.getline(b.Employee_Name, 31, '|'); strbuf.getline(b.Employee_Position, 50, '|');
		if (b.Dept_ID == Dept_ID) {
			cout << "----------------------------------------\n";
			cout << "EMPLOYEE ID		: " << b.Employee_ID << "\n";
			cout << "DEPARTMENT ID		: " << b.Dept_ID << "\n";
			cout << "EMPLOYEE NAME		: " << b.Employee_Name << "\n";
			cout << "EMPLOYEE POSITION	: " << b.Employee_Position << "\n";
			cout << "----------------------------------------\n";
		}
	}
		cout << "not found" << endl;
		stream.seekg(0, ios::beg);
}
void PrintDepartment_id(fstream& stream, Department& b, string Dept_ID)
{
	stream.seekg(4, ios::beg);
	while (!stream.eof()) {
		char buffer[100];
		stream.read(buffer, 100);
		istrstream strbuf(buffer);
		strbuf.getline(b.Dept_ID, 30, '|'); strbuf.getline(b.department_name, 50, '|');
		strbuf.getline(b.department_manager, 50, '|');
		if (b.Dept_ID == Dept_ID) {
			cout << "----------------------------------------\n";
			cout << "DEPARTMENT ID		: " << b.Dept_ID << "\n";
			cout << "DEPARTMENT NAME		: " << b.department_name << "\n";
			cout << "MANAGER NAME	: " << b.department_manager << "\n";
			cout << "----------------------------------------\n";
		}
	}
		cout << "not found" << endl;
		stream.seekg(0, ios::beg);
}
void PrintDepartment_name(fstream& stream, Department& b, string name)
{
	stream.seekg(4, ios::beg);
	while (!stream.eof()) {
		char buffer[100];
		stream.read(buffer, 100);
		istrstream strbuf(buffer);
		strbuf.getline(b.Dept_ID, 30, '|'); strbuf.getline(b.department_name, 50, '|');
		strbuf.getline(b.department_manager, 50, '|');
		if (b.department_name == name) {
			cout << "----------------------------------------\n";
			cout << "DEPARTMENT ID		: " << b.Dept_ID << "\n";
			cout << "DEPARTMENT NAME		: " << b.department_name << "\n";
			cout << "MANAGER NAME	: " << b.department_manager << "\n";
			cout << "----------------------------------------\n";
		}
	}
	cout << "not found" << endl;
	stream.seekg(0, ios::beg);
}
/*PrimaryIndex_Employee* loadprimaryindex()
{
    fstream fileee;
    fileee.open("primaryEmployees.txt", ios::in|ios::app);
    PrimaryIndex_Employee obj;
    PrimaryIndex_Employee arr[10];
    int i=0;
    while(!fileee.eof())
    {
        getline(fileee,&obj.Employee_ID,'|');
        getline(fileee,string(obj.offset),'|');
        getline(fileee,char(obj.offset),'|');
        arr[i]=obj;
        1i++;
    }
}*/
Employee SearchById(const string& ID)
{
    fstream file,PrimIndex;
    file.open("Employees.txt",ios::in);
    PrimIndex.open("EPrimary.txt",ios::in);
    void readEmployee(fstream & f)
    {   short length;
        f.read((char*)&length, sizeof(length));
        char * record = new char[length];
        f.read(record,length);
        istrstream strbuf(record);
        strbuf>>*this;
    }
    Employee employee{};
    int byteOffset;
    byteOffset= GetRecordPosition(PrmIndexArray,EmpCont,ID);
    char c;
    if(byteOffset!=0)
    {
        file.seekp(byteOffset-1,ios::beg);
    }
    file.get(c);
    if(c=='*' || byteOffset == -1)
    {
        cout<<"Not Found\n";
    }
    else
    {
        file.seekg(byteOffset, ios::beg);
        employee.readEmployee(file);
    }
    file.close();
    PrimIndex.close();
    return employee;
}
void WriteQuery(string message) {}
int main()
{
    int n=0;
    int choice;
    char check='y';
    do
    {
        cout<<"1- ADD NEW EMPLOYEE"<<endl;
        cout<<"2- ADD NEW DEPARTMENT"<<endl;
        cout<<"3- DELETEDELETE EMPLOYEE"<<endl;
        cout<<"4- DELETE DEPARTMENT "<<endl;
        cout<<"5- PRINT EMPLOYEE(ID)"<<endl;
        cout<<"6- PRINT EMPLOYEE(Dept_ID) "<<endl;
        cout<<"7- PRINT DEPARTMENT(ID) "<<endl;
        cout<<"8- PRINT DEPARTMENT(NAME) "<<endl;
        cout<<"9- WRITE A QUERY "<<endl;
        cout<<"10- EXIT"<<endl;
        cout<<"enter number of operation you want:"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            addEmployee();
            break;
        case 2:
            addDepartment();
            break;
        case 3:
            deleteEmployee();
            break;
        case 4:
            deleteDepartment();
        case 5:
            PrintEmployee_id(fstream& stream, Employee& b, string Employee_ID);
        case 6:
            PrintEmployee_Dept_ID(fstream& stream, Employee& b, string Dept_ID);
        case 7:
            PrintDepartment_id(fstream& stream, Department& b, string Dept_ID);
        case 8:
            PrintDepartment_name(fstream& stream, Department& b, string name);
        case 9:
            writeQuery();
        case 10:
            return 0;
        default:
            break;
        }
        cin.ignore();
        cout<<"Do you want to continue"<<endl;
        cin>>check;
        cin.ignore();
    }
    while(check=='y'||check=='Y');
    return 0;
}
