#include<iostream>
#include<cmath>
#include<vector>
#include <iomanip>
using namespace std;
class Point {
protected:
	std::vector<double>mCoordinates;
	double mDistance;
	friend class Point2D;
	friend class Point3D;
	friend class Point4D;
public:
	virtual void print() = 0;
	virtual void calculateDistance() = 0;
	virtual Point* multiply(Point* p) = 0;
	virtual vector<double> getCoordonates()
	{
		return mCoordinates;
	}
	double getDistance() {
		return mDistance;
	}
};
class Point4D :public Point {
public:
	Point4D() {
		mCoordinates.push_back(0);
		mCoordinates.push_back(0);
		mCoordinates.push_back(0);
		mCoordinates.push_back(0);
		mDistance = 0;
	}
	Point4D(double a, double b, double c, double d) {
		mCoordinates.push_back(a);
		mCoordinates.push_back(b);
		mCoordinates.push_back(c);
		mCoordinates.push_back(d);
		mDistance = mDistance;
	}
	virtual void print() {

		printf("%.3lf+%.3lf", mCoordinates[0], mCoordinates[1]);
		printf("i+%.3lfj+%.3lfk -> ", mCoordinates[2], mCoordinates[3]);
		printf("%.3lf", mDistance);
	}
	virtual void calculateDistance() {
		double suma = 0;
		for (int i = 0; i < mCoordinates.size(); i++) {
			suma = suma + pow(mCoordinates[i], 4);
		}
		mDistance = pow(suma, 1 / 4.);
	}
	virtual Point* multiply(Point* param) override
	{
		vector<double> ndPointCoordinates = param->getCoordonates();
		vector<double> coord;
		for (int i = 0; i < mCoordinates.size(); i++)
		{
			coord.push_back(0);
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < ndPointCoordinates.size(); j++)
			{
				if (i == 0)
				{
					double aux = mCoordinates[i] * ndPointCoordinates[j];
					coord[j] += aux;
				}
				if (i != 0 && i != j)
				{
					if (j == 0)
					{
						double aux = mCoordinates[i] * ndPointCoordinates[j];
						coord[i] += aux;
					}
				}
				if (i != 0 && i == j)
				{
					double aux = mCoordinates[i] * ndPointCoordinates[j] * (-1);
					coord[0] += aux;
				}
			}
		}
		Point4D* result = new Point4D(coord[0], coord[1], coord[2], coord[3]);
		return result;
	}
};
class Point2D :public Point {
public:
	Point2D() {
		mCoordinates.push_back(0);
		mCoordinates.push_back(0);
		mDistance = 0;
	}
	Point2D(double a, double b) {
		mCoordinates.push_back(a);
		mCoordinates.push_back(b);
	}
	virtual void print() {
		printf("%.3lf+%.3lfi -> ", mCoordinates[0], mCoordinates[1]);
		printf("%.3lf", mDistance);
	}
	virtual void calculateDistance() {
		double suma = 0;
		for (int i = 0; i < mCoordinates.size(); i++) {
			suma = suma + mCoordinates[i] * mCoordinates[i];
		}
		mDistance = sqrt(suma);
	}
	virtual Point* multiply(Point* param) override
	{
		vector<double> ndPointCoordinates = param->getCoordonates();
		vector<double> coord;
		for (int i = 0; i < mCoordinates.size(); i++)
		{
			coord.push_back(0);
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (i == 0)
				{
					double aux = mCoordinates[i] * ndPointCoordinates[j];
					coord[j] += aux;
				}
				if (i != 0 && i != j)
				{
					if (j == 0)
					{
						double aux = mCoordinates[i] * ndPointCoordinates[j];
						coord[i] += aux;
					}
				}
				if (i != 0 && i == j)
				{
					double aux = mCoordinates[i] * ndPointCoordinates[j] * (-1);
					coord[0] += aux;
				}
			}
		}
		Point2D* result = new Point2D(coord[0], coord[1]);
		return result;
	}
};
class Point3D :public Point {
public:
	Point3D() {
		mCoordinates.push_back(0);
		mCoordinates.push_back(0);
		mCoordinates.push_back(0);
		mDistance = 0;
	}
	Point3D(double a, double b, double c) {
		mCoordinates.push_back(a);
		mCoordinates.push_back(b);
		mCoordinates.push_back(c);
		mDistance = mDistance;
	}
	virtual void print() {
		printf("%.3lf+%.3lf", mCoordinates[0], mCoordinates[1]);
		printf("i+%.3lfj -> ", mCoordinates[2]);
		printf("%.3lf", mDistance);
	}
	virtual void calculateDistance() {
		double suma = 0;
		for (int i = 0; i < mCoordinates.size(); i++) {
			suma = suma + pow(mCoordinates[i], 3);
		}
		mDistance = pow(suma, 1 / 3.);
	}
	virtual Point* multiply(Point* param) override
	{
		vector<double> ndPointCoordinates = param->getCoordonates();
		vector<double> coord;
		for (int i = 0; i < 3; i++)
		{
			coord.push_back(0);
		}
		for (int i = 0; i < mCoordinates.size(); i++)
		{
			for (int j = 0; j < ndPointCoordinates.size(); j++)
			{
				if (i == 0)
				{
					double aux = mCoordinates[i] * ndPointCoordinates[j];
					coord[j] += aux;
				}
				if (i != 0 && i != j)
				{
					if (j == 0)
					{
						double aux = mCoordinates[i] * ndPointCoordinates[j];
						coord[i] += aux;
					}
				}
				if (i != 0 && i == j)
				{
					double aux = mCoordinates[i] * ndPointCoordinates[j] * (-1);
					coord[0] += aux;
				}
			}
		}
		Point3D* result = new Point3D(coord[0], coord[1], coord[2]);
		return result;
	}

};
//bool comparator(Point* a, Point* b){
// return a->getDistance()>b->getDistance();
//}
int main() {
	char d;
	std::vector<Point*> p, x;
	double p1, p2, p3, p4;
	while (std::cin >> p1) {
		d = getchar();
		std::cin >> p2;
		d = getchar();
		if (d == ';') {
			std::cin >> p3;
			d = getchar();
			if (d == ';') {



				std::cin >> p4;
				p.push_back(new Point4D(p1, p2, p3, p4));
			}
			else
				p.push_back(new Point3D(p1, p2, p3));



		}
		else p.push_back(new Point2D(p1, p2));
	}
	for (auto i : p) {



		for (auto j : p) {
			if (j != i) {
				x.push_back(i->multiply(j));
			}
		}
	}
	for (auto i : x) {
		i->calculateDistance();
	}
	double ok = 0;
	for (auto i : x) {


		if (i->getDistance() > ok) ok = i->getDistance();
	}
	for (auto i : x) {
		if (i->getDistance() == ok) {
			i->print();




		}
	}
	return 0;
}
