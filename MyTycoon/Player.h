class player
{
public:
	player();//constructor

	//GETS

	int getGreed() {return greed;};
	int getRuthlessness() {return ruthlessness;};
	int getInsanity() {return insanity;};
	int getWillpower() {return willpower;};
	int getCharm() {return charm;};

	float getLocationExposure() {return locationExposure;};
	float getPopularityBonus() {return popularityBonus;};
	float getPopularity() {return popularity;};
	float getMoney() {return money;};

	//SETS
	void setGreed(int num);
	void setRuthlessness(int num);
	void setInsanity(int num);
	void setWillpower(int num);
	void setCharm(int num);
	void setLocationExposure(float exposure);
	void setPopularityBonus(float bonus);
	void setPopularity(float pop);
	void setMoney(float tempMoney);

private:
	//MEMBERS
	int greed, ruthlessness, insanity, willpower, charm;

	float locationExposure;
	float popularityBonus;
	float popularity;
	float money;

};

//CONSTRUCTOR
player::player()
	//Initializations
	:greed(),ruthlessness(),insanity(),willpower(),charm(), locationExposure(), popularityBonus(), 
	popularity(), money()
{
	greed = 1;
	ruthlessness = 2;
	insanity = 3;
	willpower = 2;
	charm = 4;

	locationExposure = 5; //starting value
	popularityBonus = 0; //starting value
	popularity = 0; //starting value
	money = 50; //starting value
}


void player::setGreed(int num)
{
	greed = num;
}

void player::setRuthlessness(int num)
{
	ruthlessness = num;
}

void player::setInsanity(int num)
{
	insanity = num;
}

void player::setWillpower(int num)
{
	willpower = num;
}

void player::setCharm(int num)
{
	charm = num;
}

void player::setLocationExposure(float exposure)
{
	locationExposure = exposure;
}

void player::setPopularityBonus(float bonus)
{
	popularityBonus = bonus;
}

void player::setPopularity(float pop)
{
	popularity = pop;
}

void player::setMoney(float tempMoney)
{
	money = tempMoney;
}