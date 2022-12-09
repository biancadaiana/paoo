#include <iostream>
#include <string.h>
using namespace std;

class Employee {
    protected:
        string name;
        int age;

    public:
        //Employee constructor
        Employee(){};
        Employee(const string& name, const int& age);
        ~Employee();

        string getName(){
            return name;
        }

    private:
        Employee(const Employee&);
        Employee& operator = (const Employee&);

};

//Employee constructor implementation
Employee::Employee(const string& name, const int& age)
        :name(name),
         age(age)
         {
            cout<<"This is an employee!"<<endl;
         }

//Employee deconstructor implementation
Employee::~Employee(){
    cout<<"Fired employee!"<<endl;
}

class Teacher : public Employee{
    public:
            string subject;
            Teacher(){};
            Teacher(const string& name, const int& age, string subject): subject(subject),
                                                                        Employee(name, age){};
            ~Teacher(){};
            
            void doWork(){
                cout<<name<<" is theaching "<<subject<<" at school!"<<endl;
            }
};

class Doctor : public Employee{
    public:
            string speciality;
            Doctor(){};
            Doctor(const string& name, const int& age, string speciality): speciality(speciality),
                                                                            Employee(name, age){};
            ~Doctor(){};

            void doWork(){
            cout<<"I'm Doctor "<<name<<" and I'm specialized in "<<speciality<<"! "<<endl;
            }


};


int main()
{
    Teacher teacher1("Dolores",34, "Biology");
    teacher1.doWork();

    Doctor dr1("Wilson", 43, "Neurology");
    dr1.doWork();

    Doctor dr2("Wiliams", 39, "Cardiology");
    dr2.doWork();

    // Doctor d2;
    // d2=dr1;
    // d2.doWork();

    // Teacher t2;
    // t2=teacher1;
    // t2.doWork();


    return 0;
}