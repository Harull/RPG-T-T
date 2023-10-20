#include <iostream>
#include <string>
using namespace std;
void ClassChosen();
void AskWitchStatAdd(int& _def, int& _att, int& _hp);
int main()
{
	ClassChosen();
	AskWitchStatAdd(_def, _att, _hp);
	system("cls");
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


void AskWitchStatAdd(int& _def, int& _att, int& _hp)
{
	int _statAdd;
	cout << "Bravo tu a gagner quel stat veut tu ajouter" << endl;
	cout << "Tes stat Actuelle : Defense Attaque Vie" << endl;
	cout << "\t\t\t" << _def << "\t" << _att << "    " << _hp << endl;
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
