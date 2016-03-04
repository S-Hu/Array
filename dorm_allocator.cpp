#pragma warning(disable: 4800)
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

// ����������
int T = 20;

// �����������ֵ
const int MaxN = 300;

// ������
int n;

// �˺���֮������۾���graph[i][j] ��ʾ i �� j �Ĵ��
int graph[MaxN + 1][MaxN + 1];

// ÿ���˵�ƫ������
int rate[MaxN + 1][MaxN + 1];

// ÿ����������
const int DormLimit = 4;

// ���������ֵ
const int MaxDCnt = (MaxN / DormLimit) + bool(MaxN % DormLimit);

// ������
int dcnt;

// ÿ�������ĸ�����
int inDrm[MaxN + 1];

// ������䷽����
class Plan {
public:
	int s;// ���������������ڳ�Ա�����ֵ��ܺͣ����������������
	int rmax;// �����������˶��������Ա�������������ֵ
	int dorm[MaxDCnt + 1][DormLimit + 1];// ��������

	Plan();// ���캯��
	void clear();// ��շ���
	bool operator>(const Plan &) const;// �ж�һ�������Ƿ�������һ������
	void calc_max_roommate_rank();// �����������
	void random_divide();// ���һ��������������������һ�� 1~n �����У���ǰ����ÿ����һ������
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

	// ö������
	for (int id = 1; id <= dcnt; ++id) {
		// ö����������
		for (int k1 = 1; k1 <= DormLimit && dorm[id][k1]; ++k1) {
			int x = dorm[id][k1];

			// ö��������������
			for (int k2 = 1; k2 <= DormLimit && dorm[id][k2]; ++k2)
				if (k1 != k2) {
					int y = dorm[id][k2];

					// �����������
					if (rate[x][y] > rmax) rmax = rate[x][y];
				}
		}
	}
}

void Plan::random_divide() {
	int perm[MaxN + 1];// �洢 1~n ��һ������

	for (int i = 1; i <= n; ++i) perm[i] = i;

	// �������
	for (int i = 1; i <= n; ++i)
		swap(perm[i], perm[rand() % i + 1]);

	// ��˳�������
	int id = 0;
	int i = 1;

	while (i <= n) {
		++id;

		for (int k = 1; k <= DormLimit && i <= n; ++k, ++i)
			inDrm[this->dorm[id][k] = perm[i]] = id;
	}

	// ���㷽���������ܺ�
	s = 0;

	for (int id = 1; id <= dcnt; ++id) {
		for (int k1 = 1; k1 < DormLimit && dorm[id][k1]; ++k1)
			for (int k2 = 1; k2 <= DormLimit && dorm[id][k2]; ++k2)
				if (k1 != k2)
					s += graph[dorm[id][k1]][dorm[id][k2]];
	}

	// �����������
	calc_max_roommate_rank();
}

// ���շ������
Plan Ans;

//����ģʽ
void read() {
	// ��������������������
	cout << "������������n(n<=300): ";
	cin >> n;

	if (n > MaxN) {
		cout << "Error: overflow! n <= " << MaxN;
		exit(1);
	}

	dcnt = n / DormLimit + static_cast<bool>(n % DormLimit);
	/* �����������ڲ��Ե�������۾��� */
	struct Coor {
		int x, y;
	};
	Coor *cr = new Coor[n + 1];
	// ÿ���˷���һ������
	const int MaxCr = 1000000;

	for (int i = 1; i <= n; ++i) {
		cr[i].x = rand() % MaxCr;
		cr[i].y = rand() % MaxCr;
	}

	// ������������پ�������ֵ
	int dis_max = 0;
	auto max = [](int a, int b) ->int {return a > b ? a : b;};

	for (int i = 1; i < n; ++i)
		for (int j = i + 1; j <= n; ++j)
			dis_max = max(dis_max, abs(cr[i].x - cr[j].x) + abs(cr[i].y - cr[j].y));

	// ��������Ϊ�������ȥ����������پ���
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			graph[i][j] = dis_max - (abs(cr[i].x - cr[j].x) + abs(cr[i].y - cr[j].y));

	delete[]cr;
}

//����ģʽ
void read(ifstream &myFile) {
	// ��������������������
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
	// �������۾���
	myFile.seekg(4, ios::beg);

	for (int i = 1; i <= n; ++i)
		myFile.read(reinterpret_cast<char *>(&graph[i][1]), 4 * n);

	myFile.close();
}


void chief() {
	// ����ƫ������rate[][]
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
		// �����ʼ����
		Cur.random_divide();

		while (true) {
			Candi.clear();
			New = Cur;

			// ö��Ҫ������������
			for (int i = 1; i < n; ++i)
				for (int j = i + 1; j <= n; ++j)
					if (inDrm[i] != inDrm[j]) { //i��j��ǰ����һ������
						int id = inDrm[i];
						int jd = inDrm[j];

						// �������ˡ��������ֺ����������
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

						// �Ƚϴ˷�����֮ǰ�����ŷ���������
						if (New > Candi) Candi = New;

						// �ָ�ԭ����
						for (int k = 1; k <= DormLimit; ++k) {
							if (New.dorm[id][k] == j) New.dorm[id][k] = i;

							if (New.dorm[jd][k] == i) New.dorm[jd][k] = j;
						}

						New.s = Cur.s;
						New.rmax = Cur.rmax;
					}

			// �ȽϽ�����ķ������ַ���������
			if (Candi > Cur) {
				Cur = Candi;

				for (int id = 1; id <= dcnt; ++id)
					for (int k = 1; k <= DormLimit && Cur.dorm[id][k]; ++k)
						inDrm[Cur.dorm[id][k]] = id;
			} else break;
		}

		if (Cur > Ans) Ans = Cur; // �Ƚ����ŷ����ʹ𰸵�����
	}
}

// �������
void write() {
	// �ض��������clog���ļ�
	ofstream myLog("report.log");
	streambuf *log = clog.rdbuf(myLog.rdbuf());
	// ��������ܺ�
	clog << "Ans = " << Ans.s << '\n';
	ofstream myFile;
	myFile.open("result.dat", ios::binary | ios::out);

	for (int id = 1; id <= dcnt; ++id) {
		clog << "\ndorm[" << id << ']';

		// ���������Ա
		for (int k = 1; k <= DormLimit && Ans.dorm[id][k]; ++k) {
			myFile.write(reinterpret_cast<char *>(&Ans.dorm[id][k]), 4);
			clog << ' ' << Ans.dorm[id][k];
		}

		// ���������ÿ�˶������˵���������
		for (int k1 = 1; k1 <= DormLimit && Ans.dorm[id][k1]; ++k1) {
			clog << "\nfor " << Ans.dorm[id][k1] << ":\n";

			for (int k2 = 1; k2 <= DormLimit && Ans.dorm[id][k2]; ++k2)
				if (k1 != k2) {
					int r = rate[Ans.dorm[id][k1]][Ans.dorm[id][k2]];
					clog << Ans.dorm[id][k2] << " ranks " << r << " in all.\n";
				}
		}

		static const int blank = 0;
		myFile.write(reinterpret_cast<const char *>(&blank), 4); //����һ���ָ���
	}

	myFile.close();
	myLog.close();
	clog.rdbuf(log);
	cout << "Procedure completed successfully.\nFor details, please refer to \'report.log\'.";
}

int main(const int argc, const char *argv[]) {
	srand(unsigned(time(NULL)));// �������������

	if (argc == 1) { // <------�޲�������������ģʽ
		cout << "Dorm Allocating Engine ����ģʽ\n";
		read();
		cout << "������������T: ";
		cin >> T;
	} else { // <------����ģʽ
		ifstream myFile;
		myFile.open(argv[1], ios::binary | ios::in);

		if (myFile.rdstate()) { // ����ļ��Ƿ�򿪳ɹ�
			cout << "Error: Cannot open file.";
			exit(1);
		} else read(myFile);

		if (argc == 3 && atoi(argv[2]))T = atoi(argv[2]);
	}

	chief();
	write();
	return 0;
}
