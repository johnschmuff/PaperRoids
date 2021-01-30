/*
Copyright(c) 2010 John Schmuff (www.johnschmuff.com)

MIT License:
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "CButton.h"
#include "CData.h"
#include "CErrorlog.h"
#include "Object.h"
#include "Player.h"

/*
Basic rendering class to handle creating the SFML window and creating virtual functions for the
derived class to be able to use when calling run in the main function. Allows for one input key
to be used "ESC" to exit the window by key press, or an event at which the window will close if
the windows X is pressed in the upper left hand corner.
*/
class CRender
{
public:
	//Constructor to take the parameters of the windows width, height and title.
	CRender(const int& windowWidth, const int& windowHeight, const std::string& windowTitle)
	{
		this->m_pWindow = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight, 32), windowTitle, sf::Style::Close);
	}
	//deconstructor to do cleanup of the class mainly deleting the window pointer.
	~CRender()
	{
		delete this->m_pWindow;
	}

	//virtual function which is intended for loading the game files if loaded correctly
	//the function will return true and false otherwise.
	virtual bool Init()
	{
		return true;
	}

	//virtual function to handle the user input from the input device in this case the
	//keyboard is used to exit the program by pressing the "ESC" button.
	virtual void Input()
	{
		const sf::Input& Input = this->m_pWindow->GetInput();

		if(Input.IsKeyDown(sf::Key::Escape))
			this->m_pWindow->Close();
	}

	//virtual function to take in all the game objects updates, IE movement, collision
	//frametime, etc...
	virtual void Update()
	{
		//Empty
	}

	//virtual function to handle drawing all the game objects that are to be shown.
	virtual void Render()
	{
		//Empty
	}

	//This is the function where it all happens, we check is the Init function returns
	//true, then we hold the main game loop taking in the events and calling the above
	//virtual functions to handle the games purpose.
	bool Run()
	{
		if(!Init())
			return false;

		while(this->m_pWindow->IsOpened())
		{
			while(this->m_pWindow->GetEvent(this->m_event))
			{
				if(this->m_event.Type == sf::Event::Closed)
					this->m_pWindow->Close();
			}

			Input();
			Update();
			this->m_pWindow->Clear();
			Render();
			this->m_pWindow->Display();
		}

		return true;
	}

	//Return the game window to allow access outside of this class.
	sf::RenderWindow* ReturnWindow()
	{
		return this->m_pWindow;
	}
private:
	sf::RenderWindow* m_pWindow;
	sf::Event m_event;
};