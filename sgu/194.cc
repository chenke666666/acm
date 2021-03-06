// =====================================================================================
// 
//       Filename:  194.cc
// 
//    Description:  http://acm.sgu.ru/problem.php?contest=0&problem=194
//    无源汇上下界可行流
// 
//        Version:  1.0
//        Created:  2013年05月23日 12时33分28秒
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Barty (bt), maiL@barty.ws
//        Company:  http://barty.ws
// 
// =====================================================================================


#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 400 + 9;
const int M = 1000000 + 9;

struct edge {
    int v, f, next;
} e[M];
int p[N], eid;
int low[M];
void init() {
    memset(p, -1, sizeof(p));
    eid = 0;
}
void insert(int x, int y, int f) {
    e[eid].v = y;
    e[eid].f = f;
    e[eid].next = p[x];
    p[x] = eid++;
}
void insert2(int x, int y, int f) {
    insert(x, y, f); insert(y, x, 0);
}
int dist[N], n, m;
int q[N], source, sink;
bool bfs() {
    q[0] = sink;
    memset(dist, -1, sizeof(dist));
    dist[sink] = n;
    int l = 0, r = 1;
    for (; l-r; ) {
        int now = q[l++];
        for (int i = p[now]; ~i; i = e[i].next)
            if (e[i^1].f && dist[e[i].v] == -1) {
                dist[e[i].v] = dist[now] - 1;
                q[r++] = e[i].v;
                if (e[i].v == source) return true;
            }
    }
    return false;
}

template <typename T> void checkMin(T &a, const T &b) { if (b < a) a = b; }
template <typename T> void checkMax(T &a, const T &b) { if (b > a) a = b; }

const int inf = 1000000000;

int gap[N];

bool done;


int dfs(int v, int f) {
    if (v == sink) return f;
    int tmp = 0;
    for (int i = p[v]; !done && i != -1; i = e[i].next)
        if (dist[v] + 1 == dist[e[i].v] && e[i].f) {
            int ret = dfs(e[i].v, min(f - tmp, e[i].f));
            e[i].f -= ret;
            e[i^1].f += ret;
            tmp += ret;
            if (tmp == f) return f;
        }
    if (!tmp) {
        --gap[dist[v]];
        if (gap[dist[v]] == 0) done = true;
        dist[v] = n+1;
    }
    return tmp;
}

int maxflow() {
    int tot = 0;
    while (bfs()) {
        memset(gap, 0, sizeof(gap));
        done = false;
        for (int i = 1; i <= n; ++i)
            if (dist[i] >= 0) ++gap[dist[i]];
        int ret = dfs(source, inf);
        if (!ret) break;
        tot += ret;
    }
    return tot;
}

int tot[N];

int main ( int argc, char *argv[] ) {
    while (scanf("%d%d", &n, &m) == 2) {
        init();
        memset(tot, 0, sizeof(tot));
        for (int i = 1; i <= m; ++i) {
            static int x, y, a, b;
            scanf("%d%d%d%d", &x, &y, &a, &b);
            low[i] = a;
            insert2(x, y, b - a);
            tot[y] += a;
            tot[x] -= a;
        }
        int sum = 0;
        for (int i = 1; i <= n; ++i)
            if (tot[i] > 0) sum += tot[i];
        source = n + 1, sink = n + 2;
        for (int i = 1; i <= n; ++i)
            if (tot[i] > 0) insert2(source, i, tot[i]);
            else insert2(i, sink, -tot[i]);
        n = sink;
        if (maxflow() < sum) {
            puts("NO");
            continue;
        }
        puts("YES");
        for (int i = 1; i <= m; ++i)
            printf("%d\n", low[i] + e[i*2-1].f);
    }
    return 0;
}				// ----------  end of function main  ----------
