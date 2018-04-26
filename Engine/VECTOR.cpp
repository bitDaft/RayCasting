#include "VECTOR.h"

#include <cmath>

double VECTOR2D::calculateDist()
{
	return std::sqrt(m_Vx*m_Vx+m_Vy*m_Vy);
}

VECTOR2D VECTOR2D::operator+(const VECTOR2D & vec) const
{
	return VECTOR2D((m_Vx + vec.m_Vx), (m_Vy + vec.m_Vy));
}

VECTOR2D VECTOR2D::operator-(const VECTOR2D & vec) const
{
	return VECTOR2D((m_Vx - vec.m_Vx), (m_Vy - vec.m_Vy));
}

VECTOR2D VECTOR2D::operator*(const double & scale) const
{
	return VECTOR2D((m_Vx*scale),(m_Vy*scale));
}

VECTOR2D VECTOR2D::operator/(const double & scale) const
{
	return VECTOR2D((m_Vx/scale), (m_Vy/scale));
}

double VECTOR2D::Dot(const VECTOR2D & b) const
{
	return ((m_Vx * b.m_Vx) + (m_Vy * b.m_Vy));
}

double VECTOR2D::getX() const
{
	return m_Vx;
}

double VECTOR2D::getY() const
{
	return m_Vy;
}

double VECTOR2D::getDistance() const
{
	return dist;
}

VECTOR2D VECTOR2D::getUnitVector() const
{
	return ((*this)/(dist));
}

VECTOR2D::VECTOR2D(const double& VX, const double& VY)
{
	m_Vx = VX;
	m_Vy = VY;
	dist = calculateDist();
}

VECTOR2D::~VECTOR2D()
{
}
