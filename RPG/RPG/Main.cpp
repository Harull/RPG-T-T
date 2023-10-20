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
#pragma endregion


int main()
{
	
	
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