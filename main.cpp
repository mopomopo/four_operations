#include "stdafx.h"
#include "stack.h"
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <stdlib.h>
#include <stack>
#include <queue>
//#include "otherFunction.h"
using namespace std;

queue<string> s1;
stack<string> s2;
stack<string> cal;

int rankd(char c3);
string functiond(string c);
int sortd(string c, int length);
/*
int convertToDouble(string str) {
	int d=0;
	stringstream ss(d);
	if (ss >> d)
		return d;
	return 0.0;
}*/
string convertToString(double d) {
	stringstream ss;
	if (ss << d)
		return ss.str();
	return "invalid conversion";
}

void display() {

	cout << "***********************************************************************************" << endl
		<< "*                                                                                 *" << endl
		<< "*                            此为四则运算程序                                     *" << endl
		<< "*                                                                                 *" << endl
		<< "*                       请输入正确表达式，如 -(3+3)*-2                            *" << endl
		<< "*                                                                                 *" << endl
		<< "*                       输入 ‘#’退出程序，                                      *" << endl
		<< "*                                                                                 *" << endl
		<< "*                       请确认开启英文输入法                                      *" << endl
		<< "*                                                                                 *" << endl
		<< "***********************************************************************************" << endl << endl;
}

int main()
{
	
	int k = 0;
	bool flag = false;
	string s;// = "-(1+3)*-2.5)";
	//string s2="0";
	string save[50];
	                      
	//获取输入的每个元素并存入save中
	//if (s[0] == '-') {\
		s2 += s;\
		s = s2;\
	}
	display();

	while (1) {
		for (int i=0 ; i < 50; i++) {
			if (save[i] == "\0")break;
			save[i] = "\0";
		}

		cout << "此处输入表达式：";
		cin >> s;
		if (s[0] == '#')break;

		k = 0;
		flag = false;
		for (int i = 0; i < s.size(); i++) {
			if (isdigit(s[i]) || s[i] == '.') {
				save[k] += s[i];
				flag = true;
			}
			else
			{
				if (flag) {
					k++;
					flag = false;
				}
				save[k++] = s[i];

			}
		}

		//将中缀表达式转成前缀表达式
		for (int i = k; i >= 0; i--) {

			sortd(save[i], k + 1);
			//	cout <<endl<< save[i]<<"      ";
		}
		//查看s1内容的代码
		/*	for (; s1.size() != 0;) {
			cout << s1.front() << "   ";
			s1.pop();
		}*/


		while (1) {

			if (cal.size() == 1 && s1.size() == 0)break;
			//if (s1.size() == 0)cout << "111";
			if (isdigit(s1.front()[0])) {
				cal.push(s1.front());

			}
			else
			{
				functiond(s1.front());

			}
			s1.pop();
			if (s1.size() == 0)break;
		}

		string s3;
		bool flag3 = false, flag4 = true;
		if (cal.size() == 0)cout << "错误" << endl;
		else {
			int i = 0; char *p;
			for (; !isdigit(cal.top()[i]); i++);
			p = &cal.top()[i];
			if (i % 2)
				cout << "             计算结果为：" <<"-" << p << endl;
			else
				cout << "             计算结果为：" << p << endl;
		}
		cal.pop();

	}
	system("PAUSE");
    return 0;
}

int rankd(char c3) {
	switch (c3) {

	case '-': return 1;

	case '*': return 2;

	case '/': return 2;

	case '+': return 3;

	case ')': return 4;
	}
	return 6;
}

string functiond(string c) {
	double p, q;
	bool flag = false;
	string s2="-";

	switch (c[0]) {
	case '-':
		//if (cal.size() == 0)cout << "222"; else cout << cal.top();
		s2+=cal.top();
		cal.pop();
		
		//cout << endl << p << "       " << q;
		cal.push(s2);
		s2 = "-";
		return "0";
	case '+':
		//if (cal.size() == 0)cout << "222"; else cout << cal.top();
		p = stod(cal.top());
		cal.pop();
		q = stod(cal.top());
		cal.pop();
		//cout << endl << p << "       " << q;
		cal.push(convertToString(p + q));
		return "0";

	case '*':

		p = stod(cal.top());
		cal.pop();
		q = stod(cal.top());
		cal.pop();
		cal.push(convertToString(p * q));
		return "0";
	case '/':

		p = stod(cal.top());
		cal.pop();
		q = stod(cal.top());
		cal.pop();
		cal.push(convertToString(p / q));
		return "0";

		return "3";
	}
}
int sortd(string c, int length) {
	static int k = 0;
	int p, q;
	k++;
	char save;
	if (isdigit(c[0])) {
		s1.push(c);
	}

	if (c[0] == ')') { s2.push(c); }
	if (c[0] == '(') {
		while (s2.top()[0] != ')') {
			s1.push(s2.top());
			s2.pop();
		}
		s2.pop();
	}
	if (c[0] == '*') {
		while (1) {
			if (!s2.empty())  save = s2.top()[0]; else save = 6;

			if (rankd(save) < 2) {
				s1.push(s2.top());
				s2.pop();
			}
			else {
				s2.push("*");
				break;
			}
		}
	}
	if (c[0] == '/') {
		while (1) {
			if (!s2.empty())  save = s2.top()[0]; else save = 6;

			if (rankd(save) < 2) {
				s1.push(s2.top());
				s2.pop();
			}
			else {
				s2.push("/");
				break;
			}
		}
	}
	if (c[0] == '+') {
		while (1) {
			if (!s2.empty())  save = s2.top()[0]; else save = 6;


			if (rankd(save) < 3) {
				s1.push(s2.top());
				s2.pop();
			}
			else {
				s2.push("+");
				break;
			}
		}
	}
	if (c[0] == '-') {
		while (1) {
			if (!s2.empty())  save = s2.top()[0]; else save = 6;

			if (rankd(save) < 3) {
				s1.push(s2.top());
				s2.pop();
			}
			else {
				s2.push("-");
				break;
			}
		}
	}

	if (k>=length) {
		k=0;
		while (!s2.empty()) {
			s1.push(s2.top());

			s2.pop();
		}
	}
	return 0;
}