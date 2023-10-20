#include <iostream>
#include <string>
using namespace std;

int main()
{
	

	return 0;
}

void EnemyTakesDamage(int*& _enemyHealth, int _strenghtUser)
{
	int* _newHealth = new int(*_enemyHealth - _strenghtUser);
	delete _enemyHealth;
	_enemyHealth = _newHealth;
}
