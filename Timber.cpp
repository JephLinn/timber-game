// Timber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// This is where our game starts from

// Incluce important libraries here
#include <sstream>
#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

// Function declarations
void udpateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite spriteBranches[NUM_BRANCHES];

//Where is the player/branch? Left or right
//Left of Right
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main()
{

	// Create a video mode object

	VideoMode vm{ {1920, 1080} };

	// Create and open a window for the game

	RenderWindow window(vm, "Timber!!!", State::Fullscreen);

	//Create a texture to hold a graphic on the GPU and Load a graphic into it
	Texture textureBackground("graphics/background.png");

	// Load a graphic into the texture alternatively
	//textureBackground.loadFromFile("graphics/background.png");

	//Create a sprite and Assign the texture to it
	Sprite spriteBackground(textureBackground);

	//Attach the texture to the sprite alternatively
	//spriteBackground.setTexture(textureBackground);

	// Set the spritebackgroud to cover the whole screen
	spriteBackground.setPosition({ 0, 0 });

	//Make a tree sprite
	Texture textureTree("graphics/tree.png");
	Sprite spriteTree(textureTree);
	spriteTree.setPosition({ 810, 0 });

	// Prepare the bee sprite
	Texture textureBee("graphics/bee.png");
	Sprite spriteBee(textureBee);
	spriteBee.setPosition({ 0, 800 });

	// Is the bee currently moving?
	bool beeActive = false;

	// How fast can the bee fly?
	float beeSpeed = 0.0f;

	// make 3 cloud sprites from 1 texture
	Texture textureCloud("graphics/cloud.png");

	// 3 New cloud sprites from the same texture
	Sprite spriteCloud1(textureCloud);
	Sprite spriteCloud2(textureCloud);
	Sprite spriteCloud3(textureCloud);

	// Position the clouds on the left of the screen and at different heights
	spriteCloud1.setPosition({ 0, 0 });
	spriteCloud2.setPosition({ 0, 250 });
	spriteCloud3.setPosition({ 0, 500 });

	// Are the clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	// How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Variable to control time itself
	Clock clock;

	// Time Bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f({ timeBarStartWidth, timeBarHeight }));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition({ (1920 / 2.0f) - (timeBarStartWidth / 2.0f), 980 });

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//Track whether the game is running
	bool paused = true;

	//We need to load a font
	Font font("font/KOMIKAP_.ttf");
	
	//Draw some text
	int score = 0;
	Text messageText(font);
	Text scoreText(font);

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Position the text (Will fix later.)
	/*FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f );*/

	messageText.setPosition({ 1920 / 2.0f, 1080 / 2.0f });

	scoreText.setPosition({ 20, 20 });



	while (window.isOpen())
	{
		/*
		Handle the player input
		*/

		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
		{
			paused = false;

			// Reset the time and score
			score = 0;
			timeRemaining = 6.0f;
		}

		/*
		Update the scene
		*/

		if (!paused)
		{

			//Measure Time
			Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			// Size up the time bar
			timeBar.setSize(
				Vector2f({ timeBarWidthPerSecond * timeRemaining, timeBarHeight }));

			if (timeRemaining <= 0.0f)
			{
				// Pause the game
				paused = true;
				// Change the message shown to the player
				messageText.setString("Out of time!!\nPress Enter to restart!");
				// Reposition the message
				/*FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(
					textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				messageText.setPosition({ 1920 / 2.0f, 1080 / 2.0f });*/
			}

			//Setup the bee
			if (!beeActive)
			{
				// How fast is the bee
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				// How high is the bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition({ 2000, height });
				beeActive = true;
			}

			else
				// Move the bee
			{
				spriteBee.setPosition({
					spriteBee.getPosition().x -
					(beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y
					});

				// Has the bee reached the left side of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					// Set it up to be a new bee next frame
					beeActive = false;
				}
			}

			// Manage the clouds
			// Cloud 1
			if (!cloud1Active)
			{

				// How fast is the cloud
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition({ -200, height });
				cloud1Active = true;


			}

			else
			{
				spriteCloud1.setPosition(
					{
					spriteCloud1.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y
					});

				// Has the cloud reached the right side of the screen?
				if (spriteCloud1.getPosition().x > 1920)
				{
					//Set it up to be a new cloud next frame
					cloud1Active = false;
				}
			}

			// Cloud 2
			if (!cloud2Active)
			{

				// How fast is the cloud
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition({ -200, height });
				cloud2Active = true;


			}

			else
			{
				spriteCloud2.setPosition(
					{
					spriteCloud2.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y
					});

				// Has the cloud reached the right side of the screen?
				if (spriteCloud2.getPosition().x > 1920)
				{
					//Set it up to be a new cloud next frame
					cloud2Active = false;
				}
			}

			//Cloud 3

			if (!cloud3Active)
			{

				// How fast is the cloud
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition({ -200, height });
				cloud3Active = true;


			}

			else
			{
				spriteCloud3.setPosition(
					{
					spriteCloud3.getPosition().x +
					(cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y
					});

				// Has the cloud reached the right side of the screen?
				if (spriteCloud3.getPosition().x > 1920)
				{
					//Set it up to be a new cloud next frame
					cloud3Active = false;
				}
			}

			// Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
		} //End if(!paused)

		/*
		Draw the Scene
		*/

		// Clear everything from the last frame 

		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Draw the tree
		window.draw(spriteTree);

		// Draw the bee
		window.draw(spriteBee);

		//Draw the Score
		window.draw(scoreText);

		window.draw(timeBar);

		if (paused)
		{
			// Draw the message
			window.draw(messageText);
		}

		// Show everything we just drew 

		window.display();

	}

	return 0;
}