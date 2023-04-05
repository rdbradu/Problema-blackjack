#include<iostream>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
#include<string>
#include<algorithm>

using namespace std;

struct Carte
{
	int numar;
	string forma;
	Carte(int arg_numar, string arg_forma)
	{
		numar = arg_numar;
		forma = arg_forma;
	}
};

class Jucator
{
private:
	string nume;
	float bani;
	vector<Carte> carti;
	int suma;
	bool winner = false;
public:
	Jucator(string arg_nume, float arg_bani)
	{
		nume = arg_nume;
		bani = arg_bani;
		suma = 0;
	}
	int getSum()
	{
		return suma;
	}
	void addCard(Carte arg_carte)
	{
		carti.push_back(arg_carte);
	}
	void sumOfCards()
	{
		for (Carte carte : carti)
		{
			if (carte.numar > 10)
			{
				suma = suma + 10;
			}
			else suma = suma + carte.numar;
		}
	}
	bool overSum()
	{
		bool os = false;
		if (suma > 21)
		{
			os = true;
		}
		return os;
	}
	bool hasBlackjack()
	{
		bool hasBj = false;
		if (suma == 21)
		{
			hasBj = true;
		}
		return hasBj;
	}
	bool notEnoughPoints()
	{
		bool nep = false;
		int sum = 0;
		for (Carte carte : carti)
		{
			if (carte.numar > 10)
			{
				sum = sum + 10;
			}
			else sum = sum + carte.numar;
		}
		{
			if (sum < 17)
			{
				nep = true;
			}
		}
		return nep;
	}
	bool noMoney()
	{
		bool noCash = false;
		if (bani < 10)
		{
			noCash = true;
		}
		return noCash;
	}
	void setWinner()
	{
		winner = true;
	}
	bool isWinner()
	{
		return winner;
	}
	void setMoney(float arg_money)
	{
		bani = bani + arg_money;
	}
	void getMoney()
	{
		bani = bani - 10;
	}
	void print()
	{
		cout << nume << ": " << bani << endl;
	}
	void reset()
	{
		carti.clear();
		suma = 0;
		winner = false;
	}
};

bool are_duplicates(vector<Carte> pachet)
{
	bool duplicates = false;
	for (int i = 0; i < pachet.size() - 1; i++)
	{
		for (int j = i + 1; j < pachet.size(); j++)
		{
			if (pachet[i].numar == pachet[j].numar && pachet[i].forma == pachet[j].forma)
			{
				duplicates = true;
			}
		}
	}
	return duplicates;
}

void check_cards()
{
	vector<Carte> pachet;

	int numar;
	string forma;
	bool masluit = false;
	bool ok = false;
	char sep;
	while (cin >> numar >> sep >> forma)
	{
		Carte temp(numar, forma);
		pachet.push_back(temp);
	}
	for (Carte carte : pachet)
	{
		if (carte.numar > 1)
		{
			if (carte.numar < 15)
			{
				if (carte.forma == "rosu" || carte.forma == "trefla" || carte.forma == "romb" || carte.forma == "negru")
				{

				}
				else masluit = true;
			}
			else masluit = true;
		}
		else masluit = true;
	}
	if (pachet.size() < 53)
	{
		if (are_duplicates(pachet) == false)
		{
			ok = true;
		}
	}

	if (masluit)
	{
		cout << "Pachet masluit" << endl;
	}
	else if (ok)
	{
		cout << "Pachet OK" << endl;
	}
	else if (!masluit)
	{
		cout << "Pregatit pentru Blackjack" << endl;
	}
}

vector<Carte> amesteca(vector<Carte> pachet, int a1, int x1, int c1, int a2, int x2, int c2)
{
	for (int i = 0; i < 50; i++)
	{
		int i1 = (a1 * x1 + c1) % pachet.size();
		x1 = i1;
		int i2 = (a2 * x2 + c2) % pachet.size();
		x2 = i2;

		Carte temporar(pachet[i1].numar, pachet[i1].forma);
		pachet[i1] = pachet[i2];
		pachet[i2] = temporar;
	}
	return pachet;
}

void shuffle_cards()
{
	int a1, a2, x1, x2, c1, c2;
	int numar;
	char sep;
	string forma;
	vector<Carte> pachet;

	cin >> a1 >> c1 >> x1;
	cin >> a2 >> c2 >> x2;

	while (cin >> numar >> sep >> forma)
	{
		Carte temp(numar, forma);
		pachet.push_back(temp);
	}
	pachet = amesteca(pachet, a1, x1, c1, a2, x2, c2);
	for (Carte carte : pachet)
	{
		cout << carte.numar << "," << carte.forma << endl;
	}

}

vector<Carte> create_pack()
{
	vector<Carte> pachet;
	vector<string> steme;
	steme.push_back("rosu");
	steme.push_back("negru");
	steme.push_back("romb");
	steme.push_back("trefla");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j < 15; j++)
		{
			if (j == 11)
			{
			}
			else
			{
				Carte temp(j, steme[i]);
				pachet.push_back(temp);
			}
		}
	}
	return pachet;
}

Jucator give_cards(vector<Carte>& pachet, Jucator jucator)
{

	//prima carte
	Carte temp = pachet[0];
	jucator.addCard(temp);
	pachet.erase(pachet.begin());

	//a doua carte
	temp = pachet[0];
	jucator.addCard(temp);
	pachet.erase(pachet.begin());

	return jucator;
}

Jucator hit_cards(vector<Carte>& pachet, Jucator jucator)
{
	//extra
	while (jucator.notEnoughPoints())
	{
		Carte temp = pachet[0];
		jucator.addCard(temp);
		pachet.erase(pachet.begin());
	}
	return jucator;
}

vector<Jucator> run_game(vector<Jucator> jucatori, Jucator& dealer)
{
	//suma cartilor
	for (int i = 0; i < jucatori.size(); i++)
	{
		jucatori[i].getMoney();//-10E miza
		jucatori[i].sumOfCards();
	}
	dealer.sumOfCards();

	//castigator sau loser
	if (dealer.overSum())//Daca dealer-ul are peste 21
	{
		for (int i = 0; i < jucatori.size(); i++)
		{
			if (!jucatori[i].overSum())
			{
				jucatori[i].setWinner();
				jucatori[i].setMoney(20);
			}
		}
	}
	else if (dealer.hasBlackjack())//Daca dealer-ul are exact 21
	{
		for (int i = 0; i < jucatori.size(); i++)
		{
			if (jucatori[i].hasBlackjack())
			{
				jucatori[i].setWinner();
				jucatori[i].setMoney(10);
			}
		}
	}
	else for (int i = 0; i < jucatori.size(); i++)//play-ul normal
	{
		if (jucatori[i].getSum() > dealer.getSum() && !jucatori[i].overSum())
		{
			jucatori[i].setWinner();
			jucatori[i].setMoney(20);
		}
		if (jucatori[i].getSum() == dealer.getSum() && !jucatori[i].overSum())
		{
			jucatori[i].setWinner();
			jucatori[i].setMoney(10);
		}
	}
	return jucatori;
}
void play_game()
{
	vector<Jucator> jucatori;
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		string nume;
		float bani;
		cin >> nume >> bani;
		Jucator temp(nume, bani);
		jucatori.push_back(temp);
	}
	Jucator dealer("Dealer", 100);
	int a1, a2, x1, x2, c1, c2;
	vector<Carte> pachet = create_pack();
	while (cin >> a1 >> c1 >> x1 >> a2 >> c2 >> x2)
	{

		pachet = amesteca(pachet, a1, x1, c1, a2, x2, c2);//amestecare
		vector<Carte> pachet_fake = pachet;
		// play_efectiv - hit/stand toata lumea 
		for (int i = 0; i < jucatori.size(); i++)//imparte carti
		{
			jucatori[i] = give_cards(pachet_fake, jucatori[i]);
		}
		dealer = give_cards(pachet_fake, dealer);
		for (int i = 0; i < jucatori.size(); i++)//hit sau stand
		{
			jucatori[i] = hit_cards(pachet_fake, jucatori[i]);
		}
		dealer = hit_cards(pachet_fake, dealer);


		// vezi cine pierde + rezolva bani
		jucatori = run_game(jucatori, dealer);

		// fara functie - da erase la cei care nu mai au bani
		for (int i = 0; i < jucatori.size(); i++)
		{
			if (jucatori[i].noMoney())
			{
				jucatori.erase(jucatori.begin() + i);
			}
			jucatori[i].reset();
			dealer.reset();
		}
	}
	for (int i = 0; i < jucatori.size(); i++)
	{
		jucatori[i].print();
	}
}
int main()
{
	string command;
	cin >> command;
	if (command == "check_cards")
	{
		check_cards();
	}
	if (command == "shuffle_cards")
	{
		shuffle_cards();
	}
	if (command == "play_game")
	{
		play_game();
	}
	return 0;
}
