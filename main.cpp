#include <iostream>
#include <vector>

struct Vector
{
	float x{}, y{}, z{};

	Vector operator-(const Vector& Rhs) const
	{
		return Vector{ x - Rhs.x, y - Rhs.y, z - Rhs.z };
	}

	float Size() const
	{
		return std::sqrtf(x * x + y * y + z * z);
	}

	Vector GetSafeNormal() const
	{
		if (Size() == NULL) return *this;

		float Scale = 1 / Size();
		return Vector{ x * Scale, y * Scale, z * Scale };
	}

	static float DotProduct(const Vector& Lhs, const Vector& Rhs)
	{
		return Rhs.x * Lhs.x + Rhs.y * Lhs.y + Rhs.z * Lhs.z;
	}

	static Vector CrossProduct(const Vector& Lhs, const Vector& Rhs)
	{
		return Vector{
			(Lhs.y * Rhs.z) - (Lhs.z * Rhs.y),
			(Lhs.z * Rhs.x) - (Lhs.x * Rhs.z),
			(Lhs.x * Rhs.y) - (Lhs.y * Rhs.x)
		};
	}
};

struct PlaneEquation
{
	Vector PointOnPlane;
	Vector PlaneNormal;

	bool IsPointOnPlane(const Vector& Point) const
	{
		float Dot = Vector::DotProduct(Point - PointOnPlane, PlaneNormal);
		Dot = std::abs(Dot);

		return Dot == 0.f;
	}
};

std::ostream& operator<<(std::ostream& cout, const Vector& Rhs)
{
	printf("< %.2f, %.2f, %.2f >", Rhs.x, Rhs.y, Rhs.z);
	return cout;
}


void GetEquationOfAPlane(const std::vector<Vector>& points, PlaneEquation& Equation)
{
	if (points.size() < 3) { std::cout << "Need three points to define a plane \n"; return; }

	Vector Edge1 = points.at(1) - points.at(0);
	Vector Edge2 = points.at(2) - points.at(0);

	Equation.PointOnPlane = points.at(0);
	Equation.PlaneNormal = Vector::CrossProduct( Edge1, Edge2).GetSafeNormal();
}
int main(void)
{
	//Three points to define a plane
	std::vector<Vector> PlanePoints{
		Vector{1, 0, 1},
		Vector{0, 1, 0},
		Vector{0, 0, 0}
	};

	PlaneEquation Equation;
	GetEquationOfAPlane(PlanePoints, Equation);

	std::cout << std::boolalpha;

	std::cout << Equation.IsPointOnPlane(Vector{ 10, 0, 10 });
	
	return 0;
}
