#include <iostream>
#include <string>
using namespace std;
void ClassChosen();

int main()
{
	ClassChosen();

	return 0;
}

void EnemyTakesDamage(int*& _enemyHealth, int _strenghtUser)
{
	int* _newHealth = new int(*_enemyHealth - _strenghtUser);
	delete _enemyHealth;
	_enemyHealth = _newHealth;
}


void ClassChosen()
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
}