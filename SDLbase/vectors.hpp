#ifndef ROGUELIKE_VECTOR2_H
#define ROGUELIKE_VECTOR2_H

#include <string>

template <typename T>
struct Vector2 {
	T x, y;

	Vector2() : x(T()), y(T()) {}
	Vector2(T x1, T y1) : x(x1), y(y1) {}
	Vector2(const Vector2& other) {
		x = other.x;
		y = other.y;
	}

	Vector2 operator+(const Vector2& a) {
		return Vector2(a.x + x, a.y + y);
	}

	Vector2 operator-(const Vector2& a) {
		return Vector2(x - a.x, y - a.y);
	}

	Vector2 operator*(const T a) {
		return Vector2(x * a, y * a);
	}

	bool operator==(Vector2& a) {
		return (a.x == x && a.y == y);
	}

	Vector2& operator=(const Vector2& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	std::string to_string() {
	    if (std::is_same<T, int>::value || std::is_same<T, float>::value) {
            return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
	    }
	}
};

#endif
