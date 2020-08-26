#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person
{
public:
    Person(const string& work, const string& name) : Name(name), Work(work){}
    virtual void Walk(string distantion) const
    {
        cout << Work << ": " << Name << " walks to: " << distantion << endl;
    }
    const string Name, Work;
};


class Student : public Person{
public:

    Student(string name, string favouriteSong) : Person ("Student", name), FavouriteSong(favouriteSong){
    }

    void Learn() const{
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(string destination) const override{
        cout << "Student: " << Name << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const{
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    const string FavouriteSong;
};


class Teacher : public Person{
public:

    Teacher(string name, string subject) : Person("Teacher", name), Subject(subject){
    }

    void Teach() const{
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }
    const string Subject;
};


class Policeman : public Person{
public:
    Policeman(string name) : Person("Policmen", name) {}

    void Check(Person& pers) const{
        cout << "Policeman: " << Name << " checks " << pers.Work << ". " << pers.Work << "'s name is: " << pers.Name << endl;
    }
};

void VisitPlaces(Person& pers, vector<string> places) {
    for (auto p : places) {
        pers.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
