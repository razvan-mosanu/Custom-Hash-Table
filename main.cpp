#include <bits/stdc++.h>
using namespace std;


template <typename T>
struct HashFunction {
    int operator()(const T& key, int N) const { return 0; }
};

template <>
struct HashFunction<int> {
    long long splitmix64(long long x) const {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    int operator()(const int& x, int N) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return (splitmix64(x + FIXED_RANDOM) % N + N) % N;
    }
};

template <typename T>
class Hash {
public:
    int n;
    vector<vector<pair<T, int>>> H;
    HashFunction<T> hasher;

    Hash(int _n = 666013) : n(_n) {
        H.resize(n);
    }


    void Insert(T x) {
        int index = hasher(x, n);
        for (auto &elem : H[index]) {
            if (elem.first == x) {
                elem.second++;
                return;
            }
        }

        H[index].push_back({x, 1});
    }

    void Delete(T x) {
        int index = hasher(x, n);
        for (size_t i = 0; i < H[index].size(); i++) {
            if (H[index][i].first == x) {
                H[index][i].second--; // Scad frecventa

                // Daca frecventa a ajuns la 0, stergem fizic elementul
                if (H[index][i].second == 0) {
                    // Swap cu ultimul element si Pop Back (O(1))
                    H[index][i] = H[index].back();
                    H[index].pop_back();
                }
                return;
            }
        }
    }

    int Count(T x) {
        int index = hasher(x, n);
        for (const auto &elem : H[index]) {
            if (elem.first == x) return elem.second;
        }
        return 0;
    }

    bool Find(T x) {
        return Count(x) > 0;
    }
};

int main()
{
    return 0;
}
