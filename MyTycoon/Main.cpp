#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>//for std::ostringstream to convert floats/ints to strings
#include <iostream>
#include <vector>
#include <string>
#include <cmath>//for std::ceil() 
#include <cstdlib>//for random number generator
#include <ctime>//for seeding the random # gen.
#include "Label.h"
#include "Item.h"
#include "Player.h"
#include "Dialogue_Box.h"
#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "* Tycoon!", sf::Style::Close);


	//CONSTANT GAMEPLAY ELEMENTS
	const int HOURS_PER_DAY = 12;
	const int SPEED_OF_HOUR_MILLISECONDS = 200; //for debugging
	const int SPEED_OF_HOUR_SECONDS = 1; //for actual gameplay

	//GAME & PLAYER OBJECTS
	player player;
	game game;
	//INITIAL LABELS
	game.updateUiLabels(player,0.f,0.f,0.f,sf::seconds(0.f));
	//FPS CLOCK

	sf::Clock debugClock;
	sf::Time debugTime;
	debugClock.restart(); 
	int debugInt = 0;
	//debug clock 2
	sf::Clock testClock;
	sf::Time testTime;
	int testInt = 0;
	//GAME STATES
	enum gameState{START_SCREEN, STAT_MENU, SETUP, DAY_BEGUN, DIALOGUE_PRICE, DIALOGUE_RECIPE};
	int currentState = START_SCREEN;
	//ADDITIONAL COLORS
	sf::Color lightGrey(220,220,220);
	sf::Color grey(106,106,106);
	//GAMEPLAY VARIABLES
	sf::Clock dayClock;
	sf::Time deltaTime;
	bool dayJustStarted = true;
	float totalCustomers = 0;
	float sales = 0;
	float totalProfit = 0;
	float profitThisIteration = 0;
	sf::Time secondsLeft = sf::seconds(60);
	float iterations = 0;
	float calculatedCustomers = 0;
	float calculatedSales = 0;
	bool subtractOffset = true;
	//label TEXT
	std::string labelText;
	//NUMBER FUDGING VARIABLES
	std::srand(static_cast<unsigned int>(time(0)));
	int randomNumber = rand();
	int customerOffset;

	sf::Text testText;
	testText.setPosition(200,200);
	testText.setCharacterSize(40);
	testText.setColor(sf::Color::Yellow);
	testText.setFont(game.gameFont);
	testText.setString("HEREHEREHERE");
	//DIALOGUE BOXES
	dialogueBox dBoxPrice("UPDATE PRICE",1);
	dialogueBox dBoxRecipe("UPDATE RECIPE",6);

//GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP----GAME LOOP
	while (window.isOpen())
	{	
//EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----EVENTS----
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
			{
				if (currentState == START_SCREEN)
				{
					currentState = STAT_MENU;
					game.updateStatScreen(player); //Set up the labels on the stat screen
				}
				else if (currentState == STAT_MENU)
				{
					currentState = SETUP;
					game.mainUiSetup(); //set up all the labels on the main screen
				}
				// VVVVV if mouse clicks in the "Start Day" box
				else if ((currentState == SETUP) && (game.getRectStartDay().isHovering(window)))
				{
					currentState = DAY_BEGUN; 		
					game.updateTimeLeft(sf::seconds(HOURS_PER_DAY)); //Put 12 hours on the timeLeft label.
				}		
				else if ((currentState == SETUP) && (game.getRectChangePrice().isHovering(window)))
				{
					currentState = DIALOGUE_PRICE;
				}
				else if ((currentState == SETUP) && (game.getRectChangeRecipe().isHovering(window)))
				{
					currentState = DIALOGUE_RECIPE;
					if (dBoxRecipe.getFormat() != game.getActiveItem().getNumberOfIngredients())
					{
						dBoxRecipe.updateFormat(game.getActiveItem().getNumberOfIngredients()); //update the recipe dialogue box
					}																			//with the correct number of labels
				}																				//based on the num of ingredients
			}
			if ((event.type == sf::Event::TextEntered) && (currentState == DIALOGUE_PRICE))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) == false)//when button is pressed 
				{
					if (isdigit(event.text.unicode))							//check if it is a number
					{
						labelText += event.text.unicode;						//if yes, add to a string
					}
					dBoxPrice.setActiveTextBoxString(labelText);				//pass the string to the active label
				}												   
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) == true) && (labelText.size() != 0))
				{				//Take a substring of labelText from character 0 to the length minus 1
					labelText = labelText.substr(0, labelText.size()-1);//remove last character of string
					dBoxPrice.setActiveTextBoxString(labelText); //pass the string to the active label
				}
			}
		}
//LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----LOGIC----
		if (currentState == DAY_BEGUN)
		{
			if(dayJustStarted)
			{
				dayClock.restart();
				totalCustomers = 0; 
				sales = 0;
				totalProfit = 0;
				profitThisIteration = 0; //profit this hour
				secondsLeft = sf::seconds(HOURS_PER_DAY);
				iterations = 0; //hours passed
				calculatedCustomers = 0;
				calculatedSales = 0;
				dayJustStarted = false; //This optimizes the code by only doing all calculations once per day
				calculatedCustomers = std::floor(game.calculateTotalCustomers(player) / HOURS_PER_DAY); //calc customers per tick
				calculatedSales = game.calculatePayingCustomers(player);

				
				//CLEAN THIS UP, ADD IT TO THE calculatePayingCustomers	FUNCTION
				if(player.getPopularity() - 50 <= 0)
					calculatedSales = (((((player.getPopularity() - 50) / 5) / 100) + 1) * calculatedSales);//50 is the popularity cutoff, above 50 = more sales, below = less 
				else																						//5 is the increment. For every 5 percent below/above 50, adjust the sales
					calculatedSales = (((((player.getPopularity() - 50) / 5) / 100) - 1) * calculatedSales);//100 is what it is divided by to make it a percentage

				calculatedSales = std::floor(calculatedSales / HOURS_PER_DAY);

				if (calculatedSales > calculatedCustomers)//Make sure there is not more sales than customers
					calculatedSales = calculatedCustomers;

				///////////////////////////////////////////////////////////////////////

				if (calculatedSales != 0)
					customerOffset = (randomNumber % static_cast<int>(calculatedSales)); //this makes it so sales aren't the same every tick
				else
					customerOffset = 0; //this stops it from rounding sales up to 1 when it should be 0
			}

			if ((dayClock.getElapsedTime().asMilliseconds() >= SPEED_OF_HOUR_MILLISECONDS) && (iterations < HOURS_PER_DAY))
			{ 
				if(subtractOffset) //if it is supposed to suctract the offset this tick, it does
				{
					sales = (sales + calculatedSales) - customerOffset;
					totalCustomers = (totalCustomers + calculatedCustomers) - customerOffset; 
					subtractOffset = false;
				}
				else if (!subtractOffset) //if it subtracted the offset last tick, it will instead add it this tick, then reseed random
				{
					sales = (sales + calculatedSales) + customerOffset;
					totalCustomers = (totalCustomers + calculatedCustomers) + customerOffset;
					subtractOffset = true;
					randomNumber = rand();
					if (calculatedSales != 0)
						customerOffset = (randomNumber % static_cast<int>(calculatedSales));
					else
						customerOffset = 0;
				}

				profitThisIteration = calculatedSales * game.getActiveItem().getUserPrice();
				totalProfit = sales * game.getActiveItem().getUserPrice(); 
				player.setMoney(player.getMoney() + profitThisIteration);
				iterations++;
				secondsLeft = secondsLeft - sf::seconds(1);

				game.updateUiLabels(player, totalCustomers, sales, totalProfit, secondsLeft);

				dayClock.restart();
			}
			else if (iterations == HOURS_PER_DAY) //if gone through all iterations
			{
				game.adjustPopularity(player); //adjust the popularity
				currentState = SETUP;
				dayJustStarted = true;
				game.updateUiLabels(player, totalCustomers, sales, totalProfit, secondsLeft);;
			}
		}
		if(currentState == DIALOGUE_PRICE)
		{
			if (dBoxPrice.getButtonOkay().isHovering(window)) //if hovering over buttonOkay, make it blue
				dBoxPrice.setButtonOkayColor(sf::Color::Blue);
			else if (dBoxPrice.getButtonCancel().isHovering(window))
				dBoxPrice.setButtonCancelColor(sf::Color::Red);
			else
				dBoxPrice.buttonNotHovering(grey);
		}

//RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----RENDERING----

		window.clear();

		if(currentState == START_SCREEN)
			window.draw(game.getStartScreenText());

		if(currentState == STAT_MENU)
		{
			for(unsigned int i = 0; i < 8; i++)
			{
				window.draw(game.getStatScreen(i));
			}
		}

		if((currentState == SETUP) || (currentState == DAY_BEGUN) || (currentState == DIALOGUE_PRICE) || (currentState == DIALOGUE_RECIPE))
		{
			//NAME, PRICE, QUALITY
			window.draw(game.getRectGroupItemInfo().getBackground());
			window.draw(game.getRectName().getBackground());
			window.draw(game.getRectPrice().getBackground());
			window.draw(game.getRectQuality().getBackground());
			window.draw(game.getRectName().getLabelText());
			window.draw(game.getRectPrice().getLabelText());
			window.draw(game.getRectQuality().getLabelText());
			//CUSTOMERS, SALES, PROFIT
			window.draw(game.getRectGroupSalesInfo().getBackground());
			window.draw(game.getRectCustomers().getBackground());
			window.draw(game.getRectSales().getBackground());
			window.draw(game.getRectProfit().getBackground());
			window.draw(game.getRectCustomers().getLabelText());
			window.draw(game.getRectSales().getLabelText());
			window.draw(game.getRectProfit().getLabelText());
			//CHANGE PRICE/RECIPE, TOTAL MONEY, TIME LEFT, POPULARITY
			window.draw(game.getRectGroupGeneralInfo().getBackground());
			window.draw(game.getRectChangePrice().getBackground());
			window.draw(game.getRectChangeRecipe().getBackground());
			window.draw(game.getRectTotalMoney().getBackground());
			window.draw(game.getRectTimeLeft().getBackground());
			window.draw(game.getRectChangePrice().getLabelText());
			window.draw(game.getRectChangeRecipe().getLabelText());
			window.draw(game.getRectTotalMoney().getLabelText());
			window.draw(game.getRectTimeLeft().getLabelText());
			window.draw(game.getRectPopularity().getBackground());
			window.draw(game.getRectPopularity().getLabelText());
			
			for(float i = 0; i < game.getActiveItem().getNumberOfIngredients(); i++)
			{
				window.draw(game.getRecipeInfo(i).getBackground());
				window.draw(game.getRecipeInfo(i).getLabelText());
			}

			window.draw(game.getRectStartDay().getBackground());
			window.draw(game.getRectStartDay().getLabelText());	
		}

		//DIALOGUE BOXES
		if (currentState == DIALOGUE_PRICE)
		{
			window.draw(dBoxPrice.getBoxBackground());
			window.draw(dBoxPrice.getButtonOkay().getBackground());
			window.draw(dBoxPrice.getButtonCancel().getBackground());
			window.draw(dBoxPrice.getButtonOkay().getLabelText());
			window.draw(dBoxPrice.getButtonCancel().getLabelText());
			window.draw(dBoxPrice.getTitleText().getLabelText());

			//vv Return the textbox in the price panel
			for (unsigned int i = 0; i < dBoxPrice.getFormat(); i++)
			{
				window.draw(dBoxPrice.getTextBoxes(i).getBackground());
				window.draw(dBoxPrice.getTextBoxes(i).getLabelText());
			}
		}
		else if (currentState == DIALOGUE_RECIPE)
		{
			window.draw(dBoxRecipe.getBoxBackground());
			window.draw(dBoxRecipe.getButtonOkay().getBackground());
			window.draw(dBoxRecipe.getButtonCancel().getBackground());
			window.draw(dBoxRecipe.getButtonOkay().getLabelText());
			window.draw(dBoxRecipe.getButtonCancel().getLabelText());
			window.draw(dBoxRecipe.getTitleText().getLabelText());

			for(unsigned int i = 0; i < dBoxRecipe.getFormat(); i++)
			{
				window.draw(dBoxRecipe.getTextBoxes(i).getBackground());
				window.draw(dBoxRecipe.getTextBoxes(i).getLabelText());
			}
		}

		window.display();	

		//FPS CLOCK
		debugTime = debugClock.getElapsedTime();
		debugInt++;
		if (debugTime.asSeconds() >= 1)
		{
			std::cout << debugInt << std::endl;
			debugInt = 0;
			debugClock.restart();
		}
	}
	return 0;
}