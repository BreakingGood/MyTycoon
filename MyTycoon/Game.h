class game
{
public:
	game();//constructor

	//GETS
	sf::Font getGameFont() {return gameFont;};
	std::vector<label> getItemInfo() {return itemInfo;};
	std::vector<label> getSalesInfo() {return salesInfo;};
	std::vector<label> getGeneralInfo() {return generalInfo;};
	std::vector<item> getAllItems() {return allItems;};

	sf::Text getStartScreenText();
	sf::Text & getStatScreen(unsigned int i);

	item getActiveItem();

	float calculateTotalCustomers(player & player);
	float calculatePayingCustomers(player & player);

	label & getRectStartDay() {return rectStartDay;};
	label & getRectChangePrice() {return rectChangePrice;};
	label & getRectChangeRecipe() {return rectChangeRecipe;};

	label & getRectGroupGeneralInfo() {return rectGroupGeneralInfo;};
	label & getRectTotalMoney() {return rectTotalMoney;};
	label & getRectTimeLeft() {return rectTimeLeft;};
	label & getRectPopularity() {return rectPopularity;};

	label & getRectGroupSalesInfo() {return rectGroupSalesInfo;};
	label & getRectCustomers() {return rectCustomers;};
	label & getRectSales() {return rectSales;};
	label & getRectProfit() {return rectProfit;};

	label & getRectGroupItemInfo() {return rectGroupItemInfo;};
	label & getRectName() {return rectName;};
	label & getRectPrice() {return rectPrice;};
	label & getRectQuality() {return rectQuality;};

	label & getRecipeInfo(unsigned int i);

	//SETS
	void updateName(std::string string);
	void updatePrice(float price);
	//update recipe
	void updateQuality(float quality);
	//set active item
	void updateCustomers(unsigned int customers);
	void updateSales(unsigned int sales);
	void updateProfit(float profit);
	void updateTotalMoney(float money);
	void updateTimeLeft(sf::Time time);
	void updatePopularity(int popularity);
	void updateUiLabels(player & player, float totalCost, float sales, float totalProfit, sf::Time & secondsRemaining);
	void updateStatScreen(player & player);
	void adjustPopularity(player & player);

	//OTHER
	void mainUiSetup();
	sf::Font gameFont;

private:
	
	//MEMBERS
	label rectChangePrice;
	label rectChangeRecipe;
	label rectGroupItemInfo;
	label rectName;
	label rectPrice;
	label rectQuality;
	label rectGroupSalesInfo;
	label rectCustomers;
	label rectSales;
	label rectProfit;
	label rectGroupGeneralInfo;
	label rectTotalMoney;
	label rectTimeLeft;
	label rectPopularity;
	label rectStartDay;

	std::vector<label> itemInfo;
	std::vector<label> salesInfo;
	std::vector<label> generalInfo;
	std::vector<label> recipeInfo;

	std::vector<item> allItems;

	std::vector<sf::Text> statList;

	sf::Text startText;

	sf::Color grey;
	sf::Color darkGrey;
	sf::Color pink;
	sf::Color darkBlue;

	item trashNBurn;
	item flashFlood;
	
	std::string tempString;
	std::ostringstream ss;
	int seconds;

	//GETS
	float calculateQuality();
	float calculateIdealPrice();
	float calculatePriceQuality();

	//SETS
	void updateItemInfo();
	void updateSalesInfo();
	void updateGeneralInfo();
	void updateRecipeInfo();

	//DEBUG
	sf::Clock debugClock;
	sf::Time debugTime;
	int debugInt;

	//OTHER
	void configureTrashNBurn();
	void configureFlashFlood();

	/*Process of adding new item:
	Create new items object "item"
	Make a configureItem function
	Call the configureItem function in the constructor
	Add the item to the allItems vector
	*/
};

game::game()
	:gameFont(), startText(), grey(155,155,155), darkGrey(106,106,106), pink(247,81,142),
	trashNBurn(2), flashFlood(3), darkBlue(43,131,108)
{
	gameFont.loadFromFile("Assets/OpenSans-Regular.ttf");
	
	sf::Text text;
	for (unsigned int i = 0; i < 8; i++)
	{
		statList.push_back(text);
		statList[i].setFont(gameFont);
		statList[i].setCharacterSize(30);
		statList[i].setColor(sf::Color::White);
		statList[i].setPosition(230.f, ((i * 50) + 75));
	}

	configureTrashNBurn();
	configureFlashFlood();

	allItems.push_back(trashNBurn);
	allItems.push_back(flashFlood);

	updateRecipeInfo();

	
	
}

sf::Text game::getStartScreenText()
{
	startText.setFont(gameFont);
	startText.setCharacterSize(30);
	startText.setColor(sf::Color::White);
	startText.setString("CLICK TO START");
	startText.setOrigin(static_cast<int>(startText.getGlobalBounds().width/2),static_cast<int>(startText.getGlobalBounds().height/2));
	startText.setPosition(320,200);
	return startText;
}

void game::updateStatScreen(player & player)
{
	statList[0].setString("STATS");
	statList[0].setPosition(270,40);
	statList[0].setColor(sf::Color::Red);
	statList[0].setCharacterSize(50);

	std::string statString = "";
	statString = "Greed: " + std::to_string((_ULonglong)player.getGreed()); //convert returned int to a string
	statList[1].setString(statString);
	
	statString.clear();
	statString = "Ruthlessness: " + std::to_string((_Longlong)player.getRuthlessness());
	statList[2].setString(statString);

	statString.clear();
	statString = "Charm: " + std::to_string((_ULonglong)player.getCharm());
	statList[3].setString(statString);

	statString.clear();
	statString = "Willpower: " + std::to_string((_ULonglong)player.getWillpower());
	statList[4].setString(statString);

	statString.clear();
	statString = "Insanity: " + std::to_string((_ULonglong)player.getInsanity());
	statList[5].setString(statString);

	statList[6].setString("CLICK TO CONTINUE");
	statList[6].setPosition(150,400);
	statList[6].setColor(sf::Color::Green);
	statList[6].setCharacterSize(40);
}

sf::Text & game::getStatScreen(unsigned int i)
{
	return statList[i];
}

void game::mainUiSetup()
{
	rectName.setBackColor(sf::Color::Red);
	rectName.setBackSize(140, 50);
	rectName.setBackPosition(500,10);

	rectName.setFont(gameFont);
	rectName.setCharacterSize(20);
	rectName.setTextColor(sf::Color::White);
	//
	rectPrice.setBackColor(sf::Color::Red);
	rectPrice.setBackSize(140, 50);
	rectPrice.setBackPosition(500,80);

	rectPrice.setFont(gameFont);
	rectPrice.setCharacterSize(20);
	rectPrice.setTextColor(sf::Color::White);
	//
	rectQuality.setBackColor(sf::Color::Blue);
	rectQuality.setBackSize(140, 50);
	rectQuality.setBackPosition(500,150);

	rectQuality.setFont(gameFont);
	rectQuality.setCharacterSize(20);
	rectQuality.setTextColor(sf::Color::White);
	//
	rectGroupItemInfo.setBackColor(pink);
	rectGroupItemInfo.setBackPosition(490,0);
	rectGroupItemInfo.setBackSize(150,220);

	rectGroupItemInfo.setFont(gameFont);
	rectGroupItemInfo.setCharacterSize(2);
	rectGroupItemInfo.setString("");
	rectGroupItemInfo.setTextColor(sf::Color::White);
	//
	updateItemInfo(); //clear and repopulate the itemInfo vector
	//
	//
	//
	rectCustomers.setBackColor(grey);
	rectCustomers.setBackSize(140, 50);
	rectCustomers.setBackPosition(0,10);

	rectCustomers.setFont(gameFont);
	rectCustomers.setCharacterSize(17);
	rectCustomers.setTextColor(sf::Color::White);
	//
	rectSales.setBackColor(grey);
	rectSales.setBackSize(140, 50);
	rectSales.setBackPosition(0,80);

	rectSales.setFont(gameFont);
	rectSales.setCharacterSize(20);
	rectSales.setTextColor(sf::Color::White);
	//
	rectProfit.setBackColor(grey);
	rectProfit.setBackSize(140, 50);
	rectProfit.setBackPosition(0,150);

	rectProfit.setFont(gameFont);
	rectProfit.setCharacterSize(20);
	rectProfit.setTextColor(sf::Color::White);
	//
	rectGroupSalesInfo.setBackColor(darkGrey);
	rectGroupSalesInfo.setBackPosition(0,0);
	rectGroupSalesInfo.setBackSize(150,210);

	rectGroupSalesInfo.setFont(gameFont);
	rectGroupSalesInfo.setCharacterSize(2);
	rectGroupSalesInfo.setString("");
	rectGroupSalesInfo.setTextColor(sf::Color::White);
	//
	updateSalesInfo(); //clear and repopulate the salesInfo vector
	//
	//
	//
	rectStartDay.setBackColor(sf::Color::Yellow);
	rectStartDay.setBackSize(140, 50);
	rectStartDay.setBackPosition(250,0);
	
	rectStartDay.setFont(gameFont);
	rectStartDay.setCharacterSize(20);
	rectStartDay.setString("START DAY");
	rectStartDay.setTextColor(sf::Color::Black);
	//
	//
	//
	rectTotalMoney.setBackColor(sf::Color::Blue);
	rectTotalMoney.setBackSize(140, 50);
	rectTotalMoney.setBackPosition(250,100);

	rectTotalMoney.setFont(gameFont);
	rectTotalMoney.setCharacterSize(20);
	rectTotalMoney.setTextColor(sf::Color::White);
	//
	//
	//
	rectTimeLeft.setBackColor(sf::Color::Blue);
	rectTimeLeft.setBackSize(140, 50);
	rectTimeLeft.setBackPosition(250,170);

	rectTimeLeft.setFont(gameFont);
	rectTimeLeft.setCharacterSize(20);
	rectTimeLeft.setTextColor(sf::Color::White);
	//
	rectPopularity.setBackColor(sf::Color::Green);
	rectPopularity.setBackSize(140, 50);
	rectPopularity.setBackPosition(250,430);

	rectPopularity.setFont(gameFont);
	rectPopularity.setCharacterSize(20);
	rectPopularity.setTextColor(sf::Color::Black);
	//
	rectGroupGeneralInfo.setBackColor(darkGrey);
	rectGroupGeneralInfo.setBackPosition(240,90);
	rectGroupGeneralInfo.setBackSize(160,140);

	rectGroupGeneralInfo.setFont(gameFont);
	rectGroupGeneralInfo.setCharacterSize(2);
	rectGroupGeneralInfo.setString("");
	rectGroupGeneralInfo.setTextColor(sf::Color::White);
	//
	rectChangePrice.setBackColor(pink);
	rectChangePrice.setBackPosition(55,410);
	rectChangePrice.setBackSize(140, 50);

	rectChangePrice.setFont(gameFont);
	rectChangePrice.setCharacterSize(20);
	rectChangePrice.setString("Change Price");
	rectChangePrice.setTextColor(sf::Color::White);
	//
	rectChangeRecipe.setBackColor(pink);
	rectChangeRecipe.setBackPosition(55,340);
	rectChangeRecipe.setBackSize(140, 50);

	rectChangeRecipe.setFont(gameFont);
	rectChangeRecipe.setCharacterSize(20);
	rectChangeRecipe.setString("Change Recipe");
	rectChangeRecipe.setTextColor(sf::Color::White);
	//
	updateGeneralInfo(); //clear and repopulate the generalInfo vector
	//
}

void game::updateUiLabels(player & player, float totalCustomers, float sales, float totalProfit, sf::Time & secondsRemaining)
{
	seconds = 0;

	for(unsigned int i = 0; i < allItems.size(); i++)
	{
		if (allItems[i].getActive() == true)
		{
			tempString = allItems[i].getName(); //get name of active item
			rectName.setString(tempString); //set the label string to said name

			ss << allItems[i].getUserPrice(); //push the user price to a stringstream
			tempString = "$" + ss.str() + "/" + allItems[i].getMeasuringUnit(); //use the stringstream to compose a string
			ss.str(""); //clear the stringstream
			rectPrice.setString(tempString); //set the label text as the composed string

			ss << calculateQuality();
			tempString = ss.str() + "% quality"; //60% Quality
			ss.str("");
			rectQuality.setString(tempString);

			ss << totalCustomers;
			tempString = ss.str() + " Customers";
			ss.str("");
			rectCustomers.setString(tempString);

			ss << sales;
			tempString = ss.str() + " Sales";
			ss.str("");
			rectSales.setString(tempString);

			ss << totalProfit;
			tempString = "$" + ss.str() + " Profit";
			ss.str("");
			rectProfit.setString(tempString);

			ss << player.getMoney();
			tempString = "$" + ss.str();
			ss.str("");
			rectTotalMoney.setString(tempString);

			seconds = secondsRemaining.asSeconds();
			ss << seconds;
			tempString = ss.str() + " Hours";
			ss.str("");
			rectTimeLeft.setString(tempString);

			ss << player.getPopularity();
			tempString = ss.str() + " Popularity";
			ss.str("");
			rectPopularity.setString(tempString);
		}
	}
}

void game::updateName(std::string string)
{
	rectName.setString(string);
	updateItemInfo();
}

void game::updatePrice(float price)
{
	std::string tempString;
	std::ostringstream ss;
	ss << price;
	tempString = "$" + ss.str() + "/Ounce";
	rectPrice.setString(tempString);
	updateItemInfo();
}

void game::updateQuality(float quality)
{
	std::string tempString;
	std::ostringstream ss;
	ss << quality;
	tempString = ss.str() + "% Quality";
	rectQuality.setString(tempString);
	updateItemInfo();
}

void game::updateCustomers(unsigned int customers)
{
	std::string tempString;
	std::ostringstream ss;
	ss << customers;
	tempString = ss.str() + " Customers";
	rectCustomers.setString(tempString);
	updateSalesInfo();
}

void game::updateSales(unsigned int sales)
{
	std::string tempString;
	std::ostringstream ss;
	ss << sales;
	tempString = ss.str() + " Sales";
	rectSales.setString(tempString);
	updateSalesInfo();
}

void game::updateProfit(float profit)
{
	std::string tempString;
	std::ostringstream ss;
	ss << profit;
	tempString = "$" + ss.str() + " Profit";
	rectProfit.setString(tempString);
	updateSalesInfo();
}

void game::updateTotalMoney(float money)
{
	std::string tempString;
	std::ostringstream ss;
	ss << money;
	tempString = "$" + ss.str();
	rectTotalMoney.setString(tempString);
	updateGeneralInfo();
}

void game::updateTimeLeft(sf::Time time)
{
	float tempFloat;
	std::string tempString;
	std::ostringstream ss;
	tempFloat = time.asSeconds();
	ss << tempFloat;
	tempString = ss.str() + " Hours";
	rectTimeLeft.setString(tempString);
	updateGeneralInfo();
}

void game::updatePopularity(int popularity)
{
	std::string tempString;
	std::ostringstream ss;
	ss << popularity;
	tempString = ss.str() + " Popularity";
	rectPopularity.setString(tempString);
}

void game::updateGeneralInfo()
{
	generalInfo.clear();
	generalInfo.push_back(rectGroupGeneralInfo);
	generalInfo.push_back(rectTotalMoney);
	generalInfo.push_back(rectTimeLeft);
	generalInfo.push_back(rectPopularity);
	generalInfo.push_back(rectChangePrice);
	generalInfo.push_back(rectChangeRecipe);
}

void game::updateSalesInfo()
{
	salesInfo.clear();
	salesInfo.push_back(rectGroupSalesInfo);
	salesInfo.push_back(rectSales);
	salesInfo.push_back(rectCustomers);
	salesInfo.push_back(rectProfit);
}

void game::updateItemInfo()
{
	itemInfo.clear();
	itemInfo.push_back(rectGroupItemInfo);
	itemInfo.push_back(rectName);
	itemInfo.push_back(rectPrice);
	itemInfo.push_back(rectQuality);
}

void game::updateRecipeInfo()
{
	std::ostringstream ss;
	label tempLabel;

	for(unsigned int i = 0; i < allItems.size(); i++)
	{
		if (allItems[i].getActive() == true)
		{
			for (int j = 0; j < allItems[i].getNumberOfIngredients(); j++) //for all ingredients in the active item
			{
				recipeInfo.push_back(tempLabel); //push back one label per ingredient 

				recipeInfo[j].setBackColor(darkBlue);
				recipeInfo[j].setBackSize(140, 40);
				recipeInfo[j].setBackPosition(500.f,(430 - (50 * j)));	//configure the labels for the ingredients
				recipeInfo[j].setFont(gameFont);						//These are the green labels that display	
				recipeInfo[j].setCharacterSize(15);						//the ingredient & the percentage of each one
				recipeInfo[j].setTextColor(sf::Color::White);

				ss << allItems[i].getUserRecipe(j); //get user percentage of the recipe 
				recipeInfo[j].setString(ss.str() + "%" + " " + allItems[i].getRecipeIngredients(j)); //use it to compose a label 
				ss.str("");																			//percentage + % + item name
			}
		}
	}
}

label & game::getRecipeInfo(unsigned int i)
{
	return recipeInfo[i];
}

float game::calculateQuality()
{
	float delta = 0;
	float quality = 0;

	for (unsigned int i = 0; i < allItems.size(); i++)
	{
		if (allItems[i].getActive() == true)
		{
			for (int j = 0; j < allItems[i].getNumberOfIngredients(); j++)
			{
				if (allItems[i].getIdealRecipe(j) < allItems[i].getUserRecipe(j)) //divide user recipe percentage by ideal recipe percentage
					delta = allItems[i].getIdealRecipe(j) / allItems[i].getUserRecipe(j);//for all ingredients in the recipe
				else
					delta = allItems[i].getUserRecipe(j) / allItems[i].getIdealRecipe(j);

				quality = quality + (delta * 1/allItems[i].getNumberOfIngredients()); //then add all of the resulting percentages up
			}
		}
	}

	quality = quality * 100; //then multiply by 100 to get the quality
	return std::ceil(quality);
}

float game::calculateIdealPrice()
{
	float idealPrice;
	for (unsigned int i = 0; i < allItems.size(); i++)
	{
		if (allItems[i].getActive() == true)
		{				//(defaultPrice * 2) * (quality/100)
			idealPrice = ((allItems[i].getDefaultPrice() * 2) * (calculateQuality() / 100));
		}
	}
	return std::ceil(idealPrice);
}

float game::calculatePriceQuality()
{
	float priceQuality = 0.f;
	for (unsigned int i = 0; i < allItems.size(); i++)
	{
		if (allItems[i].getActive() == true)
		{				//ideal price / user price
			priceQuality = calculateIdealPrice()/allItems[i].getUserPrice();
		}
	}

	return priceQuality;
}

void game::adjustPopularity(player & player)
{
	if((calculateQuality() > 85.f) && (player.getPopularity() < 100)) //if sheer quality is over 85 & popularity isn't 100
	{																//increase popularity by 1
		player.setPopularity(player.getPopularity() + 1);
	}
	else if ((calculateQuality() < 30.f) && (player.getPopularity() > 0)) //if sheer quality is below 30 & popularity isn't 0
	{																	//reduce popularity by 1
		player.setPopularity(player.getPopularity() - 1);
	}

	if((calculatePriceQuality() > 1.4) && (player.getPopularity() < 100)) //if quality of the user price is above 1.4
	{																	//increase
		player.setPopularity(player.getPopularity() + 1);
		std::cout << player.getPopularity();
	}
	else if ((calculatePriceQuality() < .6) && (player.getPopularity() > 0)) //if quality of price below .6
	{																		//decrease
		player.setPopularity(player.getPopularity() - 1);
	}

	if (player.getPopularity() < player.getPopularityBonus()) //if players popularity is below current popularity bonus amount
	{														//set the total popularity to be equal to the popularity bonus amount
		player.setPopularity(player.getPopularityBonus());
	}
}

float game::calculateTotalCustomers(player & player)
{
	float total = 0;
	for (unsigned int i = 0; i < allItems.size(); i++)
	{
		if (allItems[i].getActive() == true)
		{	//25 (at the end of this equation) is the starting bump to keep early game interesting, it becomes negligible later						
			total = (player.getLocationExposure() * allItems[i].getDesirability() + player.getLocationExposure() * player.getPopularity()) + 25;
		}	//(locationExposure * desirability) + (locationExposure * popularity) + 25
	}
	return total;
}

float game::calculatePayingCustomers(player & player)
{
	float payingCustomers = 0;
	float totalCustomers = 0;

	totalCustomers = calculateTotalCustomers(player);
	payingCustomers = totalCustomers * calculatePriceQuality();

	if(payingCustomers > totalCustomers)
	{
		payingCustomers = totalCustomers;
	}
	return std::ceil(payingCustomers);
}

void game::configureTrashNBurn()
{
	trashNBurn.setName("Trash n' Burn");
	trashNBurn.setUserPrice(80);//80
	trashNBurn.setDefaultPrice(80);//80
	trashNBurn.setMeasuringUnit("Ounce");
	trashNBurn.setUserRecipe(0,50);//0,50
	trashNBurn.setUserRecipe(1,50);//1,50
	trashNBurn.setIdealRecipe(0,30);//0,30
	trashNBurn.setIdealRecipe(1,70);//0,70
	trashNBurn.setRecipeIngredients(0,"Rotten Fruit");
	trashNBurn.setRecipeIngredients(1,"Lighter Fluid");
	trashNBurn.setActive(false);
	trashNBurn.setDesirability(5);
}

void game::configureFlashFlood()
{
	flashFlood.setName("Flash Flood");
	flashFlood.setUserPrice(250); //250
	flashFlood.setDefaultPrice(250); //250
	flashFlood.setMeasuringUnit("fl oz");
	flashFlood.setUserRecipe(0,33); //33
	flashFlood.setUserRecipe(1,33); //33
	flashFlood.setUserRecipe(2,34); //34
	flashFlood.setIdealRecipe(0,10); //10
	flashFlood.setIdealRecipe(1,30); //30
	flashFlood.setIdealRecipe(2,60); //60
	flashFlood.setRecipeIngredients(0,"Magnesium Powder");
	flashFlood.setRecipeIngredients(1,"Steel Shavings");
	flashFlood.setRecipeIngredients(2,"Glacial Spring Water");
	flashFlood.setActive(true);
	flashFlood.setDesirability(10);
}

item game::getActiveItem()
{
	for(unsigned int i = 0; i < allItems.size(); i++)
	{
		if(allItems[i].getActive() == true)
		{
			return allItems[i];
		}
	}
}







