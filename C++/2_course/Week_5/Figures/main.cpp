#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

class Figure
{
public:
    Figure(const string& s) : name_(s){}

    virtual string Name() const=0;
    virtual double Perimeter() const=0;
    virtual double Area() const=0;
    const string name_;
protected:
    double perimeter_, area_;
};

class Rect : public Figure
{
public:
    Rect(const string& s, int wight, int height) : Figure(s), wight_(wight), height_(height){
        perimeter_ = 2*(wight_+height_);
        area_ = wight_*height_;
    }
    string Name() const override{
        return name_;
    }
    double Perimeter() const override{
        return perimeter_;
    }
    double Area() const override{
        return area_;
    }
    const int wight_, height_;
};

class Triangle : public Figure
{
public:
    Triangle(const string& s, int a, int b, int c) : Figure(s), a_(a), b_(b), c_(c){
        perimeter_ = a_+b_+c_;
        area_ = sqrt(perimeter_/2*(perimeter_/2-a_)*(perimeter_/2-b_)*(perimeter_/2-c_));
    }
    string Name() const override{
        return name_;
    }
    double Perimeter() const override{
        return perimeter_;
    }
    double Area() const override{
        return area_;
    }
    const int a_, b_, c_;
};

class Circle : public Figure
{
public:
    Circle(const string& s, int r) : Figure (s), radius_(r){
        double pi = 3.14;
        perimeter_ = 2*pi*radius_;
        area_ = pi*radius_*radius_;
    }
    string Name() const override{
        return name_;
    }
    double Perimeter() const override{
        return perimeter_;
    }
    double Area() const override{
        return area_;
    }
    const int radius_;
};

shared_ptr<Figure> CreateFigure(istringstream& is)
{
    string name_;
    shared_ptr<Figure> figure;
    is >> name_;
    if(name_ == "RECT")
    {
        int wight, height;
        is >> wight >> height;
        figure = make_shared<Rect>("RECT", wight, height);
    }else if (name_ == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        figure = make_shared<Triangle>("TRIANGLE", a, b, c);

    }else if (name_ == "CIRCLE") {
        int r;
        is >> r;
        figure = make_shared<Circle>("CIRCLE", r);
    }
    return figure;
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
