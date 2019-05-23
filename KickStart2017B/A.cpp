#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
#if 1
ifstream fin("A-large-practice.in");
ofstream fout("A-large-practice.out2");
#define cin fin
#define cout fout
#endif

const int MOD = (int)(1e9 + 7);
vector<long long> pow2;
void init() {
    pow2.resize(100000);
    pow2[0] = 1;
    for (int i = 1; i <= 100000; ++i) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }
}
int main() {
    int T;
    cin >> T;
    init();
    for (int cas = 1; cas <= T; ++cas) {
        int N;
        cin >> N;
        vector<int> nums;
        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            nums.emplace_back(x);
        }
        // sort(nums.begin(), nums.end());
        long long sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum = (sum + (nums[i] % MOD * pow2[i]) % MOD) % MOD;
        }
        for (int i = 0; i < nums.size(); ++i) {
            sum = (sum - (nums[i] % MOD * pow2[nums.size() - i - 1]) % MOD + MOD) % MOD;
        }
        cout << "Case #" << cas << ": " << sum << endl;
    }
    return 0;
}