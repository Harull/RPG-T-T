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
void DisplayWinRound();
bool GameLoop();
void Clear();
void DisplayEnemy(const int _enemyHealth);
int ClassChosen();
void AskWitchStatAdd(int& _def, int& _att, int& _hp);
void DisplayStats(const int _def, const int _att, const int _hp);
void InitializeStatsPerso(int _choce, int& _def, int& _att, int& _hp, int& _mana);
void InitializeStatsEnemy(int& _ennemiLevel, int& _enemiAtt, int& _enemiHp);
void ChoosenAction(int& _enemyHealth, int _strenghtUser);

#pragma endregion


int main()
{
	GameLoop();
	
	return 0;
}




bool GameLoop()
{
	
	int _def, _att, _hp, _mana;
	InitializeStatsPerso(ClassChosen(), _def, _att, _hp, _mana);
	int _enemyLevel, _enemyAtt, _enemyHp;	
	InitializeStatsEnemy(_enemyLevel, _enemyAtt, _enemyHp);
	Clear();
	for (int _index = 1; _index < 5; _index++)
	{

		while (true)
		{
			DisplayEnemy(_enemyHp);
			ChoosenAction(_enemyHp, _att);
			Clear();
			DisplayEnemy(_enemyHp);
			if (IsDead(_enemyHp))
			{
				break;
			}
			EnemyDealsDamage(_enemyAtt, _hp, _def);
			if (IsDead(_hp))
			{
				Say("AHAHAHAHA TU ES MORT BOZO");
				return 0;
			}
		}
	}

	return 0;

}
void EnemyTakesDamage(int& _enemyHealth, const int _strenghtUser)
{
	_enemyHealth -= 10 + _strenghtUser * 5;
}
void EnemyDealsDamage(int _enemyStrenght, int& _healthUser, const int _defenseUser)
{
	int _trueDamage = _enemyStrenght * 1.25 + 10;
	int _reducedDamage = _enemyStrenght * 2 * (1 - _defenseUser / 100);
	cout << "L'ennemi vous mets une bastoss (ouch ça doit faire mal), et vous prenez " << _trueDamage + _reducedDamage << " Degats";
	_healthUser = _trueDamage + _reducedDamage;
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
void DisplayWinRound()
{
	Barr();
	Say("OH MON DIEUUUU, vOuS aVeZ vAiNcU l'EnNeMi");
	Barr();
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
	cout << _result << endl;
}
void Clear()
{
	system("cls");
}
void DisplayEnemy(const int _enemyHealth)
{
	cout << endl;
	Barr();
	cout << "Un ennemi est devant toi, il a actuellement " << _enemyHealth << " HP " << endl;
	Barr();
	cout << endl;
}

//GREG
int ClassChosen()
{
	int _choice;

	cout << "Quel class veut tu prendre \t Tes stat : Defense  Attaque   Vie " << endl;

	string _tab[4]
	{

		"1 : Guerrier \t\t\t\t\t2\t2\t3 ",
		"2 : Mage \t\t\t\t\t1\t4\t2",
		"3 : Assasin\t\t\t\t\t1\t5\t1",
		"4 : Gardien\t\t\t\t\t3\t1\t3",
	};


	for (int _index = 0; _index < 4; _index++)
	{
		cout << _tab[_index] << endl;
	}
	cout << "Quel est ton choix : ";
	cin >> _choice;

	while (_choice < 1 || _choice >4)
	{
		cout << "Cette class n'existe pas" << endl;
		cin >> _choice;
	}

	return _choice;
}
void AskWitchStatAdd(int& _def, int& _att, int& _hp)
{
	int _statAdd;
	cout << "Bravo tu a gagner quel stat veut tu ajouter" << endl;
	DisplayStats(_def, _att, _hp);
	cout << "Quel stat veut tu ameliorer" << endl;

	for (int _index = 0; _index < 2; _index++)
	{
		cout << "1 : Defense +1 " << endl;
		cout << "2 : Attaque +1 " << endl;
		cout << "3 : Vie +1 " << endl;
		cin >> _statAdd;
		while (_statAdd < 1 || _statAdd >3)
		{
			cout << "Ceci est impossible" << endl;
			cin >> _statAdd;
		}
		if (_statAdd == 1)
		{
			_def + 1;
		}
		else if (_statAdd == 2)
		{
			_att + 1;
		}
		else
			_hp + 1;
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
		_hp = 3;
		_mana = 100;
		break;
	case 2:
		_def = 1;
		_att = 4;
		_hp = 2;
		_mana = 150;
		break;
	case 3:
		_def = 1;
		_att = 5;
		_hp = 1;
		_mana = 75;
		break;
	case 4:
		_def = 3;
		_att = 1;
		_hp = 3;
		_mana = 80;
		break;
	}
}
void InitializeStatsEnemy(int& _ennemiLevel, int& _enemiAtt, int& _enemiHp)
{
	_ennemiLevel = 1;
	_enemiAtt = 10;
	_enemiHp = 55;
}
void ChoosenAction(int& _enemyHealth, int _strenghtUser)
{
	int _chose;
	cout << "Que veut tu faire ? : ";
	cout << "1- Attaquer" << "\n";
	Barr();
	cin >> _chose;
	switch (_chose)
	{
	case 1:
		EnemyTakesDamage(_enemyHealth, _strenghtUser);
	}
}