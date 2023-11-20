#pragma once
#include <iostream>
#include <complex>
#include <stdexcept>
#include <cmath>
#include <random>
#define PI 3.14
#define e 0.0001
using namespace std;

template<typename T>
struct Point {
	T x;
	T y;
	Point() : x(0), y(0) {}
	Point(T _x, T _y) : x(_x), y(_y) {}
	friend ostream& operator<<(ostream& os, const Point<T>& point) {
		os << "(" << point.x << ", " << point.y << ") ";
		return os;
	}
	bool& operator==(const Point<T>& other) {
		if (abs(this->x - other.x) < e and abs(this->y == other.y) < e)
			return true;
		else
			return false;
	}
};

template<typename T>
class Polyline {
	Point<T>* points;
	int size;
public:
	Polyline() : points(nullptr), size(0) {}
	Polyline(int _size) : size(_size) {
		if (_size < 0) {
			throw out_of_range("Index out of range");
		}
		points = new Point<T>[size];
	}
	Polyline(Polyline<T>& other) {
		size = other.size;
		points = new Point<T>[size];
		for (int i = 0; i < size; ++i)
		{
			points[i] = other[i];
		}
	}
	Polyline(int _size, const T& m1, const T& m2) : size(_size) {
		if (_size < 0) {
			throw out_of_range("Index out of range");
		}
		points = new Point<T>[size];
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<T> distrib(m1, m2);
		for (int i = 0; i < size; i++) {
			T randomX = distrib(gen);
			T randomY = distrib(gen);
			points[i] = Point<T>(randomX, randomY);
		}
	}
	~Polyline() {
		delete[] points;
	}

	friend ostream& operator<<(ostream& os, const Polyline<T>& polyline) {
		for (int i = 0; i < polyline.size; i++) {
			os << "(" << polyline.points[i].x << ", " << polyline.points[i].y << ") ";
		}
		return os;
	}
	bool& operator==(const Polyline<T>& other) {
		int k = 0;
		if (this->size != other->size)
			throw out_of_range("size must be ==");
		for (int i = 0; i < size; ++i) {
			if (this->points[i] == other->points[i])
				k++;
		}
		if (k == size)
			return true;
		else
			return false;
	}
};
template<typename T>
struct Point<complex<T>> {
	complex<T> x;
	complex<T> y;
	Point() : x(0.0), y(0.0) {}
	Point(complex<T> _x, complex<T> _y) : x(_x), y(_y) {}
	friend ostream& operator<<(ostream& os, const Point<complex<T>>& point) {
		os << "(" << point.x << ", " << point.y << ") ";
		return os;
	}
	bool& operator==(const Point<complex<T>>& other) {
		if ((abs(this->x.real() - other.x.real()) < e) and (abs(this->y.real()) - (other.y.real)) < e and (abs(this->x.imgl() - other.x.img()) < e) and (abs(this->y.img()) - (other.y.img())))
			return true;
		else
			return false;
	}
};

template<typename T>
class Polyline<complex<T>> {
	Point<complex<T>>* points;
	int size;
public:
	Polyline() : points(nullptr), size(0) {};
	Polyline(int _size) : size(_size) {
		if (_size < 0) {
			throw out_of_range("Index out of range");
		}
		points = new Point<complex<T>>[size];
	}
	Polyline(Polyline<complex<T>>& other) {
		size = other.size;
		points = new Point<complex<T>>[size];
		for (int i = 0; i < size; ++i) {
			points[i] = other[i];
		}
	}
	Polyline(int _size, const complex<T>& m1, const complex<T>& m2) : size(_size) {
		if (_size < 0) {
			throw out_of_range("Index out of range");
		}
		points = new Point<complex<T>>[size];
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<T> real_distrib(m1.real(), m2.real());
		//uniform_real_distribution<T> imag_distrib(m1.imag(), m2.imag());
		for (int i = 0; i < size; i++) {
			T random_X = real_distrib(gen);
			T randomX = real_distrib(gen);
			T random_Y = real_distrib(gen);
			T randomY = real_distrib(gen);
			points[i] = Point<complex<T>>(std::complex<T>(random_X, randomX), std::complex<T>(random_Y, randomY));
		}
	}
	~Polyline() {
		delete[] points;
	}

	void add(const Point<complex<T>>& point) {
		Point<complex<T>>* newElements = new Point<complex<T>>[size + 1];
		for (int i = 0; i < size; ++i) {
			newElements[i] = points[i];
		}
		newElements[size] = point;
		delete[] points;
		points = newElements;
		size += 1;
	}


	friend ostream& operator<<(ostream& os, const Polyline<complex<T>>& polyline) {
		for (int i = 0; i < polyline.size; i++) {
			os << "(" << polyline.points[i].x << ",  " << polyline.points[i].y << ") ";
		}
		return os;
	}

};

int main() {

	Polyline<int> polyline_int;
	Polyline<int> polyline_default;
	cout << "polyline_default: " << endl;
	cout << polyline_default << endl;

	Polyline<int> polyline_with_size(5);
	cout << "polyline_with_size: " << endl;
	cout << polyline_with_size << endl;

	Polyline<int> polyline_with_values(3, 1, 2);
	cout << "polyline_with_values: " << endl;
	cout << polyline_with_values << endl;

	Polyline<int> polyline_copy(polyline_with_values);
	cout << "polyline_copy: " << endl;
	cout << polyline_copy << endl;

	
	cout << "\n----------------------------------------------------" << endl;

	Point<complex<float>> complex_point1(complex<float>(1, 2), complex<float>(3, 4));
	cout << "complex_point1: " << endl;
	cout << complex_point1 << endl;

	Polyline<complex<float>> polyline_with_complex_values(2, complex<float>(-3, -4), complex<float>(1, 1));
	cout << "polyline_with_complex_values: " << endl;
	cout << polyline_with_complex_values << endl;

	Polyline<complex<float>> polyline_copy_complex(polyline_with_complex_values);
	cout << "polyline_copy_complex: " << endl;
	cout << polyline_copy_complex << endl;

	Point<complex<float>> complex_point2(complex<float>(1, 2), complex<float>(3, 4));
	polyline_copy_complex.add(complex_point2);
	cout << "polyline_add_complex_point: " << endl;
	cout << polyline_copy_complex << endl;

}