// InformationSecurity_HW1.cpp : 定義主控台應用程式的進入點。
//

#include <map>
#include<iostream>
#include<string>
#include <vector>
#include<cctype>

using namespace std;

void toLower(string& s)
{
	for (int i = 0; i < s.size(); i++)
		s[i]=tolower(s[i]);
}

bool isExist(string s, char c)
{
	for each (char tmp in s)
		if (tmp == c)
			return true;
	return false;
}

void deleteExist(string& s, char c)
{
	for (int i = 0; i < s.size(); i++)
		if (s[i] == c)
			s.erase(s.begin() + i);
}

void translate(string& s, char c, char c2)
{
	for (int i = 0; i < s.size(); i++)
		if (s[i] == c2)
			s[i] = c;
}

vector<int> findPosition(vector<string> m, char c)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (m[i][j] == c)
				return 	vector<int>{i, j};
}

void caesar()
{
	cout << "Key:";
	int key = 0;
	while (cin >> key)
	{
		if (key == 0)
			return;
		cout << "CipherText:";
		string cipherText;
		cin >> cipherText;
		toLower(cipherText);
		for (int i = 0; i < cipherText.size(); i++)
		{
			cipherText[i] -= key;
			if (cipherText[i] < 'a')
				cipherText[i] += 26;
		}
		cout << "PlainText:" << cipherText << endl << "Key:";
	}
}

void monoalphabetic()
{
	cout << "Key:";
	string key;
	while (cin >> key)
	{
		if (key == "0")
			return;
		toLower(key);
		map<char, char> keyMap;
		for (int i = 0; i < key.size(); i++)
			keyMap[key[i]] = 'a' + i;
		cout << "CipherText:";
		string cipherText;
		cin >> cipherText;
		toLower(cipherText);
		for (int i = 0; i < cipherText.size(); i++)
			cipherText[i] = keyMap[cipherText[i]];
		cout << "PlainText:" << cipherText << endl <<"Key:";
	}
}

void playfair()
{
	cout << "Key:";
	string key;
	while (cin >> key)
	{
		if (key == "0")
			return;
		toLower(key);
		vector<string> matrix;
		string fill;
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		//刪除j
		deleteExist(alphabet, 'j');
		//去除重複
		for each (char tmp in key)
			if (!isExist(fill, tmp))
				fill.push_back(tmp);
		//製作keyMatrix
		for (int i = 0; i < 5; i++)
		{
			string tmp;
			matrix.push_back(tmp);
			for (int j = 0; j < 5; j++)
			{
				//放入key
				if (fill.size() > 0)
				{
					matrix[i].push_back(fill[0]);
					deleteExist(alphabet, fill[0]);
					fill.erase(fill.begin());
				}
				//放入剩餘字母
				else
				{
					matrix[i].push_back(alphabet[0]);
					alphabet.erase(alphabet.begin());
				}
			}
		}
		//解密
		cout << "CipherText:";
		string cipherText;
		cin >> cipherText;
		toLower(cipherText);
		//替換j
		translate(cipherText, 'i', 'j');
		for (int i = 0; i < cipherText.size(); i += 2)
		{
			vector<int> pos1 = findPosition(matrix, cipherText[i]);
			vector<int> pos2 = findPosition(matrix, cipherText[i + 1]);
			//同Row
			if (pos1[0] == pos2[0])
			{
				cipherText[i] = pos1[1] == 0 ? matrix[pos1[0]][4] : matrix[pos1[0]][pos1[1] - 1];
				cipherText[i + 1] = pos2[1] == 0 ? matrix[pos2[0]][4] : matrix[pos2[0]][pos2[1] - 1];
			}
			//同Column
			else if (pos1[1] == pos2[1])
			{
				cipherText[i] = pos1[0] == 0 ? matrix[4][pos1[0]] : matrix[pos1[0] - 1][pos1[1]];
				cipherText[i + 1] = pos2[0] == 0 ? matrix[4][pos2[0]] : matrix[pos2[0] - 1][pos2[1]];
			}
			//都不同
			else
			{
				cipherText[i] = matrix[pos1[0]][pos2[1]];
				cipherText[i + 1] = matrix[pos2[0]][pos1[1]];
			}
		}

		cout << "PlainText:" << cipherText << endl << "Key:";
	}
}

void vernamAutokey()
{
	string key;
	cout << "Key:";
	while (cin >> key)
	{
		if (key == "0")
			return;
		toLower(key);
		cout << "CipherText:";
		string cipherText;
		cin >> cipherText;
		toLower(cipherText);
		for (int i = 0; i < cipherText.size(); i++)
		{
			cipherText[i] -= 'a';
			if(i<key.size())
				key[i] -= 'a';
		}
		if (key.size() > cipherText.size())
		{
			for (int i = 0; i < cipherText.size(); i++)
				cipherText[i] ^= key[i];
		}
		else
		{
			for (int i = 0; i < cipherText.size(); i += key.size())
			{
				for (int j = i; j < i + key.size() && j < cipherText.size(); j++)
				{
					cipherText[j] ^= key[j%key.size()];
					cipherText[j] %= 26;
					key[j%key.size()] = cipherText[j];
				}
			}
		}
		for(int i=0;i<cipherText.size();i++)
			cipherText[i] += 'a';
		cout << "PlainText:" << cipherText << endl << "Key:";
	}
}

void rowTransposition()
{
	int keySize;
	cout << "KeySize:";
	while (cin >> keySize)
	{
		if (keySize == 0)
			return;
		cout << "Key:";
		vector<int> key(keySize);
		for (int i = 0; i < keySize; i++)
			cin >> key[i];
		map<int, int> keyMap;
		for(int i=0;i<key.size();i++)
			keyMap[key[i]] = i;
		cout << "CipherText:";
		string cipherText;
		cin >> cipherText;
		toLower(cipherText);
		int row = cipherText.size() / key.size();
		int reminder = cipherText.size() % key.size();
		vector<string> matrix(row);
		for (int i = 0; i < cipherText.size() / key.size(); i++)
			matrix[i] = string(key.size(), ' ');
		if (reminder != 0)
			matrix.push_back(string(reminder,' '));

		for (int i = 0; i < key.size(); i++)
		{
			int position = keyMap[(i+1)];
			for (int j = 0; j < row + (reminder == 0 ? 0 : 1) && position<matrix[j].size(); j++)
			{
				matrix[j][position] = cipherText[0];
				cipherText.erase(cipherText.begin());
			}
		}
		
		//拼成一句
		for each (string var in matrix)
		{
			cipherText += var;
		}

		cout << "PlainText:" << cipherText << endl << "KeySize:";
	}
}

void product()
{
	int keySize;
	cout << "KeySize:";
	while (cin >> keySize)
	{
		if (keySize == 0)
			return;
		cout << "Key:";
		vector<int> key(keySize);
		for (int i = 0; i < keySize; i++)
			cin >> key[i];
		cout << "CipherText:";
		string cipherText;
		cin >> cipherText;
		toLower(cipherText);
		string plainText(cipherText);
		for (int i = 0; i < cipherText.size(); i++)
		{
			plainText[key[i]-1] = cipherText[i];
		}

		cout << "PlainText:" << plainText << endl << "KeySize:";
	}
}

int main()
{
	int input;
	cout << "1.Caesar\n2.Monoalphabetic\n3.Playfair\n4.VernamAutokey\n5.RowTransposition\n6.Product\n題目:";
	while (cin >> input)
	{
		switch (input)
		{
		case 1:caesar(); break;
		case 2:monoalphabetic(); break;
		case 3:playfair(); break;
		case 4:vernamAutokey(); break;
		case 5:rowTransposition(); break;
		case 6:product(); break;
		}
		cout << "1.Caesar\n2.Monoalphabetic\n3.Playfair\n4.VernamAutokey\n5.RowTransposition\n6.Product\n題目:";
	}

    return 0;
}