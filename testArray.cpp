/*
������ѧ��C++���Գ�����ơ��γ�
ģ��Vectorʵ����ҵ
by S.Hu
Array����Գ���
2015/10
���Ի�����Microsoft Visual Studio 2015
*/
#include<iostream>
#include"Array.h"

int main() {
	Array<int> myArr(6, 1);
	Array<int> hisArr{ 12,23,34,45,56,67,78,89,90 };

	//������ʾ��
	for (Array<int>::iterator myIter = myArr.begin();myIter != myArr.end();++myIter) { std::cout << *myIter << '\t'; }
	std::cout << std::endl;
	for (Array<int>::reverse_iterator hisIter = hisArr.rbegin();hisIter != hisArr.rend();++hisIter) { std::cout << *hisIter << '\t'; }
	std::cout << std::endl;

	//���ݶ�ȡ���޸ĺ���
	myArr.assign(10,7);
	myArr.push_back(1);
	myArr.push_back(2);
	myArr.front() = 0;
	myArr.at(7) = 0;
	for (unsigned int i = 0;i < myArr.size();++i) { std::cout << myArr[i] << '\t'; }
	std::cout << std::endl;
	myArr.insert(myArr.begin() + 4, hisArr.begin() + 1, hisArr.end() - 2);
	myArr.pop_back();
	myArr.erase(myArr.begin() + 1, myArr.begin() + 3);
	for (Array<int>::iterator myIter = myArr.begin();myIter != myArr.end();++myIter) { std::cout << *myIter << '\t'; }
	std::cout << std::endl;
	swap(myArr, hisArr);
	for (Array<int>::iterator myIter = myArr.begin();myIter != myArr.end();++myIter) { std::cout << *myIter << '\t'; }
	std::cout << std::endl;
	
	//������غ���
	myArr.clear();
	std::cout << "capacity=" << hisArr.capacity() << " size=" << hisArr.size() << " empty=" << hisArr.empty() << std::endl;

	system("pause>nul");
	return 0;
}