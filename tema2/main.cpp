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
        Employee(const string& name, const int& age):name(name),
                                                     age(age){
            cout<<"This is an employee! Name: "<<name<<"Age: "<<age<<endl;
         };
        //Deconstructor
        ~Employee(){
            cout<<"Fired employee!"<<endl;
        };

        //copy constructor
         Employee(const Employee& rhs):name(rhs.name),
                                      age(rhs.age){
                cout<<"!!Copy constructor!!"<<endl;                                            

            } 
        //copy assignment operator
         Employee& operator = (const Employee& rhs){ 
                if(this == &rhs)
                {
                    return *this;
                }
                name = rhs.name;
                age = rhs.age;
                
            return *this; 
            }

        string getName(){
            return name;
        }

        int getAge(){
            return age;
        }


};

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
            Teacher(const string& name, const int& age):Employee(name, age){};
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
            Doctor(const string& name, const int& age):Employee(name, age){};
            Doctor(const string& name, const int& age, Sallary &sal): name(name),
                                                                      age(age),
                                                                      sal(new Sallary(sal)){};
            ~Doctor(){};
            Doctor(const Doctor& rhs):Employee(rhs.name,rhs.age){}; 
            
            Doctor& operator=(const Doctor& rhs){
                Sallary *pt= sal;
                sal=new Sallary(*rhs.sal);
                delete pt;
                return *this;
               
            }
            

            void doWork(){
            cout<<"I'm Doctor "<<name<<" and I'm "<<age<<" years old. Sallary:"<<sal[0].getSal()<<endl;
            }


};



int main()
{
    // Teacher teacher1("Dolores",34);
    // teacher1.doWork();

    Employee e1("Andra",28);
    Employee e2("Lucas", 35);
    Sallary s1(4000);
    Sallary s2(4500);
    Doctor d1("Matei",39,s1);
    Doctor d2("Sonia",46,s2);
    d1.doWork();
    d2.doWork();
    Employee e3;
    e3=e1;
    cout<<e3.getName()<<"  "<<e3.getAge()<<endl;
    Employee e4=e1;
    cout<<e4.getName()<<"  "<<e3.getAge()<<endl;



   
    return 0;
}