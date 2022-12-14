#include "Pig.h"

Pig::Pig(float in_x, float in_y, float width, float height, float max_displacement)
	:
	Entity( in_x, in_y, width, height)
{
	xVel = 20.0f;
	m_maxDisplacement = max_displacement;
}

void Pig::move(float dt)
{
	x += xVel * dt;
	// Invert movement if pig reaches maximum displacement 
	if (x > m_initialX + m_maxDisplacement)
		xVel = -xVel;
	if (x < m_initialX)
		xVel = -xVel;
}

void Pig::stop()
{
	xVel = 0;
}

void Pig::check_fruit_existance(Fruit& fruit)
{
	if (fruit.is_collected())
		enrage();
}
void Pig::enrage()
{
	
	// Double velocity when pig enrages
	xVel *= 2.1;
	enraged = true;
}

bool Pig::is_enraged()
{
	return enraged;
}