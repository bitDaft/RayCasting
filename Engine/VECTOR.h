#pragma once


class VECTOR2D
{
private:
	double m_Vx;
	double m_Vy;

	double dist;

	double calculateDist();

public:
	VECTOR2D operator+(const VECTOR2D & vec) const;
	VECTOR2D operator-(const VECTOR2D & vec) const;
	VECTOR2D operator*(const double & scale) const;
	VECTOR2D operator/(const double & scale) const;
	VECTOR2D & operator=(const VECTOR2D & vec) = default;
	
	VECTOR2D Dot(const VECTOR2D & vecB) const;

	double getX() const ;
	double getY() const ;
	double getDistance() const;
	VECTOR2D getUnitVector() const;

	VECTOR2D() = delete;
	VECTOR2D(const VECTOR2D &) = default;
	VECTOR2D(const double &, const double &);
	~VECTOR2D();
};

