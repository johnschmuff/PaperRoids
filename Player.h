#ifndef _PLAYER_H
#define _PLAYER_H

#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

class Player
{
public:
	Player()
	{
		//Initalize all the objects parameters
		this->m_angle = 0;
		this->m_speed = 0;
		this->m_xPos = 0;
		this->m_yPos = 0;
		this->m_startX = 0;
		this->m_startY = 0;
		for(int i = 0; i < this->m_maxShots; i++)
		{
			this->m_lasAngle[i] = 0;
			this->m_lasXPos[i] = 0;
			this->m_lasYPos[i] = 0;
			this->m_isFired[i] = false;
		}
		this->m_lasSpeed = 5.0f;
		this->m_shotNum = 0;
		this->m_lives = 3;
		this->m_score = 0;
		this->m_hasCollided = false;
		this->m_Timer.Reset();
		this->m_soundEnabled = true;
	}

	~Player()
	{
	}

	bool LoadTextFont(const char* data, const int& size)
	{
		if(!this->m_font.LoadFromMemory(data, size))
		{
			return false;
		}
		else
		{
			this->m_livesText.SetFont(this->m_font);
			this->m_livesText.SetColor(sf::Color(0, 0, 0));
			this->m_livesText.SetString("");
			this->m_livesText.SetPosition(50, 0);
			this->m_scoreText.SetFont(this->m_font);
			this->m_scoreText.SetColor(sf::Color(0, 0, 0));
			this->m_scoreText.SetString("");
			this->m_scoreText.SetPosition(825, 0);
		}

		return true;
	}

	bool LoadPlayerImage(const char* data, const int& size)
	{
		//Load the image for the player ship into the buffer
		if(!this->m_buffer.LoadFromMemory(data, size))
		{
			//Error logging goes here
			return false;
		}
		else
		{
			//Once image is loaded into the buffer set the sprites image and center
			this->m_sprite.SetImage(this->m_buffer);
			this->m_sprite.SetOrigin(static_cast<float>(this->m_buffer.GetWidth() / 2), static_cast<float>(this->m_buffer.GetHeight() / 2));
		}

		return true;
	}

	bool LoadLaserImage(const char* data, const int& size)
	{
		//Load the image for the ships laser into the buffer
		if(!this->m_lasBuffer.LoadFromMemory(data, size))
		{
			//Error logging goes here
			return false;
		}
		else
		{
			//Once image is loaded into the buffer set the laser sprites and center for each shot
			this->m_lasBuffer.SetSmooth(false);
			for(int i = 0; i < this->m_maxShots; i++)
			{
				this->m_lasSprite[i].SetImage(this->m_lasBuffer);
				this->m_lasSprite[i].SetOrigin(static_cast<float>(this->m_lasBuffer.GetWidth() / 2), static_cast<float>(this->m_lasBuffer.GetHeight() / 2));
			}
		}

		return true;
	}

	bool LoadLaserSound(const char* data, const int& size)
	{
		//Load the sound for the ships laser into the buffer
		if(!this->m_soundBuffer.LoadFromMemory(data, size))
		{
			//Error logging goes here
			return false;
		}
		else
		{
			//Once the sound is loaded into the buffer set the lasers sound effect
			this->m_sound.SetBuffer(this->m_soundBuffer);
		}

		return true;
	}

	void SetPosition(const float& x, const float& y)
	{
		//Set the starting position
		this->m_startX = x;
		this->m_startY = y;

		//Set the position of the player ship from x/y parameters
		this->m_xPos = x;
		this->m_yPos = y;
	}

	float toRadians(const float& degrees)
	{
		//Returns radians from degrees
		return degrees * 3.14f / 180;
	}

	void Update(const float& frametime)
	{
		if(!this->m_hasCollided)
		{
			//Update the frametime of the game window for class use
			this->m_frametime = frametime;

			//Calculate the position of the ship based on it's angle and speed
			this->m_xPos += this->m_speed * -sin(toRadians(this->m_angle));
			this->m_yPos += this->m_speed * -cos(toRadians(this->m_angle));

			//Update the rotation and the position of the player ship
			this->m_sprite.SetRotation(this->m_angle);
			this->m_sprite.SetPosition(this->m_xPos, this->m_yPos);

			//Keep the player object in bounds of the game window
			if(this->m_yPos < -30)
			{
				this->m_yPos = 798;
			}
			else if(this->m_yPos > 798)
			{
				this->m_yPos = -30;
			}
			if(this->m_xPos < -30)
			{
				this->m_xPos = 1054;
			}
			else if(this->m_xPos > 1054)
			{
				this->m_xPos = -30;
			}

			//Cycle through the max shots of the player ships laser
			for(int i = 0; i < this->m_maxShots; i++)
			{
				if(!this->m_isFired[i])
				{
					//Update the position and the angle of the lasers before being fired
					this->m_lasXPos[i] = this->m_xPos;
					this->m_lasYPos[i] = this->m_yPos;
					this->m_lasAngle[i] = this->m_angle;
				}
				else
				{
					//If the shot was fired, send them traving at there set speed and last angle before fired
					this->m_lasXPos[i] += this->m_lasSpeed * -sin(toRadians(this->m_lasAngle[i]));
					this->m_lasYPos[i] += this->m_lasSpeed * -cos(toRadians(this->m_lasAngle[i]));
				}

				//Update the rotation and the position of the laser sprite
				this->m_lasSprite[i].SetRotation(this->m_lasAngle[i]);
				this->m_lasSprite[i].SetPosition(this->m_lasXPos[i], this->m_lasYPos[i]);

				//Check whether the laser shots went out of bounds and reset them if they did
				if(this->m_lasYPos[i] < -10)
					this->m_isFired[i] = false;
				else if(this->m_lasYPos[i] > 778)
					this->m_isFired[i] = false;
				else if(this->m_lasXPos[i] < -10)
					this->m_isFired[i] = false;
				else if(this->m_lasXPos[i] > 1034)
					this->m_isFired[i] = false;
			}
		}
		else if(this->m_hasCollided)
		{
			//Move object out of collision range
			this->m_xPos = -1000;
			this->m_yPos = -1000;
			this->m_sprite.SetPosition(this->m_xPos, this->m_yPos);
			//Wait 2 seconds before resetting object
			if(this->m_Timer.GetElapsedTime() > 2)
			{
				ResetPosition();
			}
		}
	}

	void ApplyThrust(const float& velocity)
	{
		//Apply the velocity parameter multiplied by the game frametime to the ships speed
		this->m_speed += velocity * this->m_frametime;

		//Make sure the speed of the ship doesn't go beyond the desired amount
		if(this->m_speed >= 2.5f)
		{
			this->m_speed = 2.5f;
		}
	}

	void ApplyBrake(const float& velocity)
	{
		//Decrease the speed by the set velocity multiplied by the game frametime
		this->m_speed -= velocity * this->m_frametime;

		//Make sure the ship doesn't go backwards if decreased to far, reset to zero
		if(this->m_speed <= 0.0f)
		{
			this->m_speed = 0.0f;
		}
	}

	void ApplyRotation(const float& rotation)
	{
		//Apply the desired amount of rotation from the function parameter (rotation)
		this->m_angle += rotation * this->m_frametime;
	}

	void FireLaser()
	{
		//Fire the laser based on its number
		this->m_isFired[this->m_shotNum] = true;
		this->m_shotNum++;
		if(m_soundEnabled)
		{
			this->m_sound.Play();
		}

		//When the num of shots fired equals the amount allowed reset to zero
		if(this->m_shotNum == this->m_maxShots)
		{
			this->m_shotNum = 0;
		}
	}

	bool CheckCollision(const sf::Sprite& Sprite1, const sf::Sprite& Sprite2)
	{
		//Get the sprites parameters to calculate distance between objects and return
		//a collision
		float spriteRad1 = (Sprite1.GetSize().x + Sprite1.GetSize().y) / 4;
		float spriteRad2 = (Sprite2.GetSize().x + Sprite2.GetSize().y) / 4;
		float xDist = Sprite1.GetPosition().x - Sprite2.GetPosition().x;
		float yDist = Sprite1.GetPosition().y - Sprite2.GetPosition().y;

		return sqrt(xDist * xDist + yDist * yDist) <= spriteRad1 + spriteRad2;
	}

	bool CheckLaserCollision(const sf::Sprite& Object)
	{
		//Cycle through all the laser shots and see if a collision has occurred with Object
		for(int i = 0; i < m_maxShots; i++)
		{
			//Test collision
			if(CheckCollision(this->m_lasSprite[i], Object))
				return true;
		}

		return false;
	}

	//Increment the score by the amount set in the function parameter
	void AddScore(const int& score)
	{
		this->m_score += score;
	}

	//Deincrement a life by 1 and score by 100
	void SubLife()
	{
		this->m_lives--;
		this->m_score -= 100;
	}

	void SetCollisionCheck(const bool& colCheck)
	{
		this->m_hasCollided = colCheck;
		this->m_Timer.Reset();
	}

	void Reset()
	{
		//Reset all the objects parameters
		this->m_xPos = this->m_startX;
		this->m_yPos = this->m_startY;
		this->m_angle = 0;
		this->m_lives = 3;
		this->m_score = 0;
	}

	void ResetPosition()
	{
		//Reset the position, speed and angle
		this->m_xPos = this->m_startX;
		this->m_yPos = this->m_startY;
		this->m_speed = 0;
		this->m_angle = 0;
		
		//set if collision has occured to false
		this->m_hasCollided = false;
	}

	void Draw(sf::RenderWindow& Window)
	{
		if(!this->m_hasCollided)
		{
			//Draw the player sprite (Ship)
			Window.Draw(this->m_sprite);

			//Cycle through the lasers to be visible based on being fired
			for(int i = 0; i < this->m_maxShots; i++)
			{
				if(this->m_isFired[i])
				{
					Window.Draw(this->m_lasSprite[i]);
				}
			}
		}

		//Draw the player score and lives
		std::stringstream ss1;
		std::stringstream ss2;

		ss1 << "Score: " << this->m_score;
		ss2 << "Lives: " << this->m_lives;

		this->m_scoreText.SetString(ss1.str().c_str());
		this->m_livesText.SetString(ss2.str().c_str());

		Window.Draw(this->m_scoreText);
		Window.Draw(this->m_livesText);
	}

	void SoundEnabled(const bool& enabled)
	{
		//enable sound true or false
		this->m_soundEnabled = enabled;
	}

	int ReturnLives()
	{
		return this->m_lives;
	}

	sf::Sprite& ReturnSprite()
	{
		return this->m_sprite;
	}
private:
	sf::Image m_buffer;
	sf::Sprite m_sprite;
	float m_xPos, m_yPos;
	float m_startX, m_startY;
	float m_angle, m_speed;
	sf::Image m_lasBuffer;
	static const int m_maxShots = 10;
	sf::Sprite m_lasSprite[m_maxShots];
	float m_lasXPos[m_maxShots], m_lasYPos[m_maxShots];
	float m_lasAngle[m_maxShots], m_lasSpeed;
	int m_shotNum;
	bool m_isFired[m_maxShots];
	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_sound;
	bool m_soundEnabled;
	float m_frametime;
	int m_lives;
	int m_score;
	sf::Text m_scoreText;
	sf::Text m_livesText;
	sf::Font m_font;
	bool m_hasCollided;
	sf::Clock m_Timer;
};

#endif