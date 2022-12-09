#include <iostream>
#include <string.h>
#include <tr1/memory>
#include <memory>
using namespace std;

class Uncopyable{
    protected:
        Uncopyable() {}
        ~Uncopyable() {}
    private:
        Uncopyable(const Uncopyable&); //prevent copying
        Uncopyable& operator = (const Uncopyable&);

};

class Employee {
    protected:
        string name;
        int age;
        bool emplLocked;
        

    public:
        //Employee constructor
        Employee(){};
        Employee(const string& name, const int& age, const bool& emplLocked):name(name),
                                                     age(age),
                                                     emplLocked(emplLocked){
           cout<<"This is an employee! NAME: "<<name<<"  AGE: "<<age<<endl;
         };
        //Deconstructor
        ~Employee(){
            cout<<"Fired employee!"<<endl;
        };

        //copy constructor
         Employee(const Employee& rhs):name(rhs.name),
                                      age(rhs.age),
                                      emplLocked(emplLocked){
                cout<<"!!Copy constructor!!"<<endl;                                            

            } 
        //copy assignment operator
         Employee& operator = (const Employee& rhs){ 
                if(this == &rhs)
                {
                    cout<<"Self asig"<<endl;
                    return *this;
                }
                name = rhs.name;
                age = rhs.age;
                emplLocked = rhs.emplLocked;
                
            return *this; 
            }

public:
        string getName(){
            return name;
        }

        void setName(string name){
            this->name= name;
        }

        int getAge(){
            return age;
        }

        void setAge(int age){
            this->age= age;
        }

        bool getEmplLocked(){
            return emplLocked;
        }

        void setEmplLocked(bool emplLocked){
            this->emplLocked = emplLocked;
        }


        void employeeToString(){
            cout<<"Employee: "<<name<<" Age: "<<age<<endl;
        }

};
    //
    
        Employee* createEmployee(const string& name, const int& age, const bool& emplLocked){
            Employee *employee = new Employee(name, age, emplLocked);
            return employee;
        }

        void lock(Employee& em){
            em.setEmplLocked(true);
            //cout<<"Blocked Employee!"<<endl;
        };

        void unlock(Employee& em){
            em.setEmplLocked(false);
            //cout<<"Unblocked Employee!"<<endl;
        };

        class Lock : private Uncopyable {
            private:
             Employee& employeePt;
            public:
             Lock(Employee& pt): employeePt(pt) {
                lock(employeePt);
             }
             ~Lock() {
                unlock(employeePt);
             }
        };

        void printANewEmployee(const string& name, const int& age, const bool& emplLocked){
            std::tr1::shared_ptr<Employee> printEm(createEmployee(name, age, emplLocked));
            printEm-> employeeToString();
        }

        // bool raiseSalary(const string& name, const int& age, const bool& emplLocked){
        //     std::tr1::shared_ptr<Employee> employee(createEmployee(name, age, emplLocked));
        //     if(age>30) {
                
        //         cout<<"Your salary has been raised!"<<endl;
        //         return 1;
        //     }
        //         else {
                    
        //             cout<<"Your salary will NOT be raised!"<<endl;
        //             return 0;
        //         }

        // }

//endl class };

class Sallary{
    private: int sal;
    public:
    Sallary(const int &sal):sal(sal){};

    int getSal(){
        return sal;
    }
};


class Teacher : public Employee{
    public:
            Teacher(){};
            Teacher(const string& name, const int& age, const bool& emplLocked):Employee(name, age, emplLocked){};
            ~Teacher(){};
            Teacher(const Teacher& rhs)= delete; //copy constructor
            Teacher& operator = (const Teacher& rhs)= delete; //copy assignment operator  
            
            void doWork(){
                cout<<name<<" is "<<age<<" years old and is working at school!"<<endl;
            }
     
          
};

class Doctor : public Employee{
    
    private:
        string name;
        int age;
        Sallary *sal;
    public:
            Doctor(){};
            Doctor(const string& name, const int& age, const bool& emplLocked):Employee(name, age, emplLocked){};
            Doctor(const string& name, const int& age, Sallary &sal): name(name),
                                                                      age(age),
                                                                      sal(new Sallary(sal)){};
            ~Doctor(){};
            Doctor(const Doctor& rhs):Employee(rhs.name,rhs.age, rhs.emplLocked){}; 
            
            Doctor& operator=(const Doctor& rhs){
                Sallary *pt= sal;
               
                sal=new Sallary(*rhs.sal);
                delete pt;
                return *this;
               
            }
            

            void doWork(){
            cout<<"I'm Doctor "<<name<<" and I'm "<<age<<" years old. Sallary:"<<sal[0].getSal()<<endl;
            }
            void doWork2(){
            cout<<"I'm Doctor "<<name<<" and I'm "<<age<<" years old."<<endl;
            }


};



int main()
{
    // Teacher teacher1("Dolores",34);
    // teacher1.doWork();

    // Employee e1("Andra",28);
    // Employee e2("Lucas", 35);
    // Sallary s1(4000);
    // Sallary s2(4500);
    // Doctor d1("Matei",39,s1);
    // Doctor d2("Sonia",46,s2);
    // d1.doWork();
    // d2.doWork();
    // Employee e3;
    // e3=e1;
    // cout<<e3.getName()<<"  "<<e3.getAge()<<endl;
    // cout<<"------"<<endl;
    // Employee e4=e2=e1;
    // cout<<e4.getName()<<"  "<<e4.getAge()<<endl;
    // cout<<"------"<<endl;
    // e1=e1;
    // cout<<e1.getName()<<"  "<<e1.getAge()<<endl;
    
    // unique_ptr<Employee> e1(createEmployee("Andreas", 36, true));
    // cout<<e1->getName()<<" "<<endl;
    // unique_ptr<Employee> e2(e1);
    // cout<<e2->getName()<<" "<<endl;


    cout<<"-----item13-------"<<endl;
    shared_ptr<Employee> e1(createEmployee("Andreas", 36, true));
    cout<<e1->getName()<<" "<<e1->getAge()<<" "<<e1->getEmplLocked()<<endl;
    shared_ptr<Employee> e2(e1); //both points to the same obj, this is not working with auto ptr
    cout<<e2->getName()<<" "<<e2->getAge()<<" "<<e2->getEmplLocked()<<endl;
    cout<<endl;
    cout<<"-----item14-------"<<endl;
    Employee e3("Andrada", 33, false);
    cout<<endl<<e3.getName()<<" "<<e3.getAge()<<" "<<e3.getEmplLocked()<<endl;
        //changing the name is a critical operation so we define this
    {
        Lock e_lock(e3); //lock the object
        cout<<"Employee loked= "<<e3.getEmplLocked()<<endl;

        e3.setName("Andra"); //change the name
        
    }

    cout<<"________"<<endl;
    cout<<"Employee loked= "<<e3.getEmplLocked()<<" "<<e3.getName()<<endl;
    cout<<"________"<<endl;


    


    return 0;
}