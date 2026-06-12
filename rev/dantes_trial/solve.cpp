#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <omp.h>

using namespace std;

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

static constexpr u64 K1 = 0x00000100000001B3ULL;
static constexpr u64 K2 = 0x9E3779B185EBCA87ULL;
static constexpr u64 INV_K1 = 0xCE965057AFF6957BULL;
static constexpr u64 INV_K2 = 0x0887493432BADB37ULL;

u8 trit_lut[256];

void init_trit() {
    u8 lut[9] = {1, 0, 0, 1, 0, 2, 2, 2, 1};
    for (int i = 0; i < 256; ++i) {
        u8 out = 0, weight = 1, a = i, b = 0;
        for (int j = 0; j < 6; ++j) {
            out = (out + weight * lut[3 * (a % 3) + (b % 3)]) & 0xFF;
            weight = (weight * 3) & 0xFF;
            a /= 3; b /= 3;
        }
        trit_lut[i] = out;
    }
}

inline u64 step_fwd(u64 s, u8 idx, u8 acc) {
    u32 hlo = (u32)s, hhi = (u32)(s >> 32);
    u64 m1 = ((u64)hhi << 32 | (hlo ^ acc)) * K1;
    u64 m2 = ((m1 & 0xFFFFFFFF00000000ULL) | ((u32)m1 ^ idx)) * K1;
    u64 shifted = (u64)trit_lut[acc] << (8 * (idx & 7));
    u64 m3 = (m2 ^ shifted) * K2;
    u32 nhhi = (u32)(m3 >> 32);
    return (u64)nhhi << 32 | ((u32)m3 ^ (nhhi >> 1));
}

inline u64 step_inv(u64 ns, u8 idx, u8 acc) {
    u32 nhhi = (u32)(ns >> 32);
    u32 nhlo = (u32)ns ^ (nhhi >> 1);
    u64 m3 = (u64)nhhi << 32 | nhlo;
    u64 m2 = (m3 * INV_K2) ^ ((u64)trit_lut[acc] << (8 * (idx & 7)));
    u64 m1_xor_idx = m2 * INV_K1;
    u64 m1 = (m1_xor_idx & 0xFFFFFFFF00000000ULL) | ((u32)m1_xor_idx ^ idx);
    u64 s_xor_acc = m1 * INV_K1;
    return (s_xor_acc & 0xFFFFFFFF00000000ULL) | ((u32)s_xor_acc ^ acc);
}

inline u8 next_idx(u8 idx, u8 acc) { return (idx + 1 + (trit_lut[acc] & 1)) & 0xFF; }
inline u8 prev_idx(u8 nidx, u8 acc) { return (nidx - 1 - (trit_lut[acc] & 1)) & 0xFF; }

struct Entry {
    u64 s;
    u8 idx;
    u64 code;
    bool operator<(const Entry& o) const {
        if (s != o.s) return s < o.s;
        return idx < o.idx;
    }
};

string decode_code(u64 code, int len, const string& charset) {
    string res = "";
    for (int i = 0; i < len; ++i) {
        res += charset[code % charset.size()];
        code /= charset.size();
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    init_trit();
    string charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_!@#$";
    u64 START_S = 0xCBF29CE484222325ULL;
    u32 T_LO = 0x29b035a7, T_HI = 0xbc4fdb80;

    int L = 4;
    vector<Entry> fwd;
    cout << "[*] Building forward table (depth " << L << ")..." << endl;
    
    auto build_fwd = [&](auto self, u64 s, u8 idx, u64 code, int d) -> void {
        if (d == L) {
            fwd.push_back({s, idx, code});
            return;
        }
        for (u32 i = 0; i < charset.size(); ++i) {
            self(self, step_fwd(s, idx, charset[i]), next_idx(idx, charset[i]), code * charset.size() + i, d + 1);
        }
    };
    build_fwd(build_fwd, START_S, 0, 0, 0);
    sort(fwd.begin(), fwd.end());
    cout << "[+] Forward table size: " << fwd.size() << endl;

    for (int len = L + 1; len <= 16; ++len) {
        int R = len - L;
        cout << "[*] Checking length " << len << " (R=" << R << ")..." << endl;
        bool found = false;

        #pragma omp parallel for shared(found)
        for (int final_idx = 0; final_idx < 256; ++final_idx) {
            if (found) continue;
            u64 target = (u64)T_HI << 32 | (T_LO ^ final_idx);
            
            auto search_back = [&](auto self, u64 ns, u8 nidx, string path, int d) -> void {
                if (found) return;
                if (d == R) {
                    auto it = lower_bound(fwd.begin(), fwd.end(), Entry{ns, nidx, 0});
                    while (it != fwd.end() && it->s == ns && it->idx == nidx) {
                        #pragma omp critical
                        {
                            if (!found) {
                                cout << "[!] FOUND: " << decode_code(it->code, L, charset) << path << endl;
                                found = true;
                            }
                        }
                        ++it;
                    }
                    return;
                }
                for (u32 i = 0; i < charset.size(); ++i) {
                    u8 pidx = prev_idx(nidx, charset[i]);
                    self(self, step_inv(ns, pidx, charset[i]), pidx, string(1, charset[i]) + path, d + 1);
                }
            };
            search_back(search_back, target, (u8)final_idx, "", 0);
        }
        if (found) break;
    }

    return 0;
}

// srdnlen{W1H31l}
