# 前言

编译选项：

```cpp
-std=gnu++17 -O2
```

## 注意事项

- 现较完善模板已有：快速 IO、并查集、ST 表、树状数组、网络最大流、扫描线、后缀数组、数论相关等内容；
- 区间数据结构的实现中，查询区间为闭区间，而不是各大主流模板库的半闭半开区间；
- 本模板库在部分问题上参考了 [AtCoder Library](https://github.com/atcoder/ac-library) 的处理方式。

## 更新

- Upd on $2024.10.13$：添加了“命题相关模板”一栏。
- Upd on $2025.8.25$：对大部分模板进行了重构。

# 第一部分 较完善模板

## 快速 IO（Fast IO）

见目录下 `fastio.hpp`。

#### 功能介绍

- `T read()`：从标准输入读取一个整数；
- `T write()`：向标准输出写入一个整数。

#### 示例代码

[P9515「JOC-1A」签到题 by FFTotoro](https://www.luogu.com.cn/record/121487446)

## 并查集（DSU）

见目录下 `dsu.hpp`。

#### 功能介绍

UPD：增加了带权功能（即维护连通块大小）。

- `dsu d(int n)`：创建一个大小为 $n(1\le n\le 10^8)$（如果不添加 `(int n)` 则为默认大小 $2\times 10^5$）的并查集，时间复杂度 $O(n)$（下文 $x,y$ 的范围均为 $0\le x,y<n$）；
- `int d.leader(int x)`：返回 $x$ 的祖先，时间复杂度 $O(\alpha(n))$；
- `int d.size(int x)`：返回 $x$ 所在连通块（集合）的大小，时间复杂度 $O(\alpha(n))$；
- `void d.merge(int x,int y)`：合并 $x$ 和 $y$ 所在的连通块（集合），时间复杂度 $O(\alpha(n))$；
- `bool d.same(int x,int y)`：返回 $x$ 和 $y$ 是否在同一个连通块（集合）内，时间复杂度 $O(\alpha(n))$。

#### 示例代码

[P9488 ZHY 的生成树 by FFTotoro](https://www.luogu.com.cn/record/118455144)

## ST 表（Sparse Table）

见目录下 `sparse_table.hpp`。

#### 功能介绍

- `sparse_table<T,op> s(vector<T> a)`：对于存储 `T` 类型的 $a$ 数组（`std::vector`）创建一个 ST 表，`op` 为你需要维护的操作（特别地，它需要满足**消去律** $\mathrm{op}(x,x)=x$；例如，$\gcd$、$\max$、$\mathrm{and}$ 等都满足消去律），时间复杂度 $O(n\log n)$，这里 $n(1\le n\le 10^7)$ 为 $a$ 的大小；
- `T s.query(int l,int r)`：返回 $\mathrm{op}_{i=l}^r a_i$ 的值，时间复杂度 $O(1)$。

#### 示例代码

[P2412 查单词 by FFTotoro](https://www.luogu.com.cn/record/127849345)

## 树状数组（Fenwick Tree）

见目录下 `fenwick_tree.hpp`。

#### 功能介绍

- `fenwick_tree<T> t(int n)`：创建一个大小为 $n(1\le n\le 10^8)$、存储类型为 `T` 的树状数组，时间复杂度 $O(n)$；
- `void t.add(int p,T d)`：向树状数组 $t$ 中的第 $p(0\le p<n)$ 个元素加上 $d$，时间复杂度 $O(\log n)$；
- `T t.sum(int l,int r)`：返回 $\sum\limits_{i=l}^r a_i(0\le l\le r<n)$，时间复杂度 $O(\log n)$。

#### 示例代码

[P3970 \[TJOI2014\] 上升子序列 by FFTotoro](https://www.luogu.com.cn/record/145270046)

## 网络最大流（Max Flow）

见目录下 `maxflow.hpp`。

#### 功能介绍

- `mf_graph<C> g(int n)`：创建一个流量类型为 `C` 的、具有 $n$ 个结点的网络流图，时间复杂度 $O(n)$；
- `void g.add_edge(int u,int v,C w)`：加入一条 $u\to v$ 的、容量为 $w$ 的边，时间复杂度 $O(1)$；
- `C g.flow(int s,int t,C l)`：求源点为 $s$、汇点为 $t$ 的网络最大流，流量上限为 $l$（默认为类型 `C` 的最大值），时间复杂度 $O(|V|^2|E|)$；
- `edge g.get_edge(int x)`：获取加入的第 $x$ 条边的信息（流量），时间复杂度 $O(1)$；
- `vector<edge> g.edges()`：获取所有边的信息（流量），时间复杂度 $O(|E|)$。

#### 示例代码

[B3607 \[图论与代数结构 502\] 网络流_2 by FFTotoro](https://www.luogu.com.cn/record/201025964)

## 矩形面积并（Atlantis）

见目录下 `atlantis.hpp`。

#### 功能介绍

- `long long atlantis(vector<tuple<long long,long long,long long,long long> > a)`：求若干个四边平行于坐标轴的矩形的面积并。

#### 示例代码

[P10096 [ROIR 2023 Day 1] 扫地机器人 by FFTotoro](https://www.luogu.com.cn/record/143880317)

## 后缀数组（Suffix Array）

见目录下 `suffix_array.hpp`。

#### 功能介绍

- `vector<int> suffix_array<T>(vector<T> s)`：求出一个存储类型为 `T` 的数组 $s$ 的后缀数组，时间复杂度 $O(n\log n)$；
- `vector<int> suffix_array(string s)`：求出一个字符串 $s$ 的后缀数组，时间复杂度 $O(n\log n)$；
- `vector<int> lcp_array<T>(vector<T> s,vector<int> sa)`：求出一个存储类型为 `T`、后缀数组为 $\text{sa}$ 的数组 $s$ 的 $\text{lcp}$ 数组（又称 $\text{height}$ 数组），时间复杂度 $O(n)$；
- `vector<int> lcp_array(string s,vector<int> sa)`：求出一个后缀数组为 $\text{sa}$ 的字符串 $s$ 的 $\text{lcp}$ 数组，时间复杂度 $O(n)$。

#### 示例代码

[P10469 后缀数组 by FFTotoro](https://www.luogu.com.cn/record/201120187)

## 数论（Number Theory）

见目录下 `number_theory.hpp`。

#### 功能介绍

- `vector<int> get_primes(int n)`：查找 $[2,n](2\le n\le 10^8)$ 以内的所有质数，并返回包含它们的一个数组（`std::vector`），时间复杂度 $O(n)$；
- `long long safe_mulll(long long a,long long b,long long M)`：返回 $a\times b\bmod M(0\le a,b\le 10^{18},1\le M\le 10^{18})$ 的值，时间复杂度 $O(\log b)$；
- `int pow_mod(int a,int b,int M)` / `long long pow_modll(long long a,long long n,long long M)`：返回 $a^b\bmod M(0\le a,b\le 10^{9},1\le M\le 10^{9})$ 的值，时间复杂度 $O(\log b)$；
- `int inv_p(int x,int M)` / `long long inv_pll(long long x,long long M)`：返回 $x(1\le x<mod)$ 在模 $M(1\le M\le 10^9)$（$M$ 是质数）意义下的逆元，时间复杂度 $O(\log M)$；
- `pair<int,int> exgcd(int a,int b)` / `pair<long long,long long> exgcdll(long long a,long long b)`：返回关于 $x,y$ 的不定方程 $ax+by=1$ 的解 $(x,y)$，时间复杂度 $O(\log\max(a,b))$；
- `int inv_cp(int x,int M)` / `long long inv_cpll(long long x,long long M)`：返回 $x(1\le x<M)$ 在模 $M(1\le M\le 10^9)$（$M$ 不一定是质数）意义下的逆元，如果 $x$ 没有逆元返回 $-1$，时间复杂度 $O(\log M)$；
- `long long crt(vector<pair<long long,long long> > a)` / `long long crt_mod(vector<pair<long long,long long> > a,int M)`：返回满足 $\forall1\le i,j\le n\land i\ne j,m_i\perp m_j$ 的方程组 $x\equiv r_i\pmod {m_i}$ 的最小非负整数解 $x$，时间复杂度 $O(n\log\max\{m_i\})$。可选择是否将 $x$ 对某个数 $M$ 取模；
- `long double lagrange(vector<pair<long long,long long> > a,long long k)`：通过其在若干个点上的值确定一个多项式 $f(x)$ 并求出 $f(k)$，时间复杂度 $O(n^2)$，这里 $n$ 是 $a$ 的大小，即给出的点的个数；
- `int lagrange_mod(vector<pair<int,int> > a,int k,int M)`：同上，求出 $f(k)\bmod M$，时间复杂度 $O(n^2)$。
- `int discrete_logarithm(int x,int y,int M)`：返回最小的非负整数 $k$ 满足 $x^k\equiv y\pmod M(1\le M\le 10^9,\ 0\le x,y<M)$，如果不存在这样的 $k$，返回 $-1$，时间复杂度 $O(\sqrt{M})$。

#### 示例代码

[P2480 古代猪文 by FFTotoro](https://www.luogu.com.cn/record/123956285)

# 第二部分 普通模板

**警告：该部分模板未经过大量的实践测试，可能存在一定错误。请谨慎使用。**

## 杂项（Misc）

### 离散化（Discretization）

见目录下 `misc/discretization.hpp`。

## 线性代数（Linear Algebra）

### 矩阵（Matrix）

见目录下 `linear_algebra/matrix.hpp`。

包含：矩阵转置（Transpose）、矩阵的秩（Rank）、行列式求值（Determinant）、线性方程组（System of Linear Equations）和普法夫型（Pfaffian）。

### 异或线性基（XOR Basis）

见目录下 `linear_algebra/xor_basis.hpp`。

## 图论（Graph Theory）

### 2-满足性问题（2-SAT）

见目录下 `graph/twosat.hpp`。

**注意：该模板输入为 $1$-indexed（按照 CNF 格式输入），返回值为 $0$-indexed。**

### 一般图最大匹配（Matching on General Graph）

见目录下 `graph/general_matching.hpp`。

### 二分图边染色（Edge Coloring of Bipartite Graph）

见目录下 `graph/bipar_edge_coloring.hpp`。

### 最小费用最大流（Min Cost Flow）

见目录下 `graph/mincostflow.hpp`。

### 无向图带权三元环枚举（Enumerate Triangles）

见目录下 `graph/enumerate_triangles.hpp`。

## 卷积

### 普通卷积（Convolution）

见目录下 `convolution/convolution.hpp`。

### 普通卷积取模（Convolution Mod $998244353$）

见目录下 `convolution/convolution_mod.hpp`。

**注意：使用 `pow` 函数时需要保证 $x_0=1$。**

### 按位与 / 或 / 异或卷积取模（Bitwise AND / OR / XOR Convolution Mod $998244353$）

见目录下 `convolution/bitwise_convolution.hpp`。

### GCD / LCM 卷积取模（GCD / LCM Convolution Mod $998244353$）

见目录下 `convolution/gcd_lcm_convolution.hpp`。

# 第三部分 命题相关模板

### 简单子任务配置生成器

见目录下 `gen/subtask_config.cpp`。
