from z3 import *


n = 34
f = [BitVec(f'f{i}', 8) for i in range(n)]

s = Solver()

s.add(f[0] == ord('s'))
s.add(f[1] == ord('r'))
s.add(f[2] == ord('d'))
s.add(f[3] == ord('n'))
s.add(f[4] == ord('l'))
s.add(f[5] == ord('e'))
s.add(f[6] == ord('n'))
s.add(f[7] == ord('{'))
s.add(f[33] == ord('}'))

s.add((f[33] + 3) ^ (f[21] - 2) == 234)

s.add(f[8] == ord('r'))

s.add((f[12] - f[23]) ^ f[18] == 119)

s.add(((f[20] >> 2) ^ f[15]) + f[10] == 190)

s.add((f[11] - f[17]) ^ f[29] == 88)

s.add(((f[7] >> 2) ^ f[16]) + f[28] == 222)

s.add(f[13] + f[14] == 130)

s.add(f[9] - ((f[9] / 5) * 5) == 1) # f[9] % 5 == 1

# s.add(f[f[22] - 48] == 114)
s.add(Or([f[22] == ord('1'), f[22] == ord('8')]))

s.add(f[22] + f[24] == 100)

s.add((f[25] + (f[26] * 2)) - (f[27] * 3) == 118)

s.add(f[30] + f[31] + f[32] == 217)



s.add(f[27] < ord('a'))
for i in range(8, 33):
    s.add(f[i] >= 0x30, f[i] <= 0x7a)


if s.check() == sat:
    m = s.model()
    flag_bytes = [m.evaluate(f[i]).as_long() for i in range(n)]
    flag = ''.join(chr(b) for b in flag_bytes)
    print("Flag:", flag)
else:
    print("No solution found")

# srdnlen{r3v_c4N_l0ok_l1K3_mAlw4r3}
