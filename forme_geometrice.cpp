#include<iostream>
#include<cstdio>
#include<string.h>
#include<algorithm>
#include<string>
#include<vector>
#include<cmath>
#include <iomanip>
#define PI
using namespace std;
class Shape {
protected:
    string mShape;
    float mArea;
public:
    virtual void print() = 0;
    virtual void calculateArea() = 0;
    float getArea() {
        return mArea;
    }
};
class Circle :public Shape {
private:
    float mRadius;
public:
    Circle() {
        this->mRadius = 0;
        this->mShape = "nedefinit";
    }
    Circle(float mRadius) {
        this->mRadius = mRadius;
        this->mShape = "cerc";
    }
    virtual void calculateArea() {
        mArea = M_PI * mRadius * mRadius;
        // return mArea;
    }
    virtual void print() {
        cout << mShape << " " << mRadius;
    }

};
class Rectangle :public Shape {
private:
    float mLength, mWidth;
public:
    Rectangle() {
        this->mLength = 0;
        this->mWidth = 0;
        this->mShape = "nedefinit";
    }
    Rectangle(float mLength, float mWidth) {
        this->mLength = mLength;
        this->mWidth = mWidth;
        this->mShape = "dreptunghi";
    }
    virtual void calculateArea() {
        mArea = mLength * mWidth;
        // return mArea;
    }
    virtual void print() {
        cout << mShape << " " << mLength << " " << mWidth;
    }

};
class Square :public Shape {
private:
    float mLength;
public:
    Square() {
        this->mLength = 0;
        this->mShape = "nedefinit";
    }
    Square(float mLength) {
        this->mLength = mLength;
        this->mShape = "patrat";
    }
    virtual void calculateArea() {
        mArea = mLength * mLength;
        //return mArea;
    }
    virtual void print() {
        cout << mShape << " " << mLength;
    }

};
bool comparator(Shape* a, Shape* b) {
    return a->getArea() > b->getArea();
}
int main() {
    vector<Shape*>v;
    string mShape;
    float mLength, mWidth;
    int nr, i;
    cin >> nr;
    while (nr > 0) {
        cin >> mShape;
        if (mShape == "patrat") {
            cin >> mLength;
            v.push_back(new Square(mLength));
        }
        if (mShape == "dreptunghi") {
            cin >> mLength >> mWidth;
            v.push_back(new Rectangle(mLength, mWidth));
        }
        if (mShape == "cerc") {
            cin >> mLength;
            v.push_back(new Circle(mLength));
        }
        nr--;
    }
    for (auto it : v) {
        // if(it->getShape=="patrat")
        it->calculateArea();
    }
    sort(v.begin(), v.end(), comparator);
    for (auto it : v) {
        cout << fixed << setprecision(2);
        it->print();
        cout << endl;
    }

    return 0;
}
