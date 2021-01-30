#ifndef _OBJECT_H
#define _OBJECT_H

#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object()
	{
		this->m_xPos = 0;
		this->m_yPos = 0;
		this->m_angle = 0;
		this->m_isVisible = false;
		this->m_quadrant = 0;
		this->m_xPosRand = 0;
		this->m_yPosRand = 0;
		this->m_angleRand = 0;
		this->m_rotation = 0;
		this->m_speed = 0;
		this->m_hasCollided =  false;
	}

	~Object()
	{
	}

	bool SetImage(const char* data, const int& size)
	{
		if(!this->m_buffer.LoadFromMemory(data, size))
		{
			//Error logging here...
			return false;
		}

		return true;
	}

	void SetSprite(sf::Image& buffer)
	{
		this->m_sprite.SetImage(buffer);
		this->m_sprite.SetOrigin(static_cast<float>(buffer.GetWidth() / 2), static_cast<float>(buffer.GetHeight() / 2));
	}

	float toRadians(const float& degree)
	{
		return degree * 3.14f / 180;
	}

	void SetCollision(const bool& collision)
	{
		this->m_hasCollided = collision;
	}

	void Update(const float& frametime)
	{
		this->m_frametime = frametime;

		if(!this->m_hasCollided)
		{
			if(!this->m_isVisible)
			{
				this->m_quadrant = rand() % 8 + 1;
				if(this->m_quadrant == 1 || this->m_quadrant == 2)
				{
					this->m_xPosRand = static_cast<float>(rand() % 1024);
					this->m_yPosRand = static_cast<float>(-(rand() % 30));
					if(this->m_xPosRand > 512)
					{
						this->m_angleRand = static_cast<float>(rand() % 30 + 30);
					}
					else if(this->m_xPosRand <= 512)
					{
						this->m_angleRand = static_cast<float>(rand() % 30 + 30);
					}
				}
				else if(this->m_quadrant == 3 || this->m_quadrant == 4)
				{
					this->m_xPosRand = static_cast<float>(rand() % 30 + 1024);
					this->m_yPosRand = static_cast<float>(rand() % 768);
					if(this->m_yPosRand > 375)
					{
						this->m_angleRand = static_cast<float>(rand() % 30 + 30);
					}
					else if(this->m_yPosRand <= 375)
					{
						this->m_angleRand = static_cast<float>(rand() % 30 + 60);
					}
				}
				else if(this->m_quadrant == 5 || this->m_quadrant == 6)
				{
					this->m_xPosRand = static_cast<float>(rand() % 1024);
					this->m_yPosRand = static_cast<float>(rand() % 30 + 768);
					if(m_xPosRand > 512)
					{
						this->m_angleRand = static_cast<float>((rand() % 30 + 1));
					}
					else if(this->m_xPosRand <= 512)
					{
						this->m_angleRand = static_cast<float>((rand() % 30 + 1));
					}
				}
				else if(this->m_quadrant == 7 || this->m_quadrant == 8)
				{
					this->m_xPosRand = static_cast<float>(-(rand() % 30));
					this->m_yPosRand = static_cast<float>(rand() % 768);
					if(this->m_yPosRand > 375)
					{
						this->m_angleRand = static_cast<float>(-(rand() % 30 + 30));
					}
					else if(this->m_yPosRand <= 375)
					{
						this->m_angleRand = static_cast<float>(-(rand() % 30 + 60));
					}
				}

				this->m_xPos = m_xPosRand;
				this->m_yPos = m_yPosRand;
				this->m_angle = m_angleRand;
				this->m_isVisible = true;

				int speedSelect = rand() % 10 + 1;
				if(speedSelect <= 2)
				{
					this->m_speed = 1.0f;
				}
				else if(speedSelect == 3 || speedSelect == 4)
				{
					this->m_speed = 1.5f;
				}
				else if(speedSelect == 5 || speedSelect == 6)
				{
					this->m_speed = 2.0f;
				}
				else if(speedSelect == 7 || speedSelect == 8)
				{
					this->m_speed = 2.5f;
				}
				else if(speedSelect == 9 || speedSelect == 10)
				{
					this->m_speed = 3.0f;
				}
			}
			else if(this->m_isVisible)
			{
				this->m_xPos += this->m_speed * -sin(toRadians(this->m_angle));
				this->m_yPos += this->m_speed * -sin(toRadians(this->m_angle));

				this->m_rotation += this->m_angle * this->m_frametime;

				this->m_sprite.SetRotation(this->m_rotation);
				this->m_sprite.SetPosition(this->m_xPos, this->m_yPos);
			}

			if(this->m_xPos < -30)
			{
				this->m_isVisible = false;
			}
			else if(this->m_xPos > 1054)
			{
				this->m_isVisible = false;
			}
			else if(this->m_yPos < -30)
			{
				this->m_isVisible = false;
			}
			else if(this->m_yPos > 798)
			{
				this->m_isVisible = false;
			}
		}
		else if(this->m_hasCollided)
		{
			this->m_sprite.SetPosition(-100, -100);
		}
	}

	void Reset()
	{
		this->m_isVisible = false;
		this->m_hasCollided = false;
	}

	void Draw(sf::RenderWindow& Window)
	{
		if(this->m_isVisible)
		{
			Window.Draw(this->m_sprite);
		}
	}

	sf::Image& ReturnBuffer()
	{
		return this->m_buffer;
	}

	sf::Sprite& ReturnSprite()
	{
		return this->m_sprite;
	}
private:
	sf::Image m_buffer;
	sf::Sprite m_sprite;
	float m_xPos, m_yPos;
	float m_angle, m_speed;
	float m_rotation, m_frametime;
	bool m_isVisible;
	int m_quadrant;
	float m_xPosRand, m_yPosRand, m_angleRand;
	bool m_hasCollided;
};

#endif