#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Orders for generating minions for each Clan
int redO[5] = { 2, 3, 4, 1, 0 };
int blueO[5] = { 3, 0, 1, 2, 4 };
const static vector<int> red_order(redO, redO + 5);
const static vector<int> blue_order(blueO, blueO + 5);

// Declare life
static int soldLife[5];
static int min_life, arrowAp;

// Declare time
static unsigned int curTime = 0;

class Soldier;
class Clan;

class Base {
protected:
	Base *next, *prev;
public:
	Base() {
		next = NULL;
		prev = NULL;
	}
	void setNext(Base * a) {
		next = a;
	}
	void setPrev(Base * a) {
		prev = a;
	}
	Base * getNext() {
		return next;
	}
	Base * getPrev() {
		return prev;
	}
};

class City : public Base {
	int lifeQuota;
	bool isOccupy;
	bool isEven;
	Soldier * s1, *s2;
	Clan * c;
public:
	City(int a, bool b) : lifeQuota(a), isEven(b), isOccupy(0) {
		s1 = NULL;
		s2 = NULL;
		c = NULL;
	}
	void genQuota(int a) {
		lifeQuota += a;
	}
	void tranfQuota() {
		c->lifeQuota += lifeQuota;
		lifeQuota = 0;
	}
};

class Clan: public Base {
	vector<Soldier *> sdr;
	int lifeQuota;
	string name;
	vector<int> indivNum;
	bool stopStatus;
	vector<int> order;
	int idx;

public:
	Clan(string a, int b, vector<int> c) : name(a), lifeQuota(b), order(c){
		//indivNum[5] = { 0 };
		indivNum.resize(5);
		fill(indivNum.begin(), indivNum.end(), 0);
		stopStatus = 0;
		idx = 0;
	}
	string getName() const { return name; }
	int getQuota() const { return lifeQuota; }
	int soldNum() const { return sdr.size(); }
	int getIndivNum(int a) { return indivNum[a]; }
	void addIndivNum(int a) { indivNum[a]++; }
	void minusIndivNum(int a) { indivNum[a]--; }
	void minusLifeQuota(int a) { lifeQuota -= a; }
	bool isStop() { return !stopStatus; }
	void prodMinion();
	friend class City;
	~Clan() {
		for (vector<Soldier *>::iterator it = sdr.begin(); it != sdr.end(); ++it) {
			delete (*it);
		}
	}
};

class Weapon{
public:
	virtual void wearOff() = 0 {}
	virtual void attack() = 0 {}
};

class Bomb :public Weapon {

};
class Sword :public Weapon {
	int ap;
public:
	Sword(int n) : ap(n) {}
	void wearOff() {
		ap = ap * 0.8;
	}
};
class Arrow :public Weapon {
	int life, ap;
public:
	Arrow() : life(3), ap(arrowAp) {};
	void wearOff() {
		life -= 1;
	}
};

Weapon * genWeapon(int n, int swordP) {
	Weapon * p;
	switch (n) {
	case 0: p = new Sword(swordP); break;
	case 1: p = new Bomb(); break;
	case 2: p = new Arrow(); break;
	default: break;
	}
	return p;
}

class Soldier{
	int life, ap;
protected:
	Clan * s;
	Base * c;
public:
	Soldier(int a, int b, Clan * p) : life(a), ap(b), s(p) {
		p->minusLifeQuota(a);
		c = NULL;
	}
	virtual void print() {
		cout << s->getName();
	}
	virtual void lionEscape() {}
	virtual void march() {
		if (s->getName() == "red") {
			c = c->getNext();
		}
		else if (s->getName() == "blue") {
			c = c->getPrev();
		}
	}
	int getLife() { return life; }
	virtual ~Soldier() {}
};

class Dragon : public Soldier {
	Weapon * w;
	float morale;
public:
	Dragon(int b, Clan * p) : Soldier(soldLife[0], b, p) {
		w = new Weapon((p->soldNum() + 1) % 3);
		morale = (float)p->getQuota() / soldLife[0];
		p->addIndivNum(0);
	}
	void print() {
		Soldier::print();
		cout << " dragon " << s->soldNum() << " born" << endl;
		cout << "It has a " << w->getName() << ",and it's morale is ";
		cout << setprecision(2) << fixed << morale << endl;
	}
	~Dragon() {
		delete w;
		s->minusIndivNum(0);
	}
};

class Ninja :public Soldier {
	Weapon * w[2];
public:
	Ninja(int b, Clan * p) : Soldier(soldLife[1], b, p) {
		w[0] = new Weapon((p->soldNum() + 1) % 3);
		w[1] = new Weapon((p->soldNum() + 2) % 3);
		p->addIndivNum(1);
	}

	void print() {
		Soldier::print();
		cout << " ninja " << s->soldNum() << " born" << endl;
		cout << "It has a " << w[0]->getName() << " and a ";
		cout << w[1]->getName() << endl;
	}

	~Ninja() {
		delete[] w;
		s->minusIndivNum(1);
	}
};

class Iceman :public Soldier {
	Weapon * w;
	int meltLife;
public:
	Iceman(int b, Clan * p) : Soldier(soldLife[2], b, p) {
		w = new Weapon((p->soldNum() + 1) % 3);
		meltLife = 2;
		p->addIndivNum(2);
	}
	void print() {
		Soldier::print();
		cout << " iceman " << s->soldNum() << " born" << endl;
		cout << "It has a " << w->getName() << endl;
	}
	~Iceman() {
		delete w;
		s->minusIndivNum(2);
	}
};

class Lion :public Soldier {
	int loy;
public:
	Lion(int b, Clan * p) : Soldier(soldLife[3], b, p) {
		loy = p->getQuota();
		p->addIndivNum(3);
	}
	void print() {
		Soldier::print();
		cout << " lion " << s->soldNum() << " born" << endl;
		cout << "It's loyalty is " << loy << endl;
	}
	~Lion() {
		s->minusIndivNum(3);
	}
};

class Wolf :public Soldier {
public:
	Wolf(int b, Clan * p) : Soldier(soldLife[4], b, p) {
		p->addIndivNum(4);
	}
	void print() {
		Soldier::print();
		cout << " wolf " << s->soldNum() << " born" << endl;
	}
	~Wolf() {
		s->minusIndivNum(4);
	}
};

void Clan::prodMinion() {
	if (lifeQuota >= soldLife[order[idx]]) {
		switch (order[idx]) {
		case 0: sdr.push_back(new Dragon(0, this)); break;
		case 1: sdr.push_back(new Ninja(0, this)); break;
		case 2: sdr.push_back(new Iceman(0, this)); break;
		case 3: sdr.push_back(new Lion(0, this)); break;
		case 4: sdr.push_back(new Wolf(0, this)); break;
		}
		sdr.back()->print();
		idx++;
	}
}

void printTime(int a, int b) {
	cout << setw(3) << setfill('0') << a << ":";
	cout << setw(2) << setfill('0') << b << " ";
}

// Time is in the unit of minute
void printEvent(Clan & red, Clan & blue, int totTime, vector<City *> & cityList) {
	do {
		int hour, min;
		hour = curTime / 60;
		min = curTime % 60;

		switch (min) {
		case 0: {
			printTime(hour, min);
			red.prodMinion();
			printTime(hour, min);
			blue.prodMinion();
			break;
		}
		case 10: {
			printTime(hour, min);

		}
		case 20: {
			for (vector<City *>::iterator it = cityList.begin(); it != cityList.end(); ++it) {
				(*it)->genQuota(10);
			}
		}
		case 50: {
			printTime(hour, min);
			cout << red.getQuota() << " elements in red headquarter" << endl;
			printTime(hour, min);
			cout << blue.getQuota() << " elements in blue headquarter" << endl;
		}
		default: break;
		}
		curTime++;
	} while ((red.isStop() || blue.isStop()) && curTime < totTime);

}

int main() {
	int trialNum = 0, totLife = 0, numCity = 0;
	int totTime = 0, loyalDrop = 0;
	cin >> trialNum;

	for (int i = 0; i < trialNum; i++) {
		cin >> totLife >> numCity >> arrowAp >> loyalDrop >> totTime;

		// Order goes as: dragon 、ninja、iceman、lion、wolf
		for (int j = 0; j < 5; j++) {
			cin >> soldLife[j];
		}

		// Initialize Clan
		Clan red("red", totLife, red_order);
		Clan blue("blue", totLife, blue_order);

		// Initialize city
		vector<City *> cityList(numCity);
		for (int i = 0; i < numCity; i++) {
			cityList[i] = new City(totLife, (i % 2 == 0));
		}

		cityList[0]->setPrev(&red);
		red.setNext(cityList[0]);
		cityList[numCity - 1]->setNext(&blue);
		blue.setPrev(cityList[numCity - 1]);

		for (int p = 0, q = 1; p < numCity - 1; p++, q++) {
			cityList[p]->setNext(cityList[p + 1]);
			cityList[q]->setPrev(cityList[q - 1]);
		}

		curTime = 0;
		// The minimal required life to produce a minion
		min_life = *min_element(soldLife, soldLife + 5);

		cout << "Case:" << (i + 1) << endl;

		printEvent(red, blue, totTime, cityList);
	}

	return 0;
}