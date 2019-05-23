#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
#if 1
ifstream fin("B-large-practice.in");
ofstream fout("B-large-practice.out");
#define cin fin
#define cout fout
#endif
struct Point {
    double x, y, w;
};
const double eps = 1e-6;
int main() {
    int T;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        int N;
        cin >> N;
        vector<Point> points1, points2;
        vector<int> idxs;
        for (int i = 0; i < N; ++i) {
            double x, y, w;
            cin >> x >> y >> w;
            points1.emplace_back(Point{x, y, w});
            points2.emplace_back(Point{x, y, w});
        }
        sort(points1.begin(), points1.end(), [](const Point &a, const Point &b) {
            return a.x + a.y < b.x + b.y;
        });
        sort(points2.begin(), points2.end(), [](const Point &a, const Point &b) {
            return a.y - a.x < b.y - b.x;
        });
        double sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += points1[i].w;
        }
        double half = 0;
        double idx = -1, idy = -1;
        for (int i = 0; i < N; ++i) {
            half += points1[i].w;
            if (half + eps >= sum / 2) {
                idx = i;
                break;
            }
        }
        half = 0;
        for (int i = 0; i < N; ++i) {
            half += points2[i].w;
            if (half + eps >= sum / 2) {
                idy = i;
                break;
            }
        }
        if (idx == -1 || idy == -1) {
            cout << "error" << endl;
            exit(1);
        }
        double b1 = points1[idx].x + points1[idx].y;
        double b2 = points2[idy].y - points2[idy].x;
        double y0 = (b1 + b2) / 2;
        double x0 = (b1 - b2) / 2;
        sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += max(fabs(points1[i].x - x0), fabs(points1[i].y - y0)) * points1[i].w;
        }
        cout << "Case #" << cas << ": " << setiosflags(ios::fixed) << setprecision(7) << sum << endl;
    }
    return 0;
}