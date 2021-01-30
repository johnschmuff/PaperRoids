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

#ifndef _CBUTTON_H
#define _CBUTTON_H

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
A very basic button class for determining if the mouse is in the area of the
button and if it is displaying a specific graphic rectangle from the sheet
specified. Also displays a graphic for being pushed down. Sounds can be enabled
so that when the button is hovered over it makes a one time sound and same with
being pushed down.
*/
class CButton
{
public:
	/*
	Constructor for creating the button object, when creating
	the button object by default enable sound effects to play
	are disabled (false), you can turn them on by following
	this example of usuage.
	USAGE:
	CButton button; //By default sounds disabled
	*/
	CButton();

	/*
	Deconstructor to clean up the CButton class
	if the sounds have been enabled, than the pointers will
	be deleted. See below SetSounds function for parameter.
	*/
	~CButton();

	/*
	Load the file that is the button sheet, once the sheet is
	loaded, all the clipping information for the buttons is
	already set for you. The button sheet must ascend on the y
	axis for this to properly work.
	USAGE:
	if(!button.LoadImageSheet("button.png"))
		return EXIT_FAILURE;
	*/
	bool LoadImageSheet(const char* data, const int& size);

	/*
	Set the position of the button in the window, once the
	position has been set, the collision rectangle is set for
	use in the Update function. Which allows the detection of
	a collision between the mouse and the button.
	USAGE:
	button.SetPosition(100, 100);
	*/
	void SetPosition(const float& xPos, const float& yPos);

	/*
	Call this function during the game loop so the button
	can be updated to check for the collision between the
	mouse and the button. If a collision has occurred the
	the clip rect gets set and if the sound is enabled than
	the sound effect for over and down will be played.
	USAGE:
	button.Update(Window.GetInput());
	*/
	void Update(const sf::Input& Input);

	/*
	Return the boolean value for the button being pressed
	down.
	USAGE:
	if(button.isPressed())
	    //do something
	*/
	bool isPressed();

	/*
	Reset the button in case you need to set isDown to false
	when a certain situation where you don't need the button
	to update anymore, but you need to reset the status.
	*/
	void resetButton();

	/*
	This function sets and enables the sound effects to be
	played when the mouse is over/and or left mouse button
	is pressed.
	USAGE:
	button.SetSounds(sound1, sound2);
	*/
	void SetSounds(const sf::Sound& soundOver, const sf::Sound& soundDown);

	/*
	Changing the volume of the button sound effects, ranging
	from 0 - 100 (none - max).
	USAGE:
	button.SetVolume(50, 50);
	*/
	void SetVolume(const float& overVolume, const float& downVolume);

	/*
	If later you wanted to enable or disable the sound effects
	during gameplay this would be a good function to use.
	USAGE:
	button.EnableSounds(true); //or (false) for no sounds
	*/
	void EnableSounds(const bool& enabled);

	/*
	Draw the button sprite in the window.
	USAGE:
	button.Draw(Window);
	*/
	void Draw(sf::RenderWindow& window);
private:
	sf::Image m_buffer;
	sf::Sprite m_sprite;
	sf::FloatRect m_colRect;
	sf::IntRect m_up, m_down, m_over;
	bool m_isDown, m_soundEnabled, m_hasPlayed;
	sf::Sound* m_soundOver;
	sf::Sound* m_soundDown;
	bool m_soundInit;
};

#endif