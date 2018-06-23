#include <iostream>
#include <unordered_map>

/*
   Put a class of self define should have the following operation:
   bool operator==(const T& t) const              	for member function or
   bool operator==(const T& t1, const T& t2)    	for global operator
   hash<T>											for struct hash<T> with operator()
 */

struct Point
{
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int x, int y): x(x), y(y) {}
};

int mygcd(int m, int n)
{
	while(n != 0) {
		int tmp = m % n;
		m = n;
		n = tmp;
	}
	return m;
}
//Para of a line in math: Ax+By+C=0;
struct Para
{
	int A;
	int B;
	int C;
	Para(int a, int b, int c)
	{
		if(a < 0 || (a == 0 && b < 0)) {
			a = -a;
			b = -b;
			c = -c;
		}
		int maxFactor = -1;
		if(a > 0) {
			maxFactor = (b > 0 ? mygcd(a, b) : mygcd(a, -b));
		}
		else {
			maxFactor = b;
		}
		maxFactor = (c > 0 ? mygcd(maxFactor, c) : mygcd(maxFactor, -c));
		A = a / maxFactor;
		B = b / maxFactor;
		C = c / maxFactor;
	}
	
	bool operator==(const Para& p) const
	{
		return (A == p.A && B == p.B && C == p.C);
	}

};
/*
bool operator==(const Para& p1, const Para& p2)
{
	return (p1.A == p2.A && p1.B == p2.B && p1.C == p2.C);
}
*/

namespace std
{
	template<>
	struct hash<Para>
	{
		std::size_t operator()(const Para& p) const
		{
			return std::hash<int>()(p.A) ^ 
				(std::hash<int>()(p.B) << 1) ^
				(std::hash<int>()(p.C) << 2);
		}
	};
}

int main()
{
	std::unordered_map<Para, int> lineCount;
	Para p1(1, 0, 1);
	lineCount[p1]++;
	Para p2(1, 0, 1);
	lineCount[p2]++;
	std::cout << lineCount.size() << std::endl;
	return 0;
}
