#include "CButton.h"

CButton::CButton()
{
	//Initialise the button parameters
	this->m_colRect = sf::FloatRect(0, 0, 0, 0);
	this->m_up = sf::IntRect(0, 0, 0, 0);
	this->m_down = sf::IntRect(0, 0, 0, 0);
	this->m_over = sf::IntRect(0, 0, 0, 0);
	this->m_isDown = false;
	this->m_soundEnabled = false;
	this->m_soundInit = false;
}

CButton::~CButton()
{
	//If the sounds have been initialised than delete pointers
	if(this->m_soundInit)
	{
		delete this->m_soundDown;
		delete this->m_soundOver;
	}
}

bool CButton::LoadImageSheet(const char* data, const int& size)
{
	if(!this->m_buffer.LoadFromMemory(data, size))
	{
		//Error logging here
		return false;
	}
	else
	{
		//Set the origin of the button sprite
		this->m_sprite.SetOrigin(static_cast<float>(this->m_buffer.GetWidth() / 2), static_cast<float>((this->m_buffer.GetHeight() / 3) / 2));

		//Button "Up" clip rectangle
		this->m_up.Left = 0;
		this->m_up.Top = 0;
		this->m_up.Width = this->m_buffer.GetWidth();
		this->m_up.Height = this->m_buffer.GetHeight() / 3;

		//Button "Down" clip rectangle
		this->m_down.Left = 0;
		this->m_down.Top = this->m_buffer.GetHeight() / 3 * 1;
		this->m_down.Width = this->m_buffer.GetWidth();
		this->m_down.Height = this->m_buffer.GetHeight() / 3;

		//Button "Over" clip rectangle
		this->m_over.Left = 0;
		this->m_over.Top = this->m_buffer.GetHeight() / 3 * 2;
		this->m_over.Width = this->m_buffer.GetWidth();
		this->m_over.Height = this->m_buffer.GetHeight() / 3;

		//Set the buffer smoothing, sprites image and the initial clip rectangle
		this->m_buffer.SetSmooth(false);
		this->m_sprite.SetImage(this->m_buffer);
		this->m_sprite.SetSubRect(this->m_up);
	}

	return true;
}

void CButton::SetPosition(const float& xPos, const float& yPos)
{
	//Set the button sprite position
	this->m_sprite.SetPosition(xPos, yPos);

	//Button collision rectangle
	this->m_colRect.Left = this->m_sprite.GetPosition().x - (this->m_buffer.GetWidth() / 2);
	this->m_colRect.Top = this->m_sprite.GetPosition().y - ((this->m_buffer.GetHeight() / 3) / 2);
	this->m_colRect.Width = this->m_sprite.GetPosition().x + (this->m_buffer.GetWidth() / 2);
	this->m_colRect.Height = this->m_sprite.GetPosition().y + ((this->m_buffer.GetHeight() / 3) / 2);
}

void CButton::Update(const sf::Input& Input)
{
	//Get the position of the mouse coordinates x/y
	float mouseX = static_cast<float>(Input.GetMouseX());
	float mouseY = static_cast<float>(Input.GetMouseY());

	//Check if the mouse has collided with the button
	if(((mouseX > this->m_colRect.Left) && mouseX < this->m_colRect.Width) &&
		((mouseY > this->m_colRect.Top) && (mouseY < this->m_colRect.Height)))
	{
		//Check if the left mouse button has been pressed
		if(Input.IsMouseButtonDown(sf::Mouse::Left) && !this->m_isDown)
		{
			//Once the mouse has collided and the button is pressed
			this->m_sprite.SetSubRect(this->m_down);
			this->m_hasPlayed = false;
			this->m_isDown = true;

			//Play sound if the sound has been enabled previously
			if(this->m_soundEnabled)
			{
				if(!this->m_hasPlayed)
				{
					this->m_soundDown->Play();
					this->m_hasPlayed = true;
				}
			}
		}
		else //If the left mouse button isn't pressed but there is collision
		{
			//Once the mouse has collided with the button
			this->m_sprite.SetSubRect(this->m_over);
			this->m_isDown = false;

			//Play sound if the sound has been enabled previously
			if(this->m_soundEnabled)
			{
				if(!this->m_hasPlayed)
				{
					this->m_soundOver->Play();
					this->m_hasPlayed = true;
				}
			}
		}
	}
	else //No collision is found between mouse and button
	{
		this->m_sprite.SetSubRect(this->m_up);
		this->m_isDown = false;
		this->m_hasPlayed = false;
	}
}

bool CButton::isPressed()
{
	return this->m_isDown;
}

void CButton::resetButton()
{
	this->m_isDown = false;
}

void CButton::SetSounds(const sf::Sound& soundOver, const sf::Sound& soundDown)
{
	this->m_soundOver = new sf::Sound(soundOver);
	this->m_soundDown = new sf::Sound(soundDown);
	this->m_soundInit = true;
}

void CButton::SetVolume(const float& overVolume, const float& downVolume)
{
	this->m_soundOver->SetVolume(overVolume);
	this->m_soundDown->SetVolume(downVolume);
}

void CButton::EnableSounds(const bool& enabled)
{
	this->m_soundEnabled = enabled;
}

void CButton::Draw(sf::RenderWindow& window)
{
	window.Draw(this->m_sprite);
}