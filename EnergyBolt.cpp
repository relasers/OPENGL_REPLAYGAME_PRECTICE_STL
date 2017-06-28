#pragma once
#include "stdafx.h"
#include "EnergyBolt.h"
#include "RanderProp.h"

CEnergyBolt::CEnergyBolt()
{

}


CEnergyBolt::CEnergyBolt(Vec3f pt, Vec3f target, 
	float speed, float size,Vec3f color, 
	list<Cbullet*>& bullets)
{
	m_vCenter = pt;
	m_color = color;
	m_vDirection = target - pt;
	Normalize(m_vDirection);
	m_speed = speed;
	m_size = size;
	m_bullets = &bullets;
}

CEnergyBolt::~CEnergyBolt()
{
}

void CEnergyBolt::Update(const float fTimeElapsed)
{
	m_speed -= fTimeElapsed*3200.0f;

	m_vCenter += m_vDirection * m_speed * fTimeElapsed;
	m_BindingCube.SetPos(m_vCenter);
	m_rotate_angle += 60.0f * fTimeElapsed;
	if (m_rotate_angle > 360.0f) m_rotate_angle = 0.0f;

	if (m_speed < 0 && m_bDie == false) {
	
		m_speed = 0;
		m_bDie = true;

		default_random_engine dre;
		uniform_int_distribution<> random_target (0, 256);
		uniform_int_distribution<> random_speed (0, 1600);

		for (int i = 0; i < 64; ++i) {
			Vec3f target = {
				m_vCenter.x - 128 + random_target(dre),
				m_vCenter.y - 128 + random_target(dre),
				m_vCenter.z - 128 + random_target(dre)
			};
			m_bullets->push_back(new Cbullet(m_vCenter, target, m_speed+ random_speed(dre), m_size*0.5, true, COLOR_EGGYOLK,false));
		}
		
	
	}
}

void CEnergyBolt::Rendering()
{
	if (!m_bDie) {
		glPushMatrix();
		{
			glLineWidth(3.0);
			glColor3f(m_color.x, m_color.y, m_color.z);
			glTranslatef(m_vCenter.x, m_vCenter.y, m_vCenter.z);
			glRotatef(m_rotate_angle, 1, 1, 1);
			glutWireSphere(m_size, 20, 20);
			glRotatef(m_rotate_angle * 2, 1, 1, 1);
			glutWireCube(m_size*0.5);
			glRotatef(m_rotate_angle * 3, 1, 1, 1);
			glutSolidCube(m_size*0.25);
			glLineWidth(1.0);
		}
		glPopMatrix();
	}
	



}
