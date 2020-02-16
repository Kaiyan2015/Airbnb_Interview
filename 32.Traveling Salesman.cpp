#include<unistd.h>
#include<stack>
#include"bits/stdc++.h"

#define dbv(v) cout << #v << "="; for (auto _x : v) cout << _x << ", "; cout << endl
using namespace std;

class Solution {
public:
    /**
     * @param n: an integer,denote the number of cities
     * @param roads: a list of three-tuples,denote the road between cities
     * @return: return the minimum cost to travel all cities
     */
//    https://www.bilibili.com/video/av36363110/
//    https://www.lintcode.com/problem/traveling-salesman/my-submissions?_from=ladder&&fromId=109
//    ���͵�TSP����    
    int minCost(int n, vector<vector<int>> &roads) {
        if (roads.size() == 0) return 0;
        vector<vector<int>> graph(n, vector<int>(n, -1));
        for(int i=0;i<n;i++) graph[i][i]=0;
        for (const auto &v:roads){

            // lintcode�ϲ��������д�����������һ������������Ĳ�������
            if(graph[v[0] - 1][v[1] - 1]!=-1 && graph[v[0] - 1][v[1] - 1]<v[2]) continue;

            graph[v[0] - 1][v[1] - 1] = v[2];  // ����1��ʼת��Ϊ��0��ʼ
            graph[v[1] - 1][v[0] - 1] = v[2];
        }

        vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX)); // dp[i][j]���������i�����нڵ㣬������jΪĩβʱ����С��cost
        vector<vector<int>> parent(1 << n, vector<int>(n));

        dp[1<<0][0]=0; // ��Ϊ����涨ֻ�ܴ����0��ʼ

        for (int i = 1; i < (1 << n); i++) {
            for (int j = 0; j < n; j++) {
                if (!(i & (1 << j))) continue;
                int prev = i - (1 << j);
                for (int k = 0; k < n; k++) {
                    if (dp[prev][k] == INT_MAX) continue;
                    if(graph[k][j]==-1) continue;  // ���������֮��û������
                    if (dp[prev][k] + graph[k][j] >= dp[i][j]) continue;
                    dp[i][j] = dp[prev][k] + graph[k][j];
                    parent[i][j] = k;
                }
            }
        }

        // ����֮�ã�������ӡ·��
        /*
        auto it = min_element(dp.back().begin(), dp.back().end());
        int cur = it - dp.back().begin();
        cout << cur << endl;
        int s = (1 << n) - 1;
        while (s) {
            cout << cur << " "<<dp[s][cur]<<endl;
            int prev = parent[s][cur];

            s &= ~(1 << cur);
            cur = prev;
        }
        cout << "---------------" << endl;
        */

        int res = INT_MAX;
        for (const auto &t:dp.back()) res = min(res, t);

        return res;
    }
};

int main() {
    vector<vector<int>> roads = {{1,2,9},{2,3,1},{3,4,9},{4,5,4},{2,4,3},{1,3,2},{5,4,9}};
    int n = 5;
    Solution s;
    cout << s.minCost(n, roads) << endl;
    return 0;
}