#include "CRender.h"

class myGame : public CRender
{
public:
	myGame() : CRender(1024, 768, "PaperRoids")
	{
		this->m_gamestate = 0;
		this->m_data = new CData("PaperRoids.dta");
		this->m_clock.Reset();
		this->m_pGame = CRender::ReturnWindow();
		this->m_pGame->SetFramerateLimit(120);
		this->m_pGame->Clear();
		this->m_pGame->Display();
		this->m_pGame->ShowMouseCursor(false);
		this->m_isSoundOff = false;
		this->m_smallAsteroids = 25;
		this->m_largeAsteroids = 5;
		this->m_totalAsteroids = this->m_smallAsteroids + this->m_largeAsteroids;
		this->m_isPressed = false;
		this->m_isLost = false;
		this->m_isWon = false;
		this->m_isPaused = false;
	}

	~myGame()
	{
	}

	bool Init()
	{
		//Load the custom cursor image
		if(!this->m_data->LoadFile("Cursor.png"))
		{
			this->m_log.Error("Unable to load Cursor.png");
			return false;
		}
		else
		{
			this->m_cursorBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_cursor.SetImage(this->m_cursorBuffer);
			this->m_cursor.SetPosition(static_cast<float>(this->m_pGame->GetInput().GetMouseX()), static_cast<float>(this->m_pGame->GetInput().GetMouseY()));
		}

		//Load the SFML logo file
		if(!this->m_data->LoadFile("SFML.png"))
		{
			this->m_log.Error("Unable to load SFML.png");
			return false;
		}
		else
		{
			this->m_splashBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_splash.SetImage(this->m_splashBuffer);
			this->m_splash.SetOrigin(static_cast<float>(this->m_splashBuffer.GetWidth() / 2), static_cast<float>(this->m_splashBuffer.GetHeight() / 2));
			this->m_splash.SetPosition(1024 / 2, 768 / 2);
		}

		//Load the background file
		if(!this->m_data->LoadFile("background.png"))
		{
			this->m_log.Error("Unable to load background.png");
			return false;
		}
		else
		{
			this->m_backgroundBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_background.SetImage(this->m_backgroundBuffer);
		}

		//Load the helpScreen overlay image
		if(!this->m_data->LoadFile("helpScreen.png"))
		{
			this->m_log.Error("Unable to load helpScreen.png");
			return false;
		}
		else
		{
			this->m_helpOverBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_helpOver.SetImage(this->m_helpOverBuffer);
			this->m_helpOver.SetOrigin(static_cast<float>(this->m_helpOverBuffer.GetWidth() / 2), static_cast<float>(this->m_helpOverBuffer.GetHeight() / 2));
			this->m_helpOver.SetPosition(1024 / 2, 768 / 2);

		}

		//Load the title files
		if(!this->m_data->LoadFile("Title.png"))
		{
			this->m_log.Error("Unable to load Title.png");
			return false;
		}
		else
		{
			this->m_titleBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_title.SetImage(this->m_titleBuffer);
			this->m_title.SetOrigin(static_cast<float>(this->m_titleBuffer.GetWidth() / 2), static_cast<float>(this->m_titleBuffer.GetHeight() / 2));
			this->m_title.SetPosition(1024 / 2, 200);
		}

		if(!this->m_data->LoadFile("Options.png"))
		{
			this->m_log.Error("Unable to load Options.png");
			return false;
		}
		else
		{
			this->m_optionsBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_options.SetImage(this->m_optionsBuffer);
			this->m_options.SetOrigin(static_cast<float>(this->m_optionsBuffer.GetWidth() / 2), static_cast<float>(this->m_optionsBuffer.GetHeight() / 2));
			this->m_options.SetPosition(1024 / 2, 200);
		}

		if(!this->m_data->LoadFile("Help.png"))
		{
			this->m_log.Error("Unable to load Help.png");
			return false;
		}
		else
		{
			this->m_helpBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_help.SetImage(this->m_helpBuffer);
			this->m_help.SetOrigin(static_cast<float>(this->m_helpBuffer.GetWidth() / 2), static_cast<float>(this->m_helpBuffer.GetHeight() / 2));
			this->m_help.SetPosition(1024 / 2, 200);
		}

		if(!this->m_data->LoadFile("credits.png"))
		{
			this->m_log.Error("Unable to load credits.png");
			return false;
		}
		else
		{
			this->m_creditsBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_credits.SetImage(this->m_creditsBuffer);
		}

		//Load sound effect files
		if(!this->m_data->LoadFile("SoundOver.wav"))
		{
			this->m_log.Error("Unable to load SoundOver.wav");
			return false;
		}
		else
		{
			this->m_overBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_over.SetBuffer(this->m_overBuffer);
		}

		if(!this->m_data->LoadFile("SoundDown.wav"))
		{
			this->m_log.Error("Unable to load SoundDown.wav");
			return false;
		}
		else
		{
			this->m_downBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_down.SetBuffer(this->m_downBuffer);
		}

		if(!this->m_data->LoadFile("Proton.wav"))
		{
			this->m_log.Error("Unable to load Proton.wav");
			return false;
		}
		else
		{
			this->m_Player.LoadLaserSound(this->m_data->ReturnData(), this->m_data->ReturnSize());
		}

		if(!this->m_data->LoadFile("Explosion.wav"))
		{
			this->m_log.Error("Unable to load Explosion.wav");
			return false;
		}
		else
		{
			this->m_explosionBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_explosion.SetBuffer(this->m_explosionBuffer);
		}

		//Load the button files
		if(!this->m_data->LoadFile("StartButton.png"))
		{
			this->m_log.Error("Unable to load StartButton.png");
			return false;
		}
		else
		{
			this->m_startButton.LoadImageSheet(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_startButton.EnableSounds(true);
			this->m_startButton.SetSounds(this->m_over, this->m_down);
			this->m_startButton.SetPosition(0, 0);
		}

		if(!this->m_data->LoadFile("OptionsButton.png"))
		{
			this->m_log.Error("Unable to load OptionsButton.png");
			return false;
		}
		else
		{
			this->m_optionsButton.LoadImageSheet(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_optionsButton.EnableSounds(true);
			this->m_optionsButton.SetSounds(this->m_over, this->m_down);
			this->m_optionsButton.SetPosition(0, 0);
		}

		if(!this->m_data->LoadFile("HelpButton.png"))
		{
			this->m_log.Error("Unable to load HelpButton.png");
			return false;
		}
		else
		{
			this->m_helpButton.LoadImageSheet(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_helpButton.EnableSounds(true);
			this->m_helpButton.SetSounds(this->m_over, this->m_down);
			this->m_helpButton.SetPosition(0, 0);
		}

		if(!this->m_data->LoadFile("QuitButton.png"))
		{
			this->m_log.Error("Unable to load QuitButton.png");
			return false;
		}
		else
		{
			this->m_quitButton.LoadImageSheet(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_quitButton.EnableSounds(true);
			this->m_quitButton.SetSounds(this->m_over, this->m_down);
			this->m_quitButton.SetPosition(0, 0);
		}

		if(!this->m_data->LoadFile("MenuButton.png"))
		{
			this->m_log.Error("Unable to load MenuButton.png");
			return false;
		}
		else
		{
			this->m_menuButton.LoadImageSheet(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_menuButton.EnableSounds(true);
			this->m_menuButton.SetSounds(this->m_over, this->m_down);
			this->m_menuButton.SetPosition(0, 0);
		}

		if(!this->m_data->LoadFile("OnButton.png"))
		{
			this->m_log.Error("Unable to load OnButton.png");
			return false;
		}
		else
		{
			this->m_onButton.LoadImageSheet(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_onButton.EnableSounds(true);
			this->m_onButton.SetSounds(this->m_over, this->m_down);
			this->m_onButton.SetPosition(0, 0);
		}

		if(!this->m_data->LoadFile("OffButton.png"))
		{
			this->m_log.Error("Unable to load OffButton.png");
			return false;
		}
		else
		{
			this->m_offButton.LoadImageSheet(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_offButton.EnableSounds(true);
			this->m_offButton.SetSounds(this->m_over, this->m_down);
			this->m_offButton.SetPosition(0, 0);
		}

		if(!this->m_data->LoadFile("ResumeButton.png"))
		{
			this->m_log.Error("Unable to load ResumeButton.png");
			return false;
		}
		else
		{
			this->m_resumeButton.LoadImageSheet(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_resumeButton.EnableSounds(true);
			this->m_resumeButton.SetSounds(this->m_over, this->m_down);
			this->m_resumeButton.SetPosition(0, 0);
		}

		//Load the text
		if(!this->m_data->LoadFile("crayon.ttf"))
		{
			this->m_log.Error("Unable to load Crayon.ttf");
			return false;
		}
		else
		{
			this->m_crayonFont.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_musicText.SetFont(this->m_crayonFont);
			this->m_musicText.SetColor(sf::Color(0, 0, 0));
			this->m_musicText.SetString("Sound Effects:");
			this->m_musicText.SetPosition(420, 520);
			this->m_Player.LoadTextFont(this->m_data->ReturnData(), this->m_data->ReturnSize());
		}

		//Load the overlays
		if(!this->m_data->LoadFile("pauseOverlay.png"))
		{
			this->m_log.Error("Unable to load pauseOverlay.png");
			return false;
		}
		else
		{
			this->m_pauseBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_pause.SetImage(this->m_pauseBuffer);
		}

		if(!this->m_data->LoadFile("overOverlay.png"))
		{
			this->m_log.Error("Unable to load overOverlay.png");
			return false;
		}
		else
		{
			this->m_gameoverBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_gameover.SetImage(this->m_gameoverBuffer);
		}

		if(!this->m_data->LoadFile("wonOverlay.png"))
		{
			this->m_log.Error("Unable to load wonOverlay.png");
			return false;
		}
		else
		{
			this->m_gamewonBuffer.LoadFromMemory(this->m_data->ReturnData(), this->m_data->ReturnSize());
			this->m_gamewon.SetImage(this->m_gamewonBuffer);
		}

		//Load the Game objects
		if(!this->m_data->LoadFile("ship.png"))
		{
			this->m_log.Error("Unable to load Ship.png");
			return false;
		}
		this->m_Player.LoadPlayerImage(this->m_data->ReturnData(), this->m_data->ReturnSize());
		this->m_Player.SetPosition(1024 / 2, 768 / 2);

		if(!this->m_data->LoadFile("proton.png"))
		{
			this->m_log.Error("Unable to load Proton.png");
			return false;
		}
		this->m_Player.LoadLaserImage(this->m_data->ReturnData(), this->m_data->ReturnSize());

		if(!this->m_data->LoadFile("asteroid1.png"))
		{
			this->m_log.Error("Unable to load Asteroid1.png");
			return false;
		}
		this->m_smlAst[0].SetImage(this->m_data->ReturnData(), this->m_data->ReturnSize());
		for(int i = 0; i < this->m_smallAsteroids; i++)
		{
			this->m_smlAst[i].SetSprite(this->m_smlAst[0].ReturnBuffer());
		}

		if(!this->m_data->LoadFile("asteroid2.png"))
		{
			this->m_log.Error("Unable to load Asteroid2.png");
			return false;
		}
		this->m_lrgAst[0].SetImage(this->m_data->ReturnData(), this->m_data->ReturnSize());
		for(int i = 0; i < this->m_smallAsteroids; i++)
		{
			this->m_lrgAst[i].SetSprite(this->m_lrgAst[0].ReturnBuffer());
		}

		return true;
	}

	void Reset()
	{
		this->m_clock.Reset();
		this->m_isLost = false;
		this->m_isWon = false;
		this->m_isPaused = false;
		this->m_Player.Reset();
		this->m_totalAsteroids = this->m_smallAsteroids + this->m_largeAsteroids;
		for(int i = 0; i < this->m_smallAsteroids; i++)
		{
			this->m_smlAst[i].Reset();
		}
		for(int i = 0; i < this->m_largeAsteroids; i++)
		{
			this->m_lrgAst[i].Reset();
		}
	}

	void Input()
	{
		const sf::Input& Input = this->m_pGame->GetInput();

		switch(this->m_gamestate)
		{
		case 0: //Splash
			//No controls allowed in this state
			break;
		case 1: //Menu
			//Update the buttons
			this->m_startButton.Update(Input);
			this->m_optionsButton.Update(Input);
			this->m_helpButton.Update(Input);
			this->m_quitButton.Update(Input);
			break;
		case 2: //Options
			//Update the buttons
			this->m_menuButton.Update(Input);
			this->m_onButton.Update(Input);
			this->m_offButton.Update(Input);
			break;
		case 3: //Help
			//Update the buttons
			this->m_menuButton.Update(Input);
			break;
		case 4: //Game
			//If game is paused update buttons
			if(this->m_isPaused)
			{
				this->m_menuButton.Update(Input);
				this->m_resumeButton.Update(Input);
			}
			//If game is over update buttons
			if(this->m_isLost || this->m_isWon)
			{
				this->m_menuButton.Update(Input);
			}
			//Input key to pause the game play
			if(Input.IsKeyDown(sf::Key::Escape))
			{
				this->m_isPaused = true;
			}
			//Input key to apply the thrust to the player object
			if(Input.IsKeyDown(sf::Key::W))
			{
				this->m_Player.ApplyThrust(1.0f);
			}
			else if(Input.IsKeyDown(sf::Key::S))
			{
				this->m_Player.ApplyBrake(1.0f);
			}

			//Input keys to apply rotation to the player object
			if(Input.IsKeyDown(sf::Key::A))
			{
				this->m_Player.ApplyRotation(90.0f);
			}
			else if(Input.IsKeyDown(sf::Key::D))
			{
				this->m_Player.ApplyRotation(-90.0f);
			}

			//Fire the ships laser 1 shot pre button press
			if(Input.IsKeyDown(sf::Key::Space))
			{
				if(!m_isPressed)
				{
					this->m_Player.FireLaser();
				}
				this->m_isPressed = true;
			}
			else
			{
				this->m_isPressed = false;
			}
			break;
		case 5: //Credits
			//No controls allowed in this state
			break;
		}
	}

	void Update()
	{
		switch(this->m_gamestate)
		{
		case 0: //Splash
			//Once 5 seconds has passed increment the gamestate
			if(this->m_clock.GetElapsedTime() > 5)
				this->m_gamestate++;
			break;
		case 1: //Menu
			//Update the cursor position from mouse coordinates
			this->m_cursor.SetPosition(static_cast<float>(this->m_pGame->GetInput().GetMouseX()), static_cast<float>(this->m_pGame->GetInput().GetMouseY()));
			//Place the buttons
			this->m_startButton.SetPosition(512, 500);
			this->m_optionsButton.SetPosition(512, 540);
			this->m_helpButton.SetPosition(512, 580);
			this->m_quitButton.SetPosition(512, 620);
			//Check if buttons have been pressed
			if(this->m_startButton.isPressed())
			{
				this->m_gamestate = 4;
			}
			else if(this->m_optionsButton.isPressed())
			{
				this->m_gamestate = 2;
			}
			else if(this->m_helpButton.isPressed())
			{
				this->m_gamestate = 3;
			}
			else if(this->m_quitButton.isPressed())
			{
				this->m_gamestate = 5;
				this->m_clock.Reset();
			}
			break;
		case 2: //Options
			//Update the cursor position from mouse coordinates
			this->m_cursor.SetPosition(static_cast<float>(this->m_pGame->GetInput().GetMouseX()), static_cast<float>(this->m_pGame->GetInput().GetMouseY()));
			//Place the buttons
			this->m_menuButton.SetPosition(512, 720);
			this->m_onButton.SetPosition(480, 580);
			this->m_offButton.SetPosition(550, 580);
			//Check if buttons have been pressed
			if(this->m_menuButton.isPressed())
			{
				this->m_gamestate = 1;
			}
			if(this->m_onButton.isPressed())
			{
				this->m_isSoundOff = false;
				this->m_startButton.EnableSounds(true);
				this->m_optionsButton.EnableSounds(true);
				this->m_helpButton.EnableSounds(true);
				this->m_quitButton.EnableSounds(true);
				this->m_menuButton.EnableSounds(true);
				this->m_onButton.EnableSounds(true);
				this->m_offButton.EnableSounds(true);
				this->m_resumeButton.EnableSounds(true);
				this->m_Player.SoundEnabled(true);
			}
			else if(this->m_offButton.isPressed())
			{
				this->m_isSoundOff = true;
				this->m_startButton.EnableSounds(false);
				this->m_optionsButton.EnableSounds(false);
				this->m_helpButton.EnableSounds(false);
				this->m_quitButton.EnableSounds(false);
				this->m_menuButton.EnableSounds(false);
				this->m_onButton.EnableSounds(false);
				this->m_offButton.EnableSounds(false);
				this->m_resumeButton.EnableSounds(false);
				this->m_Player.SoundEnabled(false);
			}
			break;
		case 3: //Help
			//Update the cursor position from mouse coordinates
			this->m_cursor.SetPosition(static_cast<float>(this->m_pGame->GetInput().GetMouseX()), static_cast<float>(this->m_pGame->GetInput().GetMouseY()));
			//Update the button position
			this->m_menuButton.SetPosition(512, 720);
			//Check if buttons has been pressed
			if(this->m_menuButton.isPressed())
			{
				this->m_gamestate = 1;
			}
			break;
		case 4: //Game
			if(this->m_totalAsteroids == 0)
			{
				this->m_isWon = true;
			}
			if(this->m_Player.ReturnLives() <= 0)
			{
				this->m_isLost = true;
			}
			if(!this->m_isPaused && !this->m_isLost && !this->m_isWon)
			{
				//Update the player ship and laser shots
				this->m_Player.Update(this->m_pGame->GetFrameTime());

				//Update the small asteroids and test for player ship and laser shot collision
				for(int i = 0; i < this->m_smallAsteroids; i++)
				{
					this->m_smlAst[i].Update(this->m_pGame->GetFrameTime());

					if(this->m_Player.CheckCollision(this->m_Player.ReturnSprite(), this->m_smlAst[i].ReturnSprite()))
					{
						this->m_totalAsteroids--;
						this->m_smlAst[i].SetCollision(true);
						this->m_Player.SubLife();
						this->m_Player.SetCollisionCheck(true);
						if(!this->m_isSoundOff)
						{
							this->m_explosion.Play();
						}
					}

					if(this->m_Player.CheckLaserCollision(this->m_smlAst[i].ReturnSprite()))
					{
						this->m_totalAsteroids--;
						this->m_smlAst[i].SetCollision(true);
						this->m_Player.AddScore(100);
						if(!this->m_isSoundOff)
						{
							this->m_explosion.Play();
						}
					}
				}

				//Update the large asteroids and test for player ship and laser shot collision
				for(int i = 0; i < this->m_largeAsteroids; i++)
				{
					this->m_lrgAst[i].Update(this->m_pGame->GetFrameTime());

					if(this->m_Player.CheckCollision(this->m_Player.ReturnSprite(), this->m_lrgAst[i].ReturnSprite()))
					{
						this->m_totalAsteroids--;
						this->m_lrgAst[i].SetCollision(true);
						this->m_Player.SubLife();
						this->m_Player.SetCollisionCheck(true);
						if(!this->m_isSoundOff)
						{
							this->m_explosion.Play();
						}
					}

					if(this->m_Player.CheckLaserCollision(this->m_lrgAst[i].ReturnSprite()))
					{
						this->m_totalAsteroids--;
						this->m_lrgAst[i].SetCollision(true);
						this->m_Player.AddScore(250);
						if(!this->m_isSoundOff)
						{
							this->m_explosion.Play();
						}
					}
				}
			}
			if(this->m_isPaused)
			{
				//Update the cursor position from mouse coordinates
				this->m_cursor.SetPosition(static_cast<float>(this->m_pGame->GetInput().GetMouseX()), static_cast<float>(this->m_pGame->GetInput().GetMouseY()));
				//Update Menu and Resume button position
				this->m_resumeButton.SetPosition(512, 420);
				this->m_menuButton.SetPosition(512, 460);
				if(this->m_menuButton.isPressed())
				{
					this->m_menuButton.resetButton();
					this->m_gamestate = 1;
					this->Reset();
				}
				if(this->m_resumeButton.isPressed())
				{
					this->m_resumeButton.resetButton();
					this->m_isPaused = false;
				}
			}
			if(this->m_isLost || this->m_isWon)
			{
				//Update the cursor position from mouse coordinates
				this->m_cursor.SetPosition(static_cast<float>(this->m_pGame->GetInput().GetMouseX()), static_cast<float>(this->m_pGame->GetInput().GetMouseY()));
				//Update the menu button position
				this->m_menuButton.SetPosition(512, 720);
				if(this->m_menuButton.isPressed())
				{
					this->m_menuButton.resetButton();
					this->m_gamestate = 1;
					this->Reset();
				}
			}
			break;
		case 5: //Credits
			if(this->m_clock.GetElapsedTime() >= 3)
			{
				this->m_pGame->Close();
			}
			break;
		}
	}

	void Render()
	{
		switch(this->m_gamestate)
		{
		case 0: //Splash
			//Draw the SFML logo
			this->m_pGame->Draw(this->m_splash);
			break;
		case 1: //Menu
			//Draw the game background and game title
			this->m_pGame->Draw(this->m_background);
			this->m_pGame->Draw(this->m_title);
			//Draw the buttons
			this->m_startButton.Draw(*this->m_pGame);
			this->m_optionsButton.Draw(*this->m_pGame);
			this->m_helpButton.Draw(*this->m_pGame);
			this->m_quitButton.Draw(*this->m_pGame);
			//Draw the custom cursor
			this->m_pGame->Draw(this->m_cursor);
			break;
		case 2: //Options
			//Draw the game background, options title and music text
			this->m_pGame->Draw(this->m_background);
			this->m_pGame->Draw(this->m_options);
			this->m_pGame->Draw(this->m_musicText);
			//Draw the buttons
			this->m_menuButton.Draw(*this->m_pGame);
			this->m_onButton.Draw(*this->m_pGame);
			this->m_offButton.Draw(*this->m_pGame);
			//Draw the custom cursor
			this->m_pGame->Draw(this->m_cursor);
			break;
		case 3: //Help
			//Draw the game background, help title and helo overlay
			this->m_pGame->Draw(this->m_background);
			this->m_pGame->Draw(this->m_help);
			this->m_pGame->Draw(this->m_helpOver);
			//Draw the buttons
			this->m_menuButton.Draw(*this->m_pGame);
			//Draw the custom cursor
			this->m_pGame->Draw(this->m_cursor);
			break;
		case 4: //Game
			//Draw the game background
			this->m_pGame->Draw(this->m_background);
			//Draw the player ship and laser shots
			this->m_Player.Draw(*this->m_pGame);
			//Draw the small asteroids
			for(int i = 0; i < this->m_smallAsteroids; i++)
			{
				this->m_smlAst[i].Draw(*this->m_pGame);
			}
			//Draw the larger asteroids
			for(int i = 0; i < this->m_largeAsteroids; i++)
			{
				this->m_lrgAst[i].Draw(*this->m_pGame);
			}
			//Draw the pause, won, loss overlays and buttons
			if(this->m_isPaused)
			{
				this->m_pGame->Draw(this->m_pause);
				this->m_pGame->Draw(this->m_cursor);
				this->m_menuButton.Draw(*this->m_pGame);
				this->m_resumeButton.Draw(*this->m_pGame);
			}
			else if(this->m_isLost)
			{
				this->m_pGame->Draw(this->m_gameover);
				this->m_pGame->Draw(this->m_cursor);
				this->m_menuButton.Draw(*this->m_pGame);
			}
			else if(this->m_isWon)
			{
				this->m_pGame->Draw(this->m_gamewon);
				this->m_pGame->Draw(this->m_cursor);
				this->m_menuButton.Draw(*this->m_pGame);
			}
			break;
		case 5: //Credits
			//Draw the credits
			this->m_pGame->Draw(this->m_background);
			this->m_pGame->Draw(this->m_credits);
			break;
		}
	}
private:
	sf::RenderWindow* m_pGame;
	int m_gamestate;
	CData* m_data;
	sf::Clock m_clock;
	CErrorlog m_log;
	bool m_isSoundOff;
	sf::Text m_musicText;
	sf::Font m_crayonFont;
	sf::Image m_cursorBuffer;
	sf::Sprite m_cursor;
	sf::Image m_backgroundBuffer;
	sf::Sprite m_background;
	sf::Image m_helpOverBuffer;
	sf::Sprite m_helpOver;
	sf::Image m_pauseBuffer;
	sf::Sprite m_pause;
	sf::Image m_creditsBuffer;
	sf::Sprite m_credits;
	sf::Image m_gameoverBuffer;
	sf::Sprite m_gameover;
	sf::Image m_gamewonBuffer;
	sf::Sprite m_gamewon;
	bool m_isPaused;
	bool m_isWon;
	bool m_isLost;
	sf::SoundBuffer m_explosionBuffer;
	sf::Sound m_explosion;
	sf::Image m_splashBuffer;
	sf::Sprite m_splash;
	sf::Image m_titleBuffer;
	sf::Sprite m_title;
	sf::Image m_optionsBuffer;
	sf::Sprite m_options;
	sf::Image m_helpBuffer;
	sf::Sprite m_help;
	sf::SoundBuffer m_overBuffer;
	sf::Sound m_over;
	sf::SoundBuffer m_downBuffer;
	sf::Sound m_down;
	CButton m_startButton;
	CButton m_optionsButton;
	CButton m_helpButton;
	CButton m_quitButton;
	CButton m_menuButton;
	CButton m_onButton;
	CButton m_offButton;
	CButton m_resumeButton;
	int m_smallAsteroids;
	int m_largeAsteroids;
	int m_totalAsteroids;
	bool m_isPressed;
	Player m_Player;
	Object m_smlAst[255], m_lrgAst[255];
};