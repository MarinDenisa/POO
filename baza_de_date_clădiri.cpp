#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//#define DEBUG_ENABLED
#define DEBUG_HOUSE "CasaIoan"
class Person
{
public:
	std::string mName;
	uint16_t mAge;
	double mSalary;
	Person()
	{
		this->mAge = 0;
		this->mSalary = 0;
		this->mName = "";
	}
	Person(std::string mName, uint16_t mAge, double mSalary)
	{
		this->mAge = mAge;
		this->mSalary = mSalary;
		this->mName = mName;
	}
	bool operator==(const Person& a)const
	{
		if (a.mName == mName && a.mSalary == mSalary && a.mAge == mAge)
			return true;
		return false;
	}
	bool operator<(const Person& a)const
	{
		if (mName < a.mName)
			return true;
		else return false;
	}
};
class Building
{
protected:
	std::string mBuildingName, mType;
	Person mCoordinator;
	std::vector<Person>mEmployees;
	std::vector<Person>mCitizens;
public:
	int GetSumOfAges()
	{
		int result = 0;
		for (auto it : mCitizens)
		{
			result += it.mAge;
		}
		return result;
	}
	double GetSalaryCoordinator()
	{
		return mCoordinator.mSalary;
	}
	double GetSalarySumEmployees()
	{
		double ok = 0;
		for (auto it : mEmployees)
		{
			ok = ok + it.mSalary;
		}
		return ok;
	}
	double GetSalarySumCitizens()
	{
		double result = 0.f;
		for (auto it : mCitizens)
		{
			result += it.mSalary;
		}
		return result;
	}
	int GetNumberOfCitizens()
	{
		int ok = 0;
		for (int i = 0; i < mCitizens.size(); i++)
		{
			if (mCitizens[i].mName != "")
				ok++;
		}
		return ok;
	}
	//doar test
	void Debug()
	{
		std::cout << "<------------------------------------------------------->" << std::endl;
		std::cout << mBuildingName << " " << mType << std::endl;
		std::cout << "Employees" << std::endl;
		for (auto val : mEmployees)
		{
			std::cout << val.mName << " ";
		}
		std::cout << std::endl;
		std::cout << "Citizens" << std::endl;
		for (auto val : mCitizens)
		{
			std::cout << val.mName << " ";
		}
		std::cout << std::endl;
		std::cout << "Coordinator: " << mCoordinator.mName << std::endl << std::endl;
	}
	Building()
	{
	}
	Building(std::string mBuildingName, std::string mType)
	{
		this->mBuildingName = mBuildingName;
		this->mType = mType;
	}
	virtual void add(const Person& a) = 0;
	virtual void remove(const Person& a) = 0;
	virtual Building* operator+(const Person& a) = 0;
	virtual Building* operator-()
	{
		return nullptr;
	}
	virtual Building* operator-(const Person& a)
	{
		return nullptr;
	}
	std::string getBuildingName()const
	{
		return mBuildingName;
	}
	std::string getType()const
	{
		return mType;
	}
	uint16_t getEmployeesSize()const
	{
		return mEmployees.size();
	}
	uint16_t getCitizensSize()const
	{
		return mCitizens.size();
	}
	Person getEmployee(uint16_t val)const
	{
		return mEmployees[val];
	}
	Person getCitizen(uint16_t val)const
	{
		return mCitizens[val];
	}
	Person getCoordinator()const
	{
		return mCoordinator;
	}
};
class Hospital : public Building
{
public:
	Hospital(std::string mBuildingName) :Building(mBuildingName, "Hospital")
	{
		mCitizens.clear();
		mEmployees.clear();
	}
	void add(const Person& a)override
	{
		mCitizens.push_back(a);
	}
	void remove(const Person& a)override
	{
		for (int i = 0; i < mCitizens.size(); i++)
		{
			if (mCitizens[i].mName == a.mName)
				mCitizens.erase(mCitizens.begin() + i);
		}
	}
	Building* operator+(const Person& a)override
	{
		mEmployees.push_back(Person(a));
		return this;
	}
	Building* operator-(const Person& a)override
	{
		for (int i = 0; i < mEmployees.size(); i++)
		{
			if (mEmployees[i].mName == a.mName)
				mEmployees.erase(mEmployees.begin() + i);
		}
		return this;
	}
	Building* operator-() override
	{
		cout << "operator -()";
		return nullptr;
	}
};

class PoliceStation :public Building
{
public:
	PoliceStation(std::string mBuildingName) :Building(mBuildingName, "PoliceStation")
	{
		mCitizens.clear();
		mEmployees.clear();
	}
	void add(const Person& a)override
	{
		mCitizens.push_back(a);
	}
	void remove(const Person& a)override
	{
		for (int i = 0; i < mCitizens.size(); i++)
		{
			if (mCitizens[i].mName == a.mName)
				mCitizens.erase(mCitizens.begin() + i);
		}
	}
	Building* operator+(const Person& a)override
	{
		mEmployees.push_back(Person(a));
		return this;
	}
	Building* operator-(const Person& a)override
	{
		for (int i = 0; i < mEmployees.size(); i++)
		{
			if (mEmployees[i].mName == a.mName)
				mEmployees.erase(mEmployees.begin() + i);
		}
		return this;
	}
	Building* operator-() override
	{
		cout << "operator -()";
		return nullptr;
	}
};
class CityHall : public Building
{
public:
	CityHall(std::string mBuildingName) : Building(mBuildingName, "CityHall")
	{
		mCitizens.clear();
		mCoordinator = Person();
	}
	void add(const Person& a)override
	{
		mCitizens.push_back(a);
	}
	void remove(const Person& a)override
	{
		for (int i = 0; i < mCitizens.size(); i++)
		{
			if (mCitizens[i].mName == a.mName)
				mCitizens.erase(mCitizens.begin() + i);
		}
	}
	Building* operator+(const Person& a)override
	{
		if (mCoordinator.mName == "")
			mCoordinator = a;
		return this;
	}
	Building* operator-() override
	{
		mCoordinator = Person();
		return this;
	}
};
class Block :public Building
{
private:
	uint16_t mMaxNumberPerFloor;
	int numar_etaje;
public:
	Block(std::string mBuildingName, int numar_etaje, uint16_t mMaxNumberPerFloor) :Building(mBuildingName, "Block")
	{
		this->mMaxNumberPerFloor = mMaxNumberPerFloor;
		mCitizens.clear();
		mCoordinator = Person();
		//se vor aloca numar_etaje * mMaxNumberPerFloor locații în acest std::vector,
		for (int i = 0; i < numar_etaje * mMaxNumberPerFloor; i++)
		{
			mCitizens.push_back(Person());
		}
	}
	void add(const Person& a)override
	{
		for (int i = 0; i < mCitizens.size(); i++)
		{
			if (mCitizens[i].mName == "")
			{
				mCitizens[i] = a;
				break;
			}
		}
	}
	void remove(const Person& a)override
	{
		for (int i = 0; i < mCitizens.size(); i++)
		{
			if (mCitizens[i].mName == a.mName && mCitizens[i].mAge >= 18)
				mCitizens.erase(mCitizens.begin() + i);
		}
	}
	Building* operator+(const Person& a)override
	{
		if (mCoordinator.mName == "")
			mCoordinator = a;
		return this;
	}
	Building* operator-() override
	{
		mCoordinator = Person();
		return this;
	}
};
class House :public Building
{
private:
	uint16_t mMaxNumber;
	int GetCurrentNumberOfPeople()
	{
		int nr = 0;
		if (mCoordinator.mName != "")
		{
			nr++;
		}
		nr += mCitizens.size();
		return nr;
	}
public:
	House(std::string mBuildingName, uint16_t mMaxNumber) : Building(mBuildingName, "House")
	{
		this->mMaxNumber = mMaxNumber;
		mCitizens.clear();
		mCoordinator = Person();
	}
	void add(const Person& a)override
	{
		if (GetCurrentNumberOfPeople() < mMaxNumber)
			mCitizens.push_back(a);
	}
	void remove(const Person& a)override
	{
		for (int i = 0; i < mCitizens.size(); i++)
		{
			if (mCitizens[i].mName == a.mName && mCitizens[i].mAge >= 18)
				mCitizens.erase(mCitizens.begin() + i);
		}
	}
	Building* operator+(const Person& a)override
	{
		if (mCoordinator.mName == "")
			mCoordinator = a;
		return this;
	}
	Building* operator-() override
	{
		mCoordinator = Person();
		return this;
	}
};
class City
{
private:
	vector<Building*>p;
	// Calculets nr of buildings of type
	int getNumbers(string type)
	{
		int ok = 0;
		for (auto it : p)
		{
			if (it->getType() == type)
				ok++;
		}
		return ok;
	}
public:
	City(vector<Building*>p)
	{
		this->p = p;
	}
	void DisplayAll()
	{
		cout << "Type: " << GetCityType() << endl;
		DisplayPacients();
		cout << "Average salary for doctors: " << GetAvgSalaryForEmployee("Hospital") << endl;
		cout << "Average salary for cops: " << GetAvgSalaryForEmployee("PoliceStation") << endl;
		cout << "Average salary for mayors: " << GetAvgSalaryForCoordinator("CityHall") << endl;
		cout << "Average salary for city hall employees: " << GetAvgSalaryForCitizen("CityHall") << endl;
		cout << "Average age of busted in police stations: " << GetAvgAgeCitizen("PoliceStation") << endl;
		DisplayHouseNBlock();
		DisplayAdmins();
	}
	string GetCityType()
	{

		if (getNumbers("CityHall") >= 3 && getNumbers("PoliceStation") >= 3 && getNumbers("Hospital") >= 2 && getNumbers("Block") >= 1)
		{
			return "Capital";
		}
		if (getNumbers("CityHall") >= 2 && getNumbers("PoliceStation") >= 2 && getNumbers("Hospital") >= 1 && getNumbers("Block") >= 1)
		{
			return "Town";
		}
		return "Village";
	}
	void DisplayPacients()
	{
		int ok = 0;
		for (auto it : p)
		{
			if (it->getType() == "Hospital")
			{
				ok = ok + it->getCitizensSize();
			}
		}
		cout << "Number of patients in hospitals: " << ok << endl;
	}
	double GetAvgSalaryForEmployee(string institution)
	{
		int nr = 0;
		double sum = 0;
		for (auto it : p)
		{
			if (it->getType() == institution)
			{
				sum = sum + it->GetSalarySumEmployees();
				nr = nr + it->getEmployeesSize();
			}
		}
		if (nr == 0)
			return 0;
		return sum / nr;
	}
	double GetAvgSalaryForCitizen(string institution)
	{
		int nr = 0;
		double sum = 0;
		for (auto it : p)
		{
			if (it->getType() == institution)
			{
				sum = sum + it->GetSalarySumCitizens();
				nr = nr + it->getCitizensSize();
			}
		}
		if (nr == 0)
			return 0;
		return sum / nr;
	}
	double GetAvgSalaryForCoordinator(string institution)
	{
		int nr = 0;
		double sum = 0;
		for (auto it : p)
		{
			if (it->getType() == institution)
			{
				if (it->getCoordinator().mName != "")
				{
					sum = sum + it->GetSalaryCoordinator();
					nr++;
				}
			}
		}
		if (nr == 0)
			return 0;
		return sum / nr;
	}
	double GetAvgAgeCitizen(string institution)
	{
		int nr = 0;
		double sum = 0;
		for (auto it : p)
		{
			if (it->getType() == institution)
			{
				sum = sum + it->GetSumOfAges();
				nr += it->getCitizensSize();
			}
		}
		if (nr == 0)
			return 0;
		return sum / nr;
	}
	void DisplayHome(Building* building)
	{
		cout << "Number of people in " << building->getType() << " " << building->getBuildingName() << ": ";
		int household = building->GetNumberOfCitizens();
		if (building->getCoordinator().mName != "")
		{
			household++;
		}
		cout << household;
		cout << endl;
	}
	void DisplayHouseNBlock()
	{
		for (auto val : p)
		{
			if (val->getType() == "House" || val->getType() == "Block")
				DisplayHome(val);
		}
	}
	void DisplayAdmins()
	{
		cout << "Administrators of house and block: ";
		vector<string> names;
		bool exists = false;
		for (auto val : p)
		{
			if (val->getType() == "House" || val->getType() == "Block")
			{
				bool ok = false;
				auto cName = val->getCoordinator().mName;
				for (int i = 0; i < names.size(); i++)
				{
					if (cName == names[i])
					{
						cout << cName << " ";
						exists = true;
						ok = true;
					}
				}
				if (!ok && cName != "")
				{
					names.push_back(cName);
				}
			}
		}
		if (!exists)
		{
			cout << "Nobody";
		}
	}
};
vector<Building*>v;
void addBuilding(string type)
{
	string cuv;
	cin >> cuv;
	if (type == "Block")
	{
		int etaje, maxetaj;
		cin >> etaje >> maxetaj;
		Block* p = new Block(cuv, etaje, maxetaj);
		v.push_back(p);
	}
	if (type == "House")
	{
		int maxnr;
		cin >> maxnr;
		House* p = new House(cuv, maxnr);
		v.push_back(p);
	}
	if (type == "Hospital")
	{
		Hospital* p = new Hospital(cuv);
		v.push_back(p);
	}
	if (type == "PoliceStation")
	{
		PoliceStation* p = new PoliceStation(cuv);
		v.push_back(p);
	}
	if (type == "CityHall")
	{
		CityHall* p = new CityHall(cuv);
		v.push_back(p);
	}
}
bool checkBuilding(string cuv)
{
	if (cuv == "Block" || cuv == "Hospital" || cuv == "House" || cuv == "PoliceStation" || cuv == "CityHall")
	{
		addBuilding(cuv);
		// cout << "Cladire: "<< cuv<<endl;
		return true;
	}
	return false;
}
Building* findBuilding(string name)
{
	for (auto it : v)
	{
		if (it->getBuildingName().compare(name) == 0)
		{
			return it;
		}
	}
	return nullptr;
}
void addCitizen(string cuv)
{
	if (cuv == "citizen")
	{
		int age;
		double salary;
		string name;
		cin >> name >> age >> salary;
		Person* p = new Person(name, age, salary);
		string building;
		cin >> building;
		auto b = findBuilding(building);
#ifdef DEBUG_ENABLED
		if (b->getBuildingName() == DEBUG_HOUSE)
		{
			cout << "//";
		}
#endif
		b->add(*p);
	}
	if (cuv == "employee")
	{
		int age;
		double salary;
		string name;
		cin >> name >> age >> salary;
		Person* p = new Person(name, age, salary);
		string building;
		cin >> building;
		auto b = findBuilding(building);
#ifdef DEBUG_ENABLED
		if (b->getBuildingName() == DEBUG_HOUSE)
		{
			cout << "//";
		}
#endif
		findBuilding(building)->operator+(*p);
	}
	if (cuv == "coordinator")
	{
		int age;
		double salary;
		string name;
		cin >> name >> age >> salary;
		Person* p = new Person(name, age, salary);
		string building;
		cin >> building;
		auto b = findBuilding(building);
#ifdef DEBUG_ENABLED
		if (b->getBuildingName() == DEBUG_HOUSE)
		{
			cout << "//";
		}
#endif
		findBuilding(building)->operator+(*p);
	}
}
void removefromBuilding(Building* building, Person p, int type)
{
	if (type == 0) // citizen
	{
#ifdef DEBUG_ENABLED
		if (building->getBuildingName() == DEBUG_HOUSE)
		{
			cout << "//";
		}
#endif
		building->remove(p);
	}
	if (type == 1) // employee
	{
#ifdef DEBUG_ENABLED
		if (building->getBuildingName() == DEBUG_HOUSE)
		{
			cout << "//";
		}
#endif
		building->operator-(p);
	}
	if (type == 2) // coordinator
	{
#ifdef DEBUG_ENABLED
		if (building->getBuildingName() == DEBUG_HOUSE)
		{
			cout << "//";
		}
#endif
		building->operator-();
	}
}
void removePerson()
{
	string cuv;
	cin >> cuv;
	if (cuv == "citizen") // type 0
	{
		int age;
		double salary;
		string name;
		cin >> name;
		Person* p = new Person(name, 0, 0);
		string building;
		cin >> building;
		removefromBuilding(findBuilding(building), *p, 0);
	}
	if (cuv == "employee") // type 1
	{
		int age;
		double salary;
		string name;
		cin >> name;
		Person* p = new Person(name, 0, 0);
		string building;
		cin >> building;
		removefromBuilding(findBuilding(building), *p, 1);
	}
	if (cuv == "coordinator") //type 2
	{
		int age;
		double salary;
		string name;
		cin >> name;
		Person* p = new Person(name, 0, 0);
		string building;
		cin >> building;
		removefromBuilding(findBuilding(building), *p, 2);
	}
}
void check()
{
	string cuv;
	cin >> cuv;
	if (!checkBuilding(cuv))
	{
		// cout << "NU este cladire"<<endl;
		addCitizen(cuv);
	}
}
void readCommand(string command)
{
	if (command == "add")
	{
		check();
	}
	if (command == "remove")
	{
		removePerson();
	}
}
void Display()
{
	cout << v.size() << endl;
	for (auto it : v)
	{
		it->Debug();
	}
}
int main()
{
	string command;
	while (cin >> command)
	{
		readCommand(command);
	}
	City* city = new City(v);
	city->DisplayAll();
	return 0;
}
