//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <limits>
//#define LAWN_LENGTH 9
//#define SUNLIGHT_TIME 3
//#define TARGET_DAMAGE 3000
//using namespace std;
//
//time_t current = 0;  // 模拟记录时间，单位s
//
///*************基类声明**************/
//class PlantBase {
//private:
//	int hp;			// 植物的生命值
//	char* name;		// 植物的名字（长度不超过20）
//
//protected:
//	int cost;		// 种植花费的阳光
//	time_t plant_time;	// 植物被种下的时间
//
//public:
//	PlantBase(int hp, int cost);
//	PlantBase(PlantBase& base);	// 复制构造函数
//	~PlantBase();
//	bool hurt(int damage);
//	char* get_name();
//};
//
///*************基类实现**************/
//PlantBase::PlantBase(int hp, int cost) :hp(hp), cost(cost), plant_time(0), name(NULL) {};
//
//PlantBase::PlantBase(PlantBase& base)
//{
//	hp = base.hp;
//	plant_time = base.plant_time;
//	cost = base.cost;
//	if (base.name != NULL)
//	{
//		name = new char[20];
//		strcpy(name, base.name);
//	}
//	else
//	{
//		name = NULL;
//	}
//}
//
//PlantBase::~PlantBase()
//{
//	delete[]name;
//}
//
//bool PlantBase::hurt(int damage)
//{
//	hp -= damage;
//	return hp > 0;
//}
//
//char* PlantBase::get_name()
//{
//	if (name == NULL)
//	{
//		name = new char[20];
//		cin >> name;
//	}
//	return name;
//}
//
///*************派生类声明和实现**************/
//class Repeater :public PlantBase
//{
//public:
//	Repeater();
//	void settime(time_t t);
//	bool canfight(time_t cur);
//};
//
//Repeater::Repeater() :PlantBase(60, 150) {};
//
//void Repeater::settime(time_t t)
//{
//	plant_time = t;
//}
//
//bool Repeater::canfight(time_t cur)
//{
//	return (cur - plant_time) % 2 == 0 && cur > plant_time;
//}
//
//class GatlingPea :public PlantBase
//{
//public:
//	GatlingPea(PlantBase& base) :PlantBase(base) {};
//	void settime(time_t t);
//	bool canfight(time_t cur);
//};
//
//void GatlingPea::settime(time_t t)
//{
//	plant_time = t;
//}
//
//bool GatlingPea::canfight(time_t cur)
//{
//	return (cur - plant_time) % 2 == 0 && cur > plant_time;
//}
//
///*************主函数**************/
//int main()
//{
//	PlantBase* lawn[LAWN_LENGTH] = {};
//	time_t planttime[LAWN_LENGTH * 2] = { 0 };
//	char series[LAWN_LENGTH][20] = { 0 };
//	int plant_num = 0; // 记录植物总数
//	int plant_count = 0;
//
//	// 输入数据
//	int sunlight, damage = 0;
//	time_t n;
//	cin >> sunlight >> n;
//
//	while (true) {
//		// 1. 环境：每3秒掉落25阳光
//		if (current % SUNLIGHT_TIME == 0 && current > 0) {
//			sunlight += 25;
//		}
//
//		/* 2. 植物：发动攻击 */
//		for (int i = 0; i < LAWN_LENGTH; i++)
//		{
//			if (lawn[i] == NULL) continue;
//			if (strcmp(series[i], "Repeater") == 0)
//			{
//				Repeater* r = static_cast<Repeater*>(lawn[i]);
//				if (r->canfight(current)) damage += 20;
//			}
//			else if (strcmp(series[i], "GatlingPea") == 0)
//			{
//				GatlingPea* g = static_cast<GatlingPea*>(lawn[i]);
//				if (g->canfight(current)) damage += 40;
//			}
//		}
//
//		/* 3. 玩家：放植物/升级 */
//		bool planted = false;
//		// 优先种双发豌豆
//		for (int i = 0; i < LAWN_LENGTH; i++)
//		{
//			if (lawn[i] == NULL && sunlight >= 150)
//			{
//				Repeater* r = new Repeater();
//				r->settime(current);
//				r->get_name();
//				lawn[i] = r;
//				strcpy(series[i], "Repeater");
//				planttime[plant_count++] = current;
//				plant_num++;
//				sunlight -= 150;
//				planted = true;
//				break;
//			}
//		}
//		// 双发豌豆放满后，升级最左侧双发为机枪
//		if (!planted && plant_num == LAWN_LENGTH)
//		{
//			for (int i = 0; i < LAWN_LENGTH; i++)
//			{
//				if (lawn[i] != NULL && strcmp(series[i], "Repeater") == 0 && sunlight >= 150)
//				{
//					GatlingPea* g = new GatlingPea(*lawn[i]);
//					g->settime(current); 
//					delete lawn[i];
//					lawn[i] = g;
//					strcpy(series[i], "GatlingPea");
//					planttime[plant_count++] = current;
//					sunlight -= 150;
//					planted = true;
//					break;
//				}
//			}
//		}
//
//		/* 4. 僵尸：攻击最右侧植物 */
//		if (current >= n)
//		{
//			int right_pos = -1;
//			// 找到最右侧存活的植物
//			for (int i = LAWN_LENGTH - 1; i >= 0; i--)
//			{
//				if (lawn[i] != NULL)
//				{
//					right_pos = i;
//					break;
//				}
//			}
//			if (right_pos != -1)
//			{
//				int dam = static_cast<int>(10 * (current - n));
//				if (!lawn[right_pos]->hurt(dam))
//				{
//					delete lawn[right_pos];
//					lawn[right_pos] = NULL;
//					strcpy(series[right_pos], "");
//					plant_num--;
//				}
//			}
//		}
//
//		// 5. 游戏胜利/失败判断
//		if (damage >= TARGET_DAMAGE) {
//			cout << "游戏胜利" << endl;
//			break;
//		}
//		else if (current >= n && plant_num == 0) {
//			cout << "游戏失败" << endl;
//			break;
//		}
//		else if (current >= 100) {
//			cout << "游戏失败" << endl;
//			break;
//		}
//
//		current++;
//	}
//
//	// 输出结果
//	cout << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << endl;
//
//	if (plant_count != 0)
//	{
//		cout << "每一株植物种下的时刻：" << endl;
//		for (int i = 0; i < plant_count; i++)
//		{
//			cout << planttime[i] << " ";
//		}
//		cout << endl;
//	}
//
//	if (plant_num != 0)
//	{
//		cout << "幸存植物的名字：" << endl;
//		for (int i = 0; i < LAWN_LENGTH; i++)
//		{
//			if (lawn[i] == NULL) continue;
//			if (strcmp(series[i], "Repeater") == 0)
//				cout << "Repeater: " << lawn[i]->get_name() << endl;
//			else if (strcmp(series[i], "GatlingPea") == 0)
//				cout << "Gatling: " << lawn[i]->get_name() << endl;
//		}
//	}
//
//	// 内存回收
//	for (int i = 0; i < LAWN_LENGTH; i++)
//	{
//		delete lawn[i];
//		lawn[i] = NULL;
//	}
//
//	return 0;
//}