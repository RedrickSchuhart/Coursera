#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human() {

    }

    string getName() const {
        return Name;
    }

    string getType() const {
        return Type;
    }

    void setName(const string& n) {
        Name = n;
    }

    void setType(const string& t) {
        Type = t;
    }

    virtual void Walk(const string& s) const = 0;

private:
    string Name;
    string Type;
};

class Student : public Human {
public:

    Student(string name, string favouriteSong) : FavouriteSong(favouriteSong){
        setName(name);
        setType("Student");
    }

    void Learn() const {
        cout << getType() << ": " << getName() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        cout << getType() << ": " << getName() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        cout << getType() << ": " << getName() << " sings a song: " << getFavouriteSongName() << endl;
    }

    string getFavouriteSongName() const {
        return FavouriteSong;
    }

private:
    const string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(string name, string subject) : Subject(subject){
        setName(name);
        setType("Teacher");
    }

    void Teach() const {
        cout << getType() << ": " << getName() << " teaches: " << getSubgect() << endl;
    }

    void Walk(const string& destination) const override {
        cout << getType() << ": " << getName() << " walks to: " << destination << endl;
    }

    string getSubgect() const {
        return Subject;
    }

private:
    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(string name) {
        setName(name);
        setType("Policeman");
    }

    void Check(Human& h) const {
        cout << getType() << ": " << getName() << " checks " << h.getType() << ". " << h.getType() << "'s name is: " << h.getName() << endl;
    }

    void Walk(const string& destination) const override {
        cout << getType() << ": " << getName() << " walks to: " << destination << endl;
    }

};


void VisitPlaces(Human& h, vector<string> places) {
    for (auto p : places) {
        h.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}
