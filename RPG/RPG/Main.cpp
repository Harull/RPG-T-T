#include <iostream>
#include <string>
using namespace std;

int main()
{
	int _def;
	int _att;
	int _hp;

	return 0;
}

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
	cin >> _chose;
	switch (_chose)
	{
	case 1:
		EnemyTakesDamage(_enemyHealth, _strenghtUser);
	}
}