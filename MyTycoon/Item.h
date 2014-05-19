class item
{
public:
	item(float numberOfIngredients);//constructor

	//GETS

	float getNumberOfIngredients() {return numberOfIngredients;};
	float getUserPrice() {return userPrice;};
	float getDefaultPrice() {return defaultPrice;};
	float getDesirability() {return desirability;};

	bool getActive() {return active;};

	std::string getMeasuringUnit() {return measuringUnit;};
	std::string getName() {return name;};

	float getIdealRecipe(unsigned int ingredientIndex);
	float getUserRecipe(unsigned int ingredientIndex);

	std::string getRecipeIngredients(unsigned int i);

	//SETS
	void setName(std::string nameTemp);
	void setUserPrice(float price);
	void setDefaultPrice(float price);
	void setMeasuringUnit(std::string nameTemp);
	void setUserRecipe(unsigned int ingredientIndex, float value);
	void setIdealRecipe(unsigned int ingredientIndex, float value);
	void setRecipeIngredients(unsigned int i, std::string nameTemp);
	void setDesirability(float value);
	void setActive(bool isActive);
	
private:
	//MEMBERS
	bool active;

	float userPrice;//eg. $50
	float defaultPrice;
	float numberOfIngredients;
	float desirability;

	std::string name;
	std::string measuringUnit; //ounce

	std::vector<float> userRecipe; //stores the percentages as whole numbers eg: 50 for ingredient 1 
	std::vector<float> idealRecipe;
	std::vector<std::string> recipeIngredients; //stores the actual name eg: Rotten Fruit for ingredient 1
};

//CONSTRUCTOR
item::item(float numIngredients)
	//Initializations
	: name(),userPrice(),measuringUnit(),userRecipe(),idealRecipe(),recipeIngredients(),desirability(), numberOfIngredients(),
	active(), defaultPrice()
{
	for (int i = 0; i < numIngredients; i++) //Use the constructor argument to push back the number of ingredients
	{
		userRecipe.push_back(0);
		idealRecipe.push_back(0);
		recipeIngredients.push_back(""); //push back a blank string for the name that will be changed later
	}

	numberOfIngredients = numIngredients;
} 


float item::getIdealRecipe(unsigned int ingredientIndex)
{
	return idealRecipe[ingredientIndex];
}

float item::getUserRecipe(unsigned int ingredientIndex)
{
	return userRecipe[ingredientIndex];
}

std::string item::getRecipeIngredients(unsigned int i)
{
	return recipeIngredients[i];
}

void item::setName(std::string nameTemp)
{
	name = nameTemp;
}

void item::setUserPrice(float price)
{
	userPrice = price;
}

void item::setDefaultPrice(float price)
{
	defaultPrice = price;
}

void item::setMeasuringUnit(std::string nameTemp)
{
	measuringUnit = nameTemp;
}

void item::setUserRecipe(unsigned int ingredientIndex, float value)
{
	userRecipe[ingredientIndex] = value;
}

void item::setIdealRecipe(unsigned int ingredientIndex, float value)
{
	idealRecipe[ingredientIndex] = value;
}

void item::setRecipeIngredients(unsigned int i, std::string nameTemp)
{
	recipeIngredients[i] = nameTemp;
}

void item::setDesirability(float value)
{
	desirability = value;
}

void item::setActive(bool isActive)
{
	active = isActive;
}

