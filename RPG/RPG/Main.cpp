#include <iostream>
#include <string>
using namespace std;

#pragma region Fwd
void EnemyTakesDamage(int& _enemyHealth, const int _strenghtUser);
void EnemyDealsDamage(int _enemyStrenght, int& _healthUser, const int _defenseUser, string _enemyName = "L'ennemi",  string _attackLines = " vous mets une bastoss (ouch ca doit faire mal)");
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
void ChoosenAction(int& _enemyHealth, int _strenghtUser, int _index, bool& isWinning);
void TypeSomethingToContinue(string& _forRandom);
void TypeSomethingToContinue();
int RandomFromBagdad(string _strMultiplier, int _chosenRandom);
bool AskGameMode();
void InfiniteGame();
void StoryGame();
void DisplayDeath(const int _deadCounter, int& _coins);
void SwitchLuck(const int _thisStatIsDoubled, int& _defProposition, string& _chanceDef, int& _attProposition, string& _chanceAtt, int& _hpProposition, string& _chanceHp);
void EnemyStoryMode(int*& _arrayEnemies);


//Displays
void DisplayStatsBetter(const int _def, const int _att, const int _hp);//Affiche nos statistiques de joueur
void DisplayTitle(); //Affiche écran titre
void DisplayWinRound(); //Nous informe qu'on a vaincu l'enemi
void DisplayEnemyTookDamage(const int _damageTaken, const int _enemyHealth); //Nous montre les dégats subis par l'enemi
void DisplayEnemyHealth(const int _enemyHealth, string _enemyName = "Ton ennemi"); //Nous indique pv de l'enemi
void DisplayIntroductionTextMainStory();
void DisplayEnemyStats(string _enemyName, int _enemyAtt, int _enemyHp);
void DisplayGameOver();
void DisplayYouWin();

void DisplayBadEnding(const string _enemyName = "ton ennemi");
void DisplayOtherBadEnding();
bool DisplayWinStoryMode();
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
		StoryGame();//Jouer au mode histoire 
	}
	return 0;
}
void InfiniteGame()
{
	//Initialisation des statistiques mc/ennemies
	int _deadCounter = 0;
	int _def, _att, _hp, _mana;
	int _enemyLevel = 1, _enemyAtt = 10, _enemyHp = 55;
	int _coins;
	//Initialisation d'un string qu'on va utiliser pour notre random
	string _forRandom = " ";

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
void StoryGame()
{
	//Init stats perso / Mob
	int _def, _att, _hp, _mana;
	int _enemyAtt, _enemyHp ;
	bool _isWinning = false;

	//Init noms enemis
	string _enemyName[7] = {"Slimey", "Teemo le petit yordle", "Obama", "Un Pointeur de tableau", "Vayne Top", "Thomas", "Seb"};
	string _attackLines[7] = { 
		" utilise l'attaque lance-morve", 
		" vous empoisonne (Hin Hin Hin)", 
		" fait un speech puissant, on dirait que l'amerique toute entiere vous porte un coup",
		", vous n'y comprennez rien et prenez des degats critique", 
		", la raciste vous burst a distance", 
		" ne veut pas vous attaquer, en revanche il vous demande de finir votre messagerie (running gag)",
		" pousse un cri TERRIFIANT, arHgHghAAAgH",
	};

	//Leurs stats ATT / Hp dans tableau unidimentionnel
	int* _arrayEnemiesStats = new int[14];
	EnemyStoryMode(_arrayEnemiesStats);

	//Initialisation d'un string qu'on va utiliser pour notre random
	string _forRandom = " ";

	//Histoire
	DisplayIntroductionTextMainStory();
	TypeSomethingToContinue(_forRandom);

	//Choix de la classe
	InitializeStatsPerso(ClassChosen(), _def, _att, _hp, _mana);
	Clear();

	//On entre dans la bataille
	for (int _index = 0; _index < 14; _index+=2)
	{
		_enemyAtt = _arrayEnemiesStats[_index], _enemyHp = _arrayEnemiesStats[_index + 1];

		//Nous indique qu'un ennemi est apparut, nous donne ses stats
		#pragma region Ennemi Apprait + stats
		Barr();
		cout << _enemyName[_index / 2] << " apparait devans vous !!!" << endl;
		DisplayEnemyStats(_enemyName[_index / 2], _enemyAtt, _enemyHp);
		Barr();
		#pragma endregion
		
		TypeSomethingToContinue(_forRandom);
		Clear();
		
		while (true)
		{
			DisplayEnemyHealth(_enemyHp, _enemyName[_index / 2]);

			//Case unique où on combat vayne
			if (_index == 8)
			{
				Clear();
				Say("Vayne top a plus de portee que vous, elle attaque en premiere");
				EnemyDealsDamage(_enemyAtt, _hp, _def, _enemyName[_index / 2], _attackLines[_index / 2]);
				//Si notre joueur est mort, message de mort et arrêt du jeu
				if (IsDead(_hp))
				{
					TypeSomethingToContinue();
					Clear();
					DisplayGameOver();
					DisplayBadEnding(_enemyName[_index / 2]);
					return;
				}
			}

			//Choisi l'attaque a utiliser, inflige dégats selon cette dernière, dislay les pvs restant de l'ennemi 
			ChoosenAction(_enemyHp, _att, _index ,_isWinning);
			
			//Si tu gagnes on stop tout
			if (_isWinning == true)
			{
				return;
			}

			//Si l'ennemi est mort
			if (IsDead(_enemyHp))
			{
				//Affiche qu'on a tué notre adversaire
				Clear();
				DisplayWinRound();

				//Nous demande quels stats augmenter x2
				AskWitchStatAdd(_def, _att, _hp, _forRandom);
				Clear();
				break;
			}

			//L'enemi a survécu, au tour de l'ennemi d'attaquer

			TypeSomethingToContinue(_forRandom);
			EnemyDealsDamage(_enemyAtt, _hp, _def, _enemyName[_index / 2], _attackLines[_index/2]);

			//Si notre joueur est mort, message de mort et arrêt du jeu
			if (IsDead(_hp))
			{
				if (_index == 12)
				{
					TypeSomethingToContinue();
					Clear();
					DisplayGameOver();
					DisplayOtherBadEnding();

					return;
				}

				TypeSomethingToContinue();
				Clear();
				DisplayGameOver();
				DisplayBadEnding(_enemyName[_index / 2]);

				return;
			}
			TypeSomethingToContinue(_forRandom);
		}
	}
	return;
}
void EnemyTakesDamage(int& _enemyHealth, const int _strenghtUser)
{
	_enemyHealth -= 10 + _strenghtUser * 5;
	Clear();
	DisplayEnemyTookDamage(10 + _strenghtUser * 5, _enemyHealth);
}
void EnemyDealsDamage(int _enemyStrenght, int& _healthUser, const int _defenseUser, string _enemyName, string _attackLines)
{
	Barr();
	int _trueDamage = _enemyStrenght*0.75;
	int _reducedDamage = _enemyStrenght * 1.25 * (1-_defenseUser*10 / 100); 

	cout << _enemyName << _attackLines << endl <<"Vous recevez " << _trueDamage + _reducedDamage << " Degats" << endl;
	_healthUser -= _trueDamage + _reducedDamage;
	cout << "Il vous reste donc " << _healthUser << " HP"<<endl;
	Barr();
}
bool IsDead(const int _health)
{
	if (_health <= 0) return true;
	else return false;
}
void EnemyStoryMode(int*& _arrayEnemies)
{
	int* _newArrayEnemies = new int[14] {

		//Att //Hp
		5, 30, // Slimey
		10, 50, // Teeemo
		15, 100, // Obama
		25, 60, // Des Pointeurs
		30, 1,  // VayneTop
		1, 250, // Thomas
		9999, 9999 //Seb
		};

	delete[] _arrayEnemies;
	_arrayEnemies = _newArrayEnemies;
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
void TypeSomethingToContinue()
{
	string _enter;
	Say("<Type Something To Continue>");
	cin >> _enter;
	Clear();
}
int RandomFromBagdad(string _strMultiplier, int _modulo) //Donne un chiffre aléatoire entre 1 et x
{
	unsigned int _seed= _strMultiplier.length();
	unsigned int _a = 1664525, _c = 1013904223;
	return (_a * _seed + _c) % _modulo + 1;
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
		std::cout << endl;
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
void DisplayWinRound()
{
	Barr();
	Say("OH MON DIEUUUU, vOuS aVeZ vAiNcU l'EnNeMi");
	Barr();
}
void DisplayEnemyHealth(const int _enemyHealth, string _enemyName)
{
	cout << endl;
	Barr();
	cout << _enemyName  <<" possede " << _enemyHealth << " HP " << endl;
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
void DisplayEnemyStats(string _enemyName, int _enemyAtt, int _enemyHp)
{
	cout << "A premiere vu, " << _enemyName << " semble disposer d'une force de " << _enemyAtt << ", il semble avoir egalement " << _enemyHp << "HP"<< endl;
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
	cout << endl << endl;
	Barr();
	Say("Bienvenue aventurier,");
	Say("Vous \x88tes le plus grand h\x82ros de tout les temps, ayant pour terrifiant nom... ROMAIN ");
	Say("Mais m\x88me un h\x82ros possede des faiblesses et des peurs, r\x82ussirez vous a les vaincres ?");
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
void DisplayGameOver()
{
	cout << "   _____                         ____                 " << endl;
	cout << "  / ____|                       / __ \\                " << endl;
	cout << " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ " << endl;
	cout << " | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|" << endl;
	cout << " | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   " << endl;
	cout << "  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   " << endl;
	cout << "                                                      " << endl;
	cout << "                                                      " << endl;
	Barr();
}
void DisplayYouWin()
{
	cout << " __     ______  _    _  __          ______  _   _    _   _   _  " << endl;
	cout << " \\ \\   / / __ \\| |  | | \\ \\        / / __ \\| \\ | |  | | | | | | " << endl;
	cout << "  \\ \\_/ / |  | | |  | |  \\ \\  /\\  / / |  | |  \\| |  | | | | | | " << endl;
	cout << "   \\   /| |  | | |  | |   \\ \\/  \\/ /| |  | | . ` |  | | | | | | " << endl;
	cout << "    | | | |__| | |__| |    \\  /\\  / | |__| | |\\  |  |_| |_| |_| " << endl;
	cout << "    |_|  \\____/ \\____/      \\/  \\/   \\____/|_| \\_|  (_) (_) (_) " << endl;
	cout << "                                                                " << endl;
	cout << "                                                                " << endl;
	Barr();
}
void DisplayBadEnding(const string _enemyName)
{
	cout << "C'est fini gars " << _enemyName << " t'a termin\x82 gros !" << endl;
	cout << "Reesaie encore, peux-etre auras-tu une chance de vaincre" << endl;
}
void DisplayOtherBadEnding()
{
	Say("Bien vu l'artiste, tu ne peux pas terminer ce jeu, tu te hurtes a un mur impossible a franchir");
	Say("He will win who knows when to fight and when not to fight. ~Sun Tzu: Art of War");
	Say("(Gagnera qui sait quand se battre et quand ne pas se battre. ~Sun Tzu: L'Art de la Guerre)");
}
bool DisplayWinStoryMode()
{
	Say("Vous ne faites rien.");
	cout << endl;
	TypeSomethingToContinue();
	Clear();
	cout << endl;
	Barr();
	Say("Seb: Jeune homme, maintenant va t'assoir et commence a travailler, nous ne sommes pas dans une cours de recreation.");
	Say("Seb: Tien! Profite du beau temps qu'il y a dehors pour apprendre a coder a l'interieur.\n");
	Say("Seb: Quand on aime coder on ne s'ennuie pas\n");
	Barr();
	TypeSomethingToContinue();
	Clear();
	DisplayYouWin();
	Say("Vous avez decide de ne pas attaquer le boss invincible,");
	Say("En ne vous battant pas contre Seb vous avez esquive une mort innevitable.");
	Say("Il vous a fait la morale, mais ce n'est pas si pire que ca, vous etes en vie, FELICITATION! ");
	return 1;
}
int ClassChosen()
{
	int _choice;
	cout << " ____________________________________________________________________" << endl;
	cout << "|Quel classe veux-tu prendre        Tes stats: Defense  Attaque   Vie|" << endl;
	cout << "|1: Guerrier                                      2        3      125|" << endl;
	cout << "|2: Mage                                          1        4      100|" << endl;
	cout << "|3: Assasin                                       1        5      75 |" << endl;
	cout << "|4: Gardien                                       3        1      175|" << endl;
	cout << "|____________________________________________________________________|" << endl;

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

	//Donne un chiffre pseudo-Aléatoire entre 1 et 6, tu as donc une chance sur 2 d'avoir un bonus chance, et 1 chance sur 3 d'avoir celui souhaité
	int _thisStatIsDoubled = RandomFromBagdad(_forRandom, 6);
	int _defProposition = 1, _attProposition = 1, _hpProposition = 15;
	string _luckDef="", _luckAtt="", _luckHp="";
	
	//Pour attribuer le ("Chance") a la stat doublé, et double également la stat concernée
	SwitchLuck(_thisStatIsDoubled, _defProposition, _luckDef, _attProposition, _luckAtt, _hpProposition, _luckHp);

	for (int _index = 0; _index < 2; _index++)
	{
		Say("Quelle stat veux-tu augmenter ?");
		DisplayStatsBetter(_def, _att, _hp);
		cout << "1 : Defense +"<< _defProposition << " "  << _luckDef<< endl;
		cout << "2 : Attaque +"<< _attProposition << " " << _luckAtt << endl;
		cout << "3 : Vie +"<< _hpProposition << " " << _luckHp <<endl;

		_luckDef = "", _luckAtt = "", _luckHp = "";

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

		//Reset de la stat doublée
		int _defProposition = 1, _attProposition = 1, _hpProposition = 15;
		string _luckDef = "", _luckAtt = "", _luckHp = "";

		//Calcul de la prochaine stat a doubler
		int _thisStatIsDoubled = RandomFromBagdad(_forRandom+"1", 6);
		SwitchLuck(_thisStatIsDoubled, _defProposition, _luckDef, _attProposition, _luckAtt, _hpProposition, _luckHp);
	}
}
void SwitchLuck(const int _thisStatIsDoubled, int& _defProposition, string& _luckDef, int& _attProposition, string& _luckAtt, int& _hpProposition, string& _luckHp)
{
	//Fais fois 2 a la stats qui aura un bonus
	switch (_thisStatIsDoubled)
	{
	case 1:
		_defProposition *= 2;
		_luckDef = "(Bonus CHANCE)";
		break;
	case 2:
		_attProposition *= 2;
		_luckAtt = "(Bonus CHANCE)";
		break;
	case 3:
		_hpProposition *= 2;
		_luckHp = "(Bonus CHANCE)";
		break;
	default:
		break;
	}


}
void InitializeStatsPerso(int _choce, int& _def, int& _att, int& _hp, int& _mana)
{
	switch (_choce)
	{
	case 1:
		_def = 2;
		_att = 3;
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
		_hp = 175;
		_mana = 80;
		break;
	}
}
void ChoosenAction(int& _enemyHealth, int _strenghtUser)
{
	int _chose;
	cout << "Que veux-tu faire ? : ";
	cout << "1- Attaquer" << "\t" << "2- Ne rien faire" << endl;
	Barr();
	cin >> _chose;
	switch (_chose)
	{
	case 1:
		EnemyTakesDamage(_enemyHealth, _strenghtUser);
		break;
	case 2:
		
		Say("Vous ne faites rien.");
		break;
	default:
		ChoosenAction(_enemyHealth, _strenghtUser);
	}	
}
void ChoosenAction(int& _enemyHealth, int _strenghtUser, int _index, bool& isWinning)
{
	int _chose;
	cout << "Que veux-tu faire ? : ";
	cout << "1- Attaquer" << "\t" << "2- Ne rien faire" << endl;
	Barr();
	cin >> _chose;
	switch (_chose)
	{
	case 1:
		EnemyTakesDamage(_enemyHealth, _strenghtUser);
		break;
	case 2:
		if (_index == 12)
		{
			isWinning = DisplayWinStoryMode();
			break;
		}
		Say("Vous ne faites rien.");
		break;
	default:
		ChoosenAction(_enemyHealth, _strenghtUser);
	}
}