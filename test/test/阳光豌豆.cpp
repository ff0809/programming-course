#include <iostream>
#include <limits>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 1000
using namespace std;

time_t current = 0;  // 模拟记录时间，单位s

/*************将基类的声明拷贝至此**************/
class PlantBase {
private:
	int hp;			// 植物的生命值
	char* name;		// 植物的名字（长度不超过20）

protected:
	int cost;		// 种植花费的阳光
	time_t plant_time;	// 植物被种下的时间

public:
	PlantBase(int hp, int cost);
	~PlantBase();
	bool hurt(int damage);
	char* get_name();
};

/********************************************/


/*************在这里给出基类的实现**************/
PlantBase::PlantBase(int hp, int cost) :hp(hp), cost(cost), plant_time(0), name(NULL) {};

PlantBase::~PlantBase()
{
	delete[]name;
}

bool PlantBase::hurt(int damage)
{
	hp -= damage;
	return hp > 0;
}

char* PlantBase::get_name()
{
	if (name == NULL)
	{
		name = new char[20];
		cin >> name;
	}
	return name;
}

/********************************************/


/**********在这里给出派生类的声明和实现***********/
class SunFlower :virtual public PlantBase {
public:
	SunFlower();                 // 无参构造（内部初始化 PlantBase）
	void settime(time_t t);
	bool canproduce(time_t cur);

};

SunFlower::SunFlower() : PlantBase(60, 125) {}   // 无参 ctor，仍初始化 PlantBase(60,125)

void SunFlower::settime(time_t t)
{
	plant_time = t;
}

bool SunFlower::canproduce(time_t cur)
{
	time_t diff = cur - plant_time;
	return diff % 5 == 0 && diff > 0;
}

class PeaShooter :virtual public PlantBase
{
public:
	PeaShooter();                // 无参构造（内部初始化 PlantBase）
	void settime(time_t t);
	bool canfight(time_t cur);
};

PeaShooter::PeaShooter() : PlantBase(60, 125) {} // 无参 ctor，仍初始化 PlantBase(60,125)

void PeaShooter::settime(time_t t)
{
	plant_time = t;
}

bool PeaShooter::canfight(time_t cur)
{
	if ((cur - plant_time) % 2 == 0 && (cur - plant_time) > 0)
	{
		return true;
	}
	return false;
}

class SunnyPea :public SunFlower, public PeaShooter
{
public:
	// 最派生类只初始化虚基类 PlantBase
	SunnyPea() : PlantBase(60, 125) {};

	void settime(time_t t)
	{
		plant_time = t;
	}

	bool canproduce(time_t cur)
	{
		return SunFlower::canproduce(cur);
	}

	bool canfight(time_t cur)
	{
		return PeaShooter::canfight(cur);
	}
};

/********************************************/


int main()
{
	/* 变量声明 */
	SunnyPea* lawn[LAWN_LENGTH] = {};
	time_t planttime[LAWN_LENGTH * 2] = {};
	int plant_num = 0; // 记录植物总数
	int plant_count = 0;
	// 输入数据
	int sunlight, damage = 0;
	time_t n;
	cin >> sunlight >> n;

	while (true) {
		// 1. 环境：每3/6/9/...s掉落一个25的阳光
		if (current % SUNLIGHT_TIME == 0 && current > 0) {
			sunlight += 25;
		}

		/* 2. 植物：发动攻击 */
		for (int i = 0; i < LAWN_LENGTH; i++)
		{
			if (lawn[i] != NULL)
			{
				if (lawn[i]->canproduce(current))
				{
					sunlight += 25;
				}
				if (lawn[i]->canfight(current))
				{
					damage += 10;
				}
			}
		}

		/* 3. 玩家：放植物（一次只能放一株）*/
		for (int i = 0; i < LAWN_LENGTH; i++)
		{
			if (lawn[i] == NULL && sunlight >= 125)
			{
				SunnyPea* s = new SunnyPea();
				s->get_name();
				s->settime(current);
				lawn[i] = s;
				planttime[plant_count] = current;
				plant_count++;
				plant_num++;
				sunlight -= 125;
				break;
			}
		}

		/* 4. 僵尸：从第n秒开始，每一秒最右侧的植物会收到10*(current-n)的伤害 */
		for (int i = LAWN_LENGTH - 1; i >= 0; i--)
		{
			if (lawn[i] != NULL && current >= n)
			{
				time_t dam_t = 10 * (current - n);
				int dam;
				if (dam_t > static_cast<time_t>(numeric_limits<int>::max()))
					dam = numeric_limits<int>::max();
				else
					dam = static_cast<int>(dam_t);
				if (!(lawn[i]->hurt(dam)))
				{
					delete lawn[i];
					lawn[i] = NULL;
					plant_num--;
				}
				break;
			}
		}

		// 5. 游戏胜利/失败判断
		if (damage >= TARGET_DAMAGE) {
			cout << "游戏胜利" << endl;
			break;
		}
		else if (current >= n && plant_num == 0) {  // 提前判定失败
			cout << "游戏失败" << endl;
			break;
		}
		else if (current >= 100) {  // 如果第100秒过去仍未积累足够阳光，则判负
			cout << "游戏失败" << endl;
			break;
		}

		current++;
	}

	cout << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << endl;

	/* 其他输出与内存回收 */
	if (plant_count != 0)
	{
		cout << "每一株植物种下的时刻：" << endl;
		for (int i = 0; i < plant_count; i++)
		{
			cout << planttime[i] << " ";
		}
		cout << endl;
	}

	if (plant_num != 0)
	{
		cout << "幸存植物的名字：" << endl;
		for (int i = 0; i < LAWN_LENGTH; i++)
		{
			if (lawn[i] != NULL)
			{
				cout << lawn[i]->get_name() << endl;
			}
		}
	}

	for (int i = 0; i < LAWN_LENGTH; i++)
	{
		if (lawn[i])
		{
			delete lawn[i];
		}
	}

	return 0;
}