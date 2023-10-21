#include <iostream>
#include <string>
using namespace std;

#pragma region Fwd
void EnemyTakesDamage(int& _enemyHealth, const int _strenghtUser);
void EnemyDealsDamage(int _enemyStrenght, int& _healthUser, const int _defenseUser);
bool IsDead(const int _health);
void EnemyLevelsUp(int& _enemyLevel, int& _enemyStrenght, int& _enemyHealth);
void Barr();
void Say(string _toSay);
bool GameChoose();
void Clear();
int ClassChosen();
void AskWitchStatAdd(int& _def, int& _att, int& _hp, string _forRandom);
void InitializeStatsPerso(int _choce, int& _def, int& _att, int& _hp, int& _mana);
void ChoosenAction(int& _enemyHealth, int _strenghtUser);
void TypeSomethingToContinue(string& _forRandom);
int RandomFromBagdad(string _strMultiplier, int _chosenRandom);
bool AskGameMode();
void InfiniteGame();
void HistoryGame();
void DisplayDeath(const int _deadCounter, int& _coins);


//Displays
void DisplayStatsBetter(const int _def, const int _att, const int _hp);
void DisplayTitle(); //Affiche écran titre
void DisplayWinRound(); //Nous informe qu'on a vaincu l'enemi
void DisplayEnemyTookDamage(const int _damageTaken, const int _enemyHealth); //Nous montre les dégats subis par l'enemi
void DisplayStats(const int _def, const int _att, const int _hp); //Affiche nos statistiques de joueur
void DisplayEnemyHealth(const int _enemyHealth); //Nous indique pv de l'enemi
void DisplayIntroductionTextMainStory();
#pragma endregion


int main()
{
	GameChoose();
	
	return 0;
}

bool GameChoose()
{
	//Afiche l'écran titre
	DisplayTitle();
	if (AskGameMode())
	{
		Clear();
		InfiniteGame();//Jouer au mode infini
	}
	else
	{
		Clear();
		HistoryGame();//Jouer au mode histoire 
	}
	return 0;
}



void EnemyTakesDamage(int& _enemyHealth, const int _strenghtUser)
{
	_enemyHealth -= 10 + _strenghtUser * 5;
	Clear();
	DisplayEnemyTookDamage(10 + _strenghtUser * 5, _enemyHealth);
}
void EnemyDealsDamage(int _enemyStrenght, int& _healthUser, const int _defenseUser)
{
	Barr();
	int _trueDamage = _enemyStrenght;
	int _reducedDamage = _enemyStrenght * (1-_defenseUser*7.5 / 100); 

	cout << "L'ennemi vous mets une bastoss (ouch ca doit faire mal), et vous prenez " << _trueDamage + _reducedDamage << " Degats" << endl;
	_healthUser -= _trueDamage + _reducedDamage;
	cout << "Il vous reste donc " << _healthUser << " HP"<<endl;
	Barr();
}
bool IsDead(const int _health)
{
	if (_health <= 0) return true;
	else return false;
}
void EnemyLevelsUp(int& _enemyLevel, int& _enemyStrenght, int& _enemyHealth)
{
	int _strenghtMultiplier = 1.5, _healthMultplier = 2 ;

	_enemyLevel += 1;
	_enemyStrenght += _enemyLevel * _strenghtMultiplier;
	_enemyHealth += _enemyLevel * _healthMultplier;
}
void Say(string _toSay)
{
	cout << _toSay << endl;
}
void Barr()
{
	string _result;
	for (int _index = 0; _index < 120; _index++)
	{
		_result += "\xCD";
	}
	cout << _result << endl << endl;
}
void Clear()
{
	system("cls");
}
void TypeSomethingToContinue(string& _forRandom)
{
	string _enter;
	Say("<Type Something To Continue>");
	cin >> _enter;
	_forRandom += _enter; //On va se servir de ce paramètre dit "aléatoire" pour créer notre propre fonction random
	Clear();
}
int RandomFromBagdad(string _strMultiplier, int _chosenRandom) //Donne un chiffre aléatoire entre 1 et x
{
	int _numChars = _strMultiplier.length();
	int _formula = ((_numChars + 22) * (_numChars)-13);
	return _formula % _chosenRandom + 1;
}
bool AskGameMode()//Return false si on choisi mode histoire, et true si mode vague infinie
{
	int _answer;
	Barr();
	Say("Choisissez votre mode de jeu ! ");
	Say("1- Mode histoire (conseill\x82) \t 2- Mode Vague Infinie");
	Barr();

	bool _condition;
	do
	{
		cin >> _answer;
		cout << endl;
		_condition = _answer != 1 && _answer != 2;
		if (_condition)
		{
			Say("Votre reponse est incorrecte, choisissez votre mode de jeu en tappant 1 ou 2");
		}
	} while (_condition);
	Clear();

	return _answer - 1;
}
void DisplayDeath(const int _deadCounter,int& _coins)
{
	Barr();
	Say("AHAHAHAHA TU ES MORT BOZO");
	cout << "TU AS VAINCU EXACTEMENT " << _deadCounter << " ENNEMIS" << endl;
	_coins = _deadCounter * 10;
	cout << "Tu obtiens donc " << _coins << " W-Bucks, nous te conseillons de les utiliser a la boutique" << endl;
	Say("Cela te permettra peut etre de vaincre plus d'ennemis !");
	Barr();
}
void InfiniteGame()
{
	//Initialisation des statistiques mc/ennemies
	int _deadCounter = 0;
	int _def, _att, _hp, _mana;
	int _enemyLevel = 1, _enemyAtt = 10, _enemyHp = 55;
	int _coins;
	//Initialisation d'un string qu'on va utiliser pour notre random
	string _forRandom;

	//Choix de la classe
	InitializeStatsPerso(ClassChosen(),_def, _att, _hp, _mana);
	Clear();
	while (true)
	{
		//Garde en mémoire les stats de pv et de force de l'ennemi précédent pour pouvoir appliquer la fonction EnemyLevelsUp, car les variables peuvent être modifié en fonction des compétences futures
		int _memoryEnemyAtt = _enemyAtt, _memoryEnemyHp = _enemyHp;
		Say("UN TERRIBLE MONSTRE APPARAIT DEVANT VOUS");
		cout << "C'est un monstre de niveau " << _enemyLevel << " !!!" <<endl;
		while (true)
		{
			DisplayEnemyHealth(_enemyHp);
			//Choisi l'attaque a utiliser, inflige dégats selon cette dernière, dislay les pvs restant de l'ennemi 
			ChoosenAction(_enemyHp, _att);

			//Si l'ennemi est mort
			if (IsDead(_enemyHp))
			{
				//Incrémente notre compteur de kill
				_deadCounter += 1;

				//Affiche qu'on a tué notre adversaire
				Clear();
				DisplayWinRound();

				//Nous demande quels stats augmenter x2
				AskWitchStatAdd(_def, _att, _hp, _forRandom);
				Clear();

				//Augmente les stats de ton ennemi
				EnemyLevelsUp(_enemyLevel, _memoryEnemyAtt, _memoryEnemyHp);
				//Garde en mémoire les stats du prochain ennemi
				_enemyAtt = _memoryEnemyAtt, _enemyHp = _memoryEnemyHp;

				break;
			}

			//L'enemi a survécu, au tour de l'ennemi d'attaquer

			TypeSomethingToContinue(_forRandom);
			EnemyDealsDamage(_enemyAtt, _hp, _def);
			//Si notre joueur est mort, message de mort et arrêt du jeu, display kill counter
			if (IsDead(_hp))
			{
				Clear();
				DisplayDeath(_enemyLevel, _coins);
				TypeSomethingToContinue(_forRandom);
				//Menu() avec 3 interfaces, 1 -=> Try Again , 2 -=> Shop, 3 -=> Quitter le jeu 
				
				return;
			}
			TypeSomethingToContinue(_forRandom);
		}
	}
}
void HistoryGame()
{
	return;
}




void DisplayWinRound()
{
	Barr();
	Say("OH MON DIEUUUU, vOuS aVeZ vAiNcU l'EnNeMi");
	Barr();
}
void DisplayEnemyHealth(const int _enemyHealth)
{
	cout << endl;
	Barr();
	cout << "Ton ennemi possede " << _enemyHealth << " HP " << endl;
	Barr();
	cout << endl;
}
void DisplayEnemyTookDamage(const int _damageTaken, const int _enemyHealth)
{
	cout << endl;
	Barr();
	cout << "Votre ennemi a pris cher ! -" << _damageTaken << " HP \t Il a actuellement " << _enemyHealth << " HP" << endl;
	Say("AU TOUR DE L'ENNEMI");
	Barr();
}
void DisplayTitle()
{
	Say("   _____                             _        ____                 _");
	Say("  |  __ \\                           ( )      / __ \\               | |");
	Say("  | |__) |___  _ __ ___   __ _ _ __ |/ ___  | |  | |_   _  ___ ___| |_ ");
	Say("  |  _  // _ \\| '_ ` _ \\ / _` | '_ \\  / __| | |  | | | | |/ _ / __| __|");
	Say("  | | \\ | (_) | | | | | | (_| | | | | \\__ \\ | |__| | |_| |  __\\__ | |_");
	Say("  |_|  \\_\\___/|_| |_| |_|\\__,_|_| |_| |___/  \\___\\_\\\\__,_|\\___|___/\\__|");
	Barr();
	cout << endl;
}
void DisplayIntroductionTextMainStory()
{
	Say("Bienvenue aventurier,");
	Say("Vous `\x88tes le plus grand \x82ros de tout les temps, ayant pour terrifiant nom... ROMAIN ");
	Say("Mais m\x88me un h\x82ros possede des faiblesses et des peurs, r\x82ussirez vous a les vaincre ?");
	Say("L'avenir nous le dira, que la qu\x88te COMMENCE :D");
	Barr();
}
void DisplayStatsBetter(const int _def, const int _att, const int _hp)
{
	Say("  __________________________");
	cout << " | " << "      " << " | " << "      " << " | " << "      " << " | " << endl;
	cout << " | " << "Def: " << _def << " | " << "Atk: " << _att << " | " << "Hp: " << _hp << " | " << endl;
	cout << " |_" << "______" << "_|_" << "______" << "_|_" << "______" << "_| " << endl;
	
}








//GREG
int ClassChosen()
{
	int _choice;

	cout << "Quel classe veut tu prendre \t Tes stat : Defense  Attaque   Vie " << endl;

	string _tab[4]
	{

		"1 : Guerrier \t\t\t\t\t2\t2\t125 ",
		"2 : Mage \t\t\t\t\t1\t4\t100",
		"3 : Assasin\t\t\t\t\t1\t5\t75",
		"4 : Gardien\t\t\t\t\t3\t1\t125",
	};


	for (int _index = 0; _index < 4; _index++)
	{
		cout << _tab[_index] << endl;
	}
	cout << "Quel est ton choix : " <<endl;
	cin >> _choice;
	cout << endl;

	while (_choice < 1 || _choice >4)
	{
		cout << "Cette class n'existe pas" << endl;
		cin >> _choice;
	}

	return _choice;
}
void AskWitchStatAdd(int& _def, int& _att, int& _hp, string _forRandom)
{
	int _statAdd;
	Say("Tu es pass\x82 au niveau sup\x82rieur, tu peux choisir 2 stats a renforcer: ");

	//Donne un chiffre pseudo-Aléatoire entre 1 et 3
	int _thisStatIsDoubled = RandomFromBagdad(_forRandom, 3);
	int _defProposition = 1, _attProposition = 1, _hpProposition = 15;
	string _chanceDef="", _chanceAtt="", _chanceHp="";
	//Fais fois 2 a la stats qui aura un bonus
	switch (_thisStatIsDoubled)
	{
	case 1:
		_defProposition *= 2;
		_chanceDef = "(Bonus CHANCE)";
		break;
	case 2:
		_attProposition *= 2;
		_chanceAtt = "(Bonus CHANCE)";
		break;
	case 3:
		_hpProposition += 10;
		_chanceHp = "(Bonus CHANCE)";
		break;
	default:
		break;
	}
	for (int _index = 0; _index < 2; _index++)
	{
		Say("Quelle stat veux-tu augmenter ?");
		DisplayStatsBetter(_def, _att, _hp);
		cout << "1 : Defense +"<< _defProposition << " "  << _chanceDef<< endl;
		cout << "2 : Attaque +"<< _attProposition << " " << _chanceAtt << endl;
		cout << "3 : Vie +"<< _hpProposition << " " << _chanceHp <<endl;

		_chanceDef = "", _chanceAtt = "", _chanceHp = "";

		cin >> _statAdd;
		cout << endl;

		while (_statAdd < 1 || _statAdd >3)
		{
			cout << "Ceci est impossible" << endl;
			cin >> _statAdd;
		}
		if (_statAdd == 1)
		{
			_def += _defProposition;
		}
		else if (_statAdd == 2)
		{
			_att += _attProposition;
		}
		else
			_hp += _hpProposition;

		_defProposition = 1, _attProposition = 1, _hpProposition = 15;
	}
}

void DisplayStats(const int _def, const int _att, const int _hp)
{
	cout << "Tes stat Actuelle : Defense Attaque Vie" << endl;
	cout << "\t\t\t" << _def << "\t" << _att << "    " << _hp << endl;
}
//Nino
void InitializeStatsPerso(int _choce, int& _def, int& _att, int& _hp, int& _mana)
{
	switch (_choce)
	{
	case 1:
		_def = 2;
		_att = 2;
		_hp = 125;
		_mana = 100;
		break;
	case 2:
		_def = 1;
		_att = 4;
		_hp = 100;
		_mana = 150;
		break;
	case 3:
		_def = 1;
		_att = 5;
		_hp = 75;
		_mana = 75;
		break;
	case 4:
		_def = 3;
		_att = 1;
		_hp = 125;
		_mana = 80;
		break;
	}
}
void ChoosenAction(int& _enemyHealth, int _strenghtUser)
{
	int _chose;
	cout << "Que veux-tu faire ? : ";
	cout << "1- Attaquer" << "\n";
	Barr();
	cin >> _chose;
	switch (_chose)
	{
	case 1:
		EnemyTakesDamage(_enemyHealth, _strenghtUser);
		break;
	default:
		ChoosenAction(_enemyHealth, _strenghtUser);
	}	
}