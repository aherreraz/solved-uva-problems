#include <bits/stdc++.h>
#define EPS 1e-7
using namespace std;
int comparar(double a, double b)
{
	if (a - b > EPS) return 1;
	if (b - a > EPS) return -1;
	return 0;
}
struct Point
{
	double x, y;
	Point () {}
	Point (double px, double py) : x(px), y(py) {}
};
double operator ~ (const Point &a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}
Point operator - (const Point &a, const Point &b)
{
	return Point (a.x - b.x, a.y - b.y);
}
double operator ^ (const Point &a, const Point &b)
{
	return a.x * b.y - b.x * a.y;
}
bool cmp (Point p1, Point p2)
{
	return p1.x > p2.x || (p1.x == p2.x && p1.y > p2.y);
}
vector<Point> convexHull (vector<Point> P)
{
	int n = (int)P.size(), k = 0;
	vector<Point> H(2 * n);
	sort(P.begin(), P.end(), cmp);
	for (int i = 0; i < n; i++)
	{
		while (k >= 2 && comparar((P[i] - H[k - 1]) ^ (H[k - 2] - H[k - 1]), 0) > 0)
			k--;
		H[k++] = P[i];
	}
	for (int i = n - 2, t = k + 1;  i >= 0; i--)
	{
		while (k >= t && comparar((P[i] - H[k - 1]) ^ (H[k - 2] - H[k - 1]), 0) > 0)
			k--;
		H[k++] = P[i];
	}
	H.resize(k);
	H.pop_back();
	return H;
}
double perimeterPolygon (vector<Point> P)
{
	int n = P.size();
	double res = 0;
	for (int i = 0; i < n; i++)
		res += ~(P[i] - P[(i + 1) % n]);
	return res;
}
int main()
{
	int n, caso = 1;
	vector <Point> v;
	while (scanf("%d",&n) && n != 0)
	{
		if (caso > 1)
			printf("\n");
		v.clear(); v.resize(n);
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &v[i].x, &v[i].y);
		vector<Point> hull = convexHull(v);
		printf("Region #%d:\n",caso++);
		int m = hull.size();
		for (int i = 0; i < m; i++)
			printf("(%.1lf,%.1lf)-", hull[i].x, hull[i].y);
		printf("(%.1lf,%.1lf)\n", hull[0].x, hull[0].y);
		printf("Perimeter length = %.2lf\n", perimeterPolygon(hull));
	}
}
