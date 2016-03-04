#pragma warning(disable: 4800)
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

// 程序计算次数
int T = 20;

// 总人数的最大值
const int MaxN = 300;

// 总人数
int n;

// 人和人之间的评价矩阵。graph[i][j] 表示 i 对 j 的打分
int graph[MaxN + 1][MaxN + 1];

// 每个人的偏好序列
int rate[MaxN + 1][MaxN + 1];

// 每个宿舍人数
const int DormLimit = 4;

// 宿舍数最大值
const int MaxDCnt = (MaxN / DormLimit) + bool(MaxN % DormLimit);

// 宿舍数
int dcnt;

// 每个人在哪个宿舍
int inDrm[MaxN + 1];

// 宿舍分配方案类
class Plan {
public:
	int s;// 方案中所有宿舍内成员互相打分的总和，即方案的总满意度
	int rmax;// 方案中所有人对其宿舍成员评价排名的最差值
	int dorm[MaxDCnt + 1][DormLimit + 1];// 方案内容

	Plan();// 构造函数
	void clear();// 清空方案
	bool operator>(const Plan &) const;// 判断一个方案是否优于另一个方案
	void calc_max_roommate_rank();// 计算最差排名
	void random_divide();// 随机一个方案。随机方法是随机一个 1~n 的排列，从前往后每四人一个宿舍
};

Plan::Plan() {
	this->clear();
}

void Plan::clear() {
	s = 0;
	rmax = MaxN + 1;
	memset(dorm, 0, sizeof(dorm));
}

bool Plan::operator>(const Plan &another) const {
	return rmax < another.rmax || (rmax == another.rmax && s > another.s);
}

void Plan::calc_max_roommate_rank() {
	rmax = 1;

	// 枚举宿舍
	for (int id = 1; id <= dcnt; ++id) {
		// 枚举宿舍内人
		for (int k1 = 1; k1 <= DormLimit && dorm[id][k1]; ++k1) {
			int x = dorm[id][k1];

			// 枚举宿舍内其他人
			for (int k2 = 1; k2 <= DormLimit && dorm[id][k2]; ++k2)
				if (k1 != k2) {
					int y = dorm[id][k2];

					// 更新最差排名
					if (rate[x][y] > rmax) rmax = rate[x][y];
				}
		}
	}
}

void Plan::random_divide() {
	int perm[MaxN + 1];// 存储 1~n 的一个排列

	for (int i = 1; i <= n; ++i) perm[i] = i;

	// 随机排列
	for (int i = 1; i <= n; ++i)
		swap(perm[i], perm[rand() % i + 1]);

	// 按顺序分宿舍
	int id = 0;
	int i = 1;

	while (i <= n) {
		++id;

		for (int k = 1; k <= DormLimit && i <= n; ++k, ++i)
			inDrm[this->dorm[id][k] = perm[i]] = id;
	}

	// 计算方案的评分总和
	s = 0;

	for (int id = 1; id <= dcnt; ++id) {
		for (int k1 = 1; k1 < DormLimit && dorm[id][k1]; ++k1)
			for (int k2 = 1; k2 <= DormLimit && dorm[id][k2]; ++k2)
				if (k1 != k2)
					s += graph[dorm[id][k1]][dorm[id][k2]];
	}

	// 计算最差排名
	calc_max_roommate_rank();
}

// 最终方案结果
Plan Ans;

//测试模式
void read() {
	// 读入人数，计算宿舍数
	cout << "请输入总人数n(n<=300): ";
	cin >> n;

	if (n > MaxN) {
		cout << "Error: overflow! n <= " << MaxN;
		exit(1);
	}

	dcnt = n / DormLimit + static_cast<bool>(n % DormLimit);
	/* 以下生成用于测试的随机评价矩阵 */
	struct Coor {
		int x, y;
	};
	Coor *cr = new Coor[n + 1];
	// 每个人分配一个坐标
	const int MaxCr = 1000000;

	for (int i = 1; i <= n; ++i) {
		cr[i].x = rand() % MaxCr;
		cr[i].y = rand() % MaxCr;
	}

	// 求两点间曼哈顿距离的最大值
	int dis_max = 0;
	auto max = [](int a, int b) ->int {return a > b ? a : b;};

	for (int i = 1; i < n; ++i)
		for (int j = i + 1; j <= n; ++j)
			dis_max = max(dis_max, abs(cr[i].x - cr[j].x) + abs(cr[i].y - cr[j].y));

	// 两人评分为最大距离减去两点间曼哈顿距离
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			graph[i][j] = dis_max - (abs(cr[i].x - cr[j].x) + abs(cr[i].y - cr[j].y));

	delete[]cr;
}

//调用模式
void read(ifstream &myFile) {
	// 读入人数，计算宿舍数
	myFile.read(reinterpret_cast<char *>(&n), 4);

	if (n > MaxN) {
		cout << "Error: overflow! n <= " << MaxN;
		exit(1);
	}

	myFile.seekg(0, ios::end);

	if (int(myFile.tellg()) != 4 * n * n + 4) {
		cout << "Error: Bad file format.";
		exit(1);
	}

	dcnt = n / DormLimit + static_cast<bool>(n % DormLimit);
	// 读入评价矩阵
	myFile.seekg(4, ios::beg);

	for (int i = 1; i <= n; ++i)
		myFile.read(reinterpret_cast<char *>(&graph[i][1]), 4 * n);

	myFile.close();
}


void chief() {
	// 计算偏好序列rate[][]
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			int sum = 0;

			for (int k = 1; k <= n; k++)
				if (graph[i][j] < graph[i][k]) sum++;

			rate[i][j] = sum;
		}

	Plan Cur, Candi, New;

	for (int t = 1; t <= T; ++t) {
		stringstream title;
		title << "title Computing, please wait... " << t << '/' << T << " ---Do NOT close this window!---";
		system(title.str().c_str());
		// 随机初始方案
		Cur.random_divide();

		while (true) {
			Candi.clear();
			New = Cur;

			// 枚举要交换的两个人
			for (int i = 1; i < n; ++i)
				for (int j = i + 1; j <= n; ++j)
					if (inDrm[i] != inDrm[j]) { //i和j当前不在一个宿舍
						int id = inDrm[i];
						int jd = inDrm[j];

						// 交换两人。计算评分和与最差排名
						for (int k = 1; k <= DormLimit && New.dorm[id][k]; ++k)
							if (New.dorm[id][k] != i) {
								(New.s -= graph[New.dorm[id][k]][i]) += graph[New.dorm[id][k]][j];
								(New.s -= graph[i][New.dorm[id][k]]) += graph[j][New.dorm[id][k]];
							} else New.dorm[id][k] = j;

						for (int k = 1; k <= DormLimit && New.dorm[jd][k]; ++k)
							if (New.dorm[jd][k] != j) {
								(New.s -= graph[New.dorm[jd][k]][j]) += graph[New.dorm[jd][k]][i];
								(New.s -= graph[j][New.dorm[jd][k]]) += graph[i][New.dorm[jd][k]];
							} else New.dorm[jd][k] = i;

						New.calc_max_roommate_rank();

						// 比较此方案和之前的最优方案的优劣
						if (New > Candi) Candi = New;

						// 恢复原方案
						for (int k = 1; k <= DormLimit; ++k) {
							if (New.dorm[id][k] == j) New.dorm[id][k] = i;

							if (New.dorm[jd][k] == i) New.dorm[jd][k] = j;
						}

						New.s = Cur.s;
						New.rmax = Cur.rmax;
					}

			// 比较交换后的方案和现方案的优劣
			if (Candi > Cur) {
				Cur = Candi;

				for (int id = 1; id <= dcnt; ++id)
					for (int k = 1; k <= DormLimit && Cur.dorm[id][k]; ++k)
						inDrm[Cur.dorm[id][k]] = id;
			} else break;
		}

		if (Cur > Ans) Ans = Cur; // 比较最优方案和答案的优劣
	}
}

// 输出方案
void write() {
	// 重定向输出流clog到文件
	ofstream myLog("report.log");
	streambuf *log = clog.rdbuf(myLog.rdbuf());
	// 输出评分总和
	clog << "Ans = " << Ans.s << '\n';
	ofstream myFile;
	myFile.open("result.dat", ios::binary | ios::out);

	for (int id = 1; id <= dcnt; ++id) {
		clog << "\ndorm[" << id << ']';

		// 输出宿舍人员
		for (int k = 1; k <= DormLimit && Ans.dorm[id][k]; ++k) {
			myFile.write(reinterpret_cast<char *>(&Ans.dorm[id][k]), 4);
			clog << ' ' << Ans.dorm[id][k];
		}

		// 输出宿舍内每人对其他人的评价排名
		for (int k1 = 1; k1 <= DormLimit && Ans.dorm[id][k1]; ++k1) {
			clog << "\nfor " << Ans.dorm[id][k1] << ":\n";

			for (int k2 = 1; k2 <= DormLimit && Ans.dorm[id][k2]; ++k2)
				if (k1 != k2) {
					int r = rate[Ans.dorm[id][k1]][Ans.dorm[id][k2]];
					clog << Ans.dorm[id][k2] << " ranks " << r << " in all.\n";
				}
		}

		static const int blank = 0;
		myFile.write(reinterpret_cast<const char *>(&blank), 4); //这是一个分隔符
	}

	myFile.close();
	myLog.close();
	clog.rdbuf(log);
	cout << "Procedure completed successfully.\nFor details, please refer to \'report.log\'.";
}

int main(const int argc, const char *argv[]) {
	srand(unsigned(time(NULL)));// 设置随机数种子

	if (argc == 1) { // <------无参数启动，测试模式
		cout << "Dorm Allocating Engine 测试模式\n";
		read();
		cout << "请输入计算次数T: ";
		cin >> T;
	} else { // <------调用模式
		ifstream myFile;
		myFile.open(argv[1], ios::binary | ios::in);

		if (myFile.rdstate()) { // 检查文件是否打开成功
			cout << "Error: Cannot open file.";
			exit(1);
		} else read(myFile);

		if (argc == 3 && atoi(argv[2]))T = atoi(argv[2]);
	}

	chief();
	write();
	return 0;
}
