class dialogueBox
{
public:
	dialogueBox(std::string titleString, int formatTemp);//constructor

	//GETS

	label & getButtonOkay() {return buttonOkay;};
	label & getButtonCancel() {return buttonCancel;};
	label & getTitleText() {return titleText;};

	int getFormat() {return format;};

	sf::RectangleShape & getBoxBackground() {return boxBackground;};

	label & getTextBoxes(unsigned int i);

	std::string getTextBoxString(unsigned int i);

	sf::Text getActiveTextBox();

	//SETS
	void setButtonOkayColor(sf::Color color);
	void setButtonCancelColor(sf::Color color);
	void setActiveTextBoxString(std::string string);
	void updateFormat(int newFormat);

	//OTHER
	void buttonNotHovering(sf::Color color);

private:

	//MEMBERS
	int format;

	sf::Font gameFont;

	sf::Color grey;

	sf::RectangleShape boxBackground;

	label buttonOkay;
	label buttonCancel;
	label titleText;
	label textBoxTemplate;

	std::string title;

	std::vector<label> textBoxes;

	//OTHER
	void configure();
};

//CONSTRUCTOR
dialogueBox::dialogueBox(std::string titleString, int formatTemp): 
	//initializations
	grey(106,106,106), textBoxTemplate(),format(),gameFont(),boxBackground(),
	buttonOkay(),buttonCancel(),titleText(),title(),textBoxes()
{
	gameFont.loadFromFile("Assets/OpenSans-Regular.ttf");
	title = titleString;
	format = formatTemp;
	configure();

	for(unsigned int i = 0; i < format; i++)
	{
		textBoxes.push_back(textBoxTemplate);
	}

	switch (format) //produce text boxes depending on the format of the dialogueBox
	{
	case 1:
		textBoxes[0].setBackPosition(245,225);
		textBoxes[0].setActive(true);
		break;
	case 2:
		textBoxes[0].setBackPosition(245,185);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,225);
		break;
	case 3:
		textBoxes[0].setBackPosition(245,185);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,220);
		textBoxes[2].setBackPosition(245,255);
		break;
	case 4:
		textBoxes[0].setBackPosition(245,175);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,205);
		textBoxes[2].setBackPosition(245,235);
		textBoxes[3].setBackPosition(245,265);
		break;
	case 5:
		textBoxes[0].setBackPosition(245,155);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,185);
		textBoxes[2].setBackPosition(245,215);
		textBoxes[3].setBackPosition(245,245);
		textBoxes[4].setBackPosition(245,275);
		break;
	case 6:
		textBoxes[0].setBackPosition(245,145);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,175);
		textBoxes[2].setBackPosition(245,205);
		textBoxes[3].setBackPosition(245,235);
		textBoxes[4].setBackPosition(245,265);
		textBoxes[5].setBackPosition(245,295);
		break;
	default:
		break;
	}
}


label & dialogueBox::getTextBoxes(unsigned int i)
{
	return textBoxes[i];
}

std::string dialogueBox::getTextBoxString(unsigned int i)
{
	return textBoxes[i].getLabelText().getString().toAnsiString();
}

sf::Text dialogueBox::getActiveTextBox()
{
	for (unsigned int i = 0; i < textBoxes.size(); i++)
	{
		if (textBoxes[i].getActive() == true)
		{
			return textBoxes[i].getLabelText();
		}
	}
}

void dialogueBox::setButtonOkayColor(sf::Color color)
{
	buttonOkay.setBackColor(color);
}

void dialogueBox::setButtonCancelColor(sf::Color color)
{
	buttonCancel.setBackColor(color);
}

void dialogueBox::setActiveTextBoxString(std::string string)
{
	for (unsigned int i = 0; i < textBoxes.size(); i++)
	{
		if (textBoxes[i].getActive() == true)
		{
			textBoxes[i].setString(string);
		}
	}
}

void dialogueBox::updateFormat(int newFormat)
{
	format = newFormat;
	textBoxes.clear();
	for(unsigned int i = 0; i < format; i++)
	{
		textBoxes.push_back(textBoxTemplate);
	}

	switch (format)
	{
	case 1:
		textBoxes[0].setBackPosition(245,225);//225
		textBoxes[0].setActive(true);
		break;
	case 2:
		textBoxes[0].setBackPosition(245,185);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,225);
		break;
	case 3:
		textBoxes[0].setBackPosition(245,185);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,220);
		textBoxes[2].setBackPosition(245,255);
		break;
	case 4:
		textBoxes[0].setBackPosition(245,175);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,205);
		textBoxes[2].setBackPosition(245,235);
		textBoxes[3].setBackPosition(245,265);
		break;
	case 5:
		textBoxes[0].setBackPosition(245,155);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,185);
		textBoxes[2].setBackPosition(245,215);
		textBoxes[3].setBackPosition(245,245);
		textBoxes[4].setBackPosition(245,275);
		break;
	case 6:
		textBoxes[0].setBackPosition(245,145);
		textBoxes[0].setActive(true);
		textBoxes[1].setBackPosition(245,175);
		textBoxes[2].setBackPosition(245,205);
		textBoxes[3].setBackPosition(245,235);
		textBoxes[4].setBackPosition(245,265);
		textBoxes[5].setBackPosition(245,295);
		break;
	default:
		break;
	}
}

void dialogueBox::buttonNotHovering(sf::Color color)
{
	buttonOkay.setBackColor(color);
	buttonCancel.setBackColor(color);
}

void dialogueBox::configure()
{
	boxBackground.setPosition(80, 100);
	boxBackground.setSize(sf::Vector2f(480.f, 280.f));
	boxBackground.setFillColor(sf::Color::Black);
	boxBackground.setOutlineColor(sf::Color::White);
	boxBackground.setOutlineThickness(5);

	buttonOkay.setBackPosition(160, 340);
	buttonOkay.setBackSize(100,30);
	buttonOkay.setBackColor(grey);
	buttonOkay.setString("OKAY");
	buttonOkay.setTextColor(sf::Color::White);
	buttonOkay.setCharacterSize(12);
	buttonOkay.setFont(gameFont);
	buttonOkay.getBackground().setOutlineColor(sf::Color::White);
	buttonOkay.getBackground().setOutlineThickness(2);

	buttonCancel.setBackPosition(380, 340);
	buttonCancel.setBackSize(100,30);
	buttonCancel.setBackColor(grey);
	buttonCancel.setString("CANCEL");
	buttonCancel.setTextColor(sf::Color::White);
	buttonCancel.setCharacterSize(12);
	buttonCancel.setFont(gameFont);
	buttonCancel.getBackground().setOutlineColor(sf::Color::White);
	buttonCancel.getBackground().setOutlineThickness(2);

	titleText.setBackPosition(80,100);
	titleText.setBackColor(sf::Color::Black);
	titleText.setBackSize(480,50);
	titleText.setString(title);
	titleText.setTextColor(sf::Color::White);
	titleText.setCharacterSize(18);
	titleText.setFont(gameFont);

	textBoxTemplate.setBackColor(sf::Color::White);
	textBoxTemplate.setBackSize(150,25);
	textBoxTemplate.setTextColor(sf::Color::Black);
	textBoxTemplate.setCharacterSize(16);
	textBoxTemplate.setFont(gameFont);
}



