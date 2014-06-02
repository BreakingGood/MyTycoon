class label
{
public:
	label();//constructor

	//GETS

	bool getActive() {return active;}; //Can be used for many purposes, particularly drawing at appropriate times

	sf::RectangleShape & getBackground();
	sf::Text & getLabelText();
	
	//SETS
	void setFont(sf::Font & font);
	void setString(std::string string);
	void setCharacterSize(int size);
	void setTextColor(sf::Color color);
	void setBackColor(sf::Color color);
	void setBackSize(float x, float y);
	void setBackPosition(float x, float y);
	void setActive(bool activeState);

	//OTHER
	bool isHovering(sf::RenderWindow & window);

private:
	//MEMBERS
	int posX,posY;

	sf::RectangleShape background;

	sf::Text labelText;	

	bool active;
};

//CONSTRUCTOR
label::label():
//initializations
background(), labelText(), active(false), posX(), posY()
{

}


sf::RectangleShape & label::getBackground()
{
	return background;
}

sf::Text & label::getLabelText()
{	//This will center the text in the background rectangle before it is returned, compensates for outline thickness
	posX = static_cast<int>(background.getPosition().x + (((background.getGlobalBounds().width - (background.getOutlineThickness() * 2)) - labelText.getGlobalBounds().width)/2));
	posY = static_cast<int>(background.getPosition().y + (((background.getLocalBounds().height - (background.getOutlineThickness() * 2)) - labelText.getLocalBounds(). height)/2));

	labelText.setPosition(posX,posY);
	return labelText;
}

void label::setFont(sf::Font & font)
{
	labelText.setFont(font);
}

void label::setString(std::string string)
{
	labelText.setString(string);
}

void label::setCharacterSize(int size)
{
	labelText.setCharacterSize(size);
}

void label::setTextColor(sf::Color color)
{
	labelText.setColor(color);
}

void label::setBackColor(sf::Color color)
{
	background.setFillColor(color);
}

void label::setBackSize(float x, float y)
{
	background.setSize(sf::Vector2f(x,y));
}

void label::setBackPosition(float x, float y)
{
	background.setPosition(sf::Vector2f(x,y));
}

void label::setActive(bool activeState)
{
	active = activeState;
}

bool label::isHovering(sf::RenderWindow & window)
{	
	if	  ((sf::Mouse::getPosition(window).x >= background.getPosition().x)	//if mouse is at least at the left bound of the rectangle
		&& (sf::Mouse::getPosition(window).x <= background.getPosition().x + background.getGlobalBounds().width)	//if mouse is before the right bound
		&& (sf::Mouse::getPosition(window).y >= background.getPosition().y)	//if mouse if below the top bound
		&& (sf::Mouse::getPosition(window).y <= background.getPosition().y + background.getGlobalBounds().height))	//if mouse is above the bottom bound
	{
		return true;
	}
	else 
		return false;
}


