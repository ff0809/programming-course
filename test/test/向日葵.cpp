//#include <iostream>
//#define LAWN_LENGTH 9
//#define SUNLIGHT_TIME 3
//#define TARGET_SUNLIGHT 500
//using namespace std;
//
//time_t current = 0;  // 模拟记录时间，单位s
//
//class PlantBase {
//private:
//	int hp;				// 植物的生命值
//
//protected:
//	time_t plant_time;	// 植物被种下的时间
//	time_t interval;	// 植物攻击或生产的时间间隔
//
//public:
//	PlantBase(int hp, time_t interval);
//	bool hurt(int damage);
//};
//
///***********在这里给出PlantBase的实现***********/
//PlantBase::PlantBase(int hp, time_t interval) :hp(hp), interval(interval), plant_time(0) {};
//bool PlantBase::hurt(int damage)
//{
//	hp -= damage;
//	return hp > 0;
//}
///********************************************/
//
//
///********在这里给出SunFlower的声明和实现*********/
//class SunFlower:public PlantBase {
//public:
//	SunFlower();
//	void settime(time_t t);
//	bool canproduce(time_t cur);
//
//};
//
//SunFlower::SunFlower() :PlantBase(60, 5) {};
//
//void SunFlower::settime(time_t t)
//{
//	plant_time = t;
//}
//
//bool SunFlower::canproduce(time_t cur)
//{
//	time_t diff = cur - plant_time;
//	return diff % 5 == 0 && diff > 0;
//}
///********************************************/
//
//int main()
//{
//	/* 变量声明 */
//	SunFlower* lawn[LAWN_LENGTH] = {};
//	int plant_num = 0; // 记录植物总数
//
//	// 输入数据
//	int sunlight;
//	time_t n;
//	cin >> sunlight >> n;
//
//	while (true) {
//		// 1. 环境：每3/6/9/...s掉落一个25的阳光
//		if (current % SUNLIGHT_TIME == 0 && current > 0) {
//			sunlight += 25;
//		}
//
//		/* 2. 植物：产阳光 */
//		for (int i = 0; i < LAWN_LENGTH; i++)
//		{
//			if (lawn[i] != NULL)
//			{
//				if (lawn[i]->canproduce(current))
//				{
//					sunlight += 25;
//				}
//			}
//		}
//
//		/* 3. 玩家：放植物（一次只能放一株）*/
//		int pos1 = -1;
//		for (int i = 0; i < LAWN_LENGTH; i++)
//		{
//			if (!lawn[i])
//			{
//				pos1 = i;
//				break;
//			}
//		}
//		if (pos1 != -1 && sunlight >= 50)
//		{
//			lawn[pos1] = new SunFlower();
//			lawn[pos1]->settime(current);
//			plant_num++;
//			sunlight -= 50;
//		}
//
//		/* 4. 僵尸：从第n秒开始，每一秒最右侧的向日葵会收到10*(current-n)的伤害 */
//		int pos2 = -1;
//		for (int i = LAWN_LENGTH - 1; i >= 0; i--)
//		{
//			if (lawn[i])
//			{
//				pos2 = i;
//				break;
//			}
//		}
//		if (pos2 != -1&&current>=n)
//		{
//			time_t dam_t = 10 * (current - n); 
//			int dam;
//			if (dam_t > static_cast<time_t>(std::numeric_limits<int>::max()))
//				dam = std::numeric_limits<int>::max();
//			else
//				dam = static_cast<int>(dam_t);
//			if (!lawn[pos2]->hurt(dam))
//			{
//				delete lawn[pos2];
//				plant_num--;
//				lawn[pos2] = NULL;
//			}
//		}
//
//		cout << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << endl;
//
//		// 5. 游戏胜利/失败判断
//		if (sunlight >= TARGET_SUNLIGHT) {
//			cout << "游戏胜利" << endl;
//			break;
//		}
//		else if (current >= n && plant_num == 0) {  // 提前判定失败
//			cout << "游戏失败" << endl;
//			break;
//		}
//		else if (current >= 100) {  // 如果第100秒过去仍未积累足够阳光，则判负
//			cout << "游戏失败" << endl;
//			break;
//		}
//
//		current++;
//	}
//
//	// 内存回收
//	for (int i = 0; i < LAWN_LENGTH; ++i) {
//		if (lawn[i])
//			delete lawn[i];
//	}
//
//	return 0;
//}