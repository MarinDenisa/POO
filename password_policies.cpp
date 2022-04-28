#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <ctype.h>
using namespace std;
class Policy
{
protected:
	bool isChecked;
public:
	virtual void check(const string& p) = 0;
	bool getCheck()const
	{
		return isChecked;
	}
};
class LengthPolicy : public Policy
{
private:
	uint16_t minLength, maxLength;
public:
	LengthPolicy(uint16_t min)
	{
		minLength = min;
		maxLength = 255;
	}
	LengthPolicy(uint16_t min, uint16_t max)
	{
		minLength = min;
		maxLength = max;
	}
	void check(const string& p)
	{
		if (p.length() < minLength || p.length() > maxLength)
			isChecked = false;
		else isChecked = true;
	}
};
class ClassPolicy : public Policy
{
private:
	uint16_t minClassCount;
public:
	ClassPolicy(uint16_t minClassCount)
	{
		this->minClassCount = minClassCount;
	}
	virtual void check(string const& p)
	{
		int ok = 0, ok1 = 0, ok2 = 0, ok3 = 0;
		for (int i = 0; i < p.length(); i++)
		{
			if (isalnum(p[i]) == 0)
			{
				ok3 = 1;
			}
			if (islower(p[i]) != 0)
			{
				ok = 1;
			}
			if (isupper(p[i]) != 0)
			{
				ok1 = 1;
			}
			if (isdigit(p[i]) != 0)
			{
				ok2 = 1;
			}
		}
		if (ok + ok1 + ok2 + ok3 < minClassCount)
			isChecked = false;
		else isChecked = true;
	}
};
class IncludePolicy :public Policy
{
private:
	char characterType;
public:
	IncludePolicy(char characterType)
	{
		this->characterType = characterType;
	}
	void check(string const& p)
	{
		isChecked = 0;
		for (int i = 0; i < p.size(); i++)
		{
			if (characterType == '$')
			{
				if (ispunct(p[i]))
				{
					isChecked = 1;
					break;
				}
			}
			if (characterType == 'A')
			{
				if (isupper(p[i]))
				{
					isChecked = 1;
					break;
				}
			}
			if (characterType == 'a')
			{
				if (islower(p[i]))
				{
					isChecked = 1;
					break;
				}
			}
			if (characterType == '0')
			{
				if (isdigit(p[i]))
				{
					isChecked = 1;
					break;
				}
			}
		}

	}
};
class NotIncludePolicy : public Policy
{
private:
	char characterType;
public:
	NotIncludePolicy(char characterType)
	{
		this->characterType = characterType;
	}
	virtual void check(string const& p)
	{
		int ok = 0;
		if (isalnum(characterType) == 0)
		{
			for (int i = 0; i < p.length(); i++)
			{
				if (isalnum(p[i]) == 0)
				{
					ok = 1;
				}
				if (ok == 1)
					break;
			}
		}
		if (islower(characterType) != 0)
		{
			for (int i = 0; i < p.length(); i++)
			{
				if (islower(p[i]) != 0)
				{
					ok = 1;
				}
				if (ok == 1)
					break;
			}
		}
		if (isupper(characterType) != 0)
		{
			for (int i = 0; i < p.length(); i++)
			{
				if (isupper(p[i]) != 0)
				{
					ok = 1;;
				}
				if (ok == 1)
					break;
			}
		}
		if (isdigit(characterType) != 0)
		{
			for (int i = 0; i < p.length(); i++)
			{
				if (isdigit(p[i]) != 0)
				{
					ok = 1;
				}
				if (ok == 1)
					break;
			}
		}
		if (ok == 0)
			isChecked = true;
		else isChecked = false;
	}
};
class RepetitionPolicy : public Policy
{
private:
	uint16_t maxCount;
public:
	RepetitionPolicy(uint16_t maxCount)
	{
		this->maxCount = maxCount;
	}
	virtual void check(string const& p)
	{
		int k = 0, ok = 0;
		for (int i = 0; i < p.length() - maxCount; i++)
		{
			ok = 0;
			for (int j = i + 1; j < maxCount + 1 + i; j++)
			{
				if (p[i] == p[j])
				{
					ok++;
				}
			}
			if (ok >= maxCount)
			{
				k = 1;
				isChecked = false;
				break;
			}
		}
		if (k == 0)
			isChecked = true;
	}
};
class ConsecutivePolicy :public Policy
{
private:
	uint16_t maxCount;
public:
	ConsecutivePolicy(uint16_t maxCount)
	{
		this->maxCount = maxCount;
	}
	virtual void check(string const& p)
	{
		isChecked = true;
		for (int i = 0; i < p.length() - maxCount; i++)
		{
			int ok = 1;
			int k = 0;
			for (int j = i + 1; j < maxCount + 1 + i; j++)
			{
				k++;
				if (p[i] + k == p[j] || p[i] - k == p[j])
					ok++;
			}
			if (ok > maxCount)
			{
				isChecked = false;
				break;
			}
		}
	}
};
string checkPassword(string parola, vector<Policy*>v)
{
	int ok = 0;
	for (int i = 0; i < v.size(); i++) {
		v[i]->check(parola);
		if (v[i]->getCheck() == true)
		{
			ok++;
		}
	}
	if (ok == v.size())
		return "OK";
	else return "NOK";
}
int main()
{
	vector<Policy*>v;
	int n, max, min;
	string command;
	char c;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> command;
		if (command == "class")
		{
			cin >> max;
			v.push_back(new ClassPolicy(max));
		}
		if (command == "length")
		{
			int j = scanf("%d %d", &min, &max);
			if (j == 1)
				v.push_back(new LengthPolicy(min));
			if (j == 2)
				v.push_back(new LengthPolicy(min, max));
		}
		if (command == "consecutive")
		{
			cin >> max;
			v.push_back(new ConsecutivePolicy(max));
		}
		if (command == "repetition")
		{
			cin >> max;
			v.push_back(new RepetitionPolicy(max));
		}
		if (command == "include")
		{
			cin >> c;
			v.push_back(new IncludePolicy(c));
		}
		if (command == "ninclude")
		{
			cin >> c;
			v.push_back(new NotIncludePolicy(c));
		}
	}
	vector<string>cuvant;
	string cuv;
	while (cin >> cuv){
		cuvant.push_back(cuv);
	}
	for (int i = 0; i < cuvant.size(); i++)
	{
		cout << checkPassword(cuvant[i], v);
		cout << endl;
	}
	return 0;
}
