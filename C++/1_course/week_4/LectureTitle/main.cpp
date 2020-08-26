#include <iostream>
#include <string>

using namespace std;

struct Specialization {
    string value;
    explicit Specialization(string new_value) {
        value = new_value;
    }
};
struct Course {
    string value;
    explicit Course(string new_value) {
        value = new_value;
    }
};
struct Week {
    string value;
    explicit Week(string new_value) {
        value = new_value;
    }
};

struct LectureTitle {
    string specialization;
    string course;
    string week;
    explicit LectureTitle(Specialization spec, Course cou, Week wee)
    {
        specialization=spec.value;
        course=cou.value;
        week=wee.value;
    }

};


int main()
{
    LectureTitle title(
        Specialization("C++"),
        Course("White belt"),
        Week("4th")
    );

    cout << "Hello World!" << endl;
    return 0;
}
