extern "C"
{
#include "testbitfields_importc.c"
}

#include <stdio.h>
#include <string.h>

template<typename T>
size_t getStructSize();
template<typename T>
size_t getStructAlign();
template<typename T>
void resetBitfield(T &data, const char *member);

#define BEGIN_STRUCT(S) \
    template<> \
    size_t getStructSize<S>() \
    { \
        return sizeof(S); \
    } \
    template<> \
    size_t getStructAlign<S>() \
    { \
        return alignof(S); \
    } \
    template<> \
    void resetBitfield<S>(S &data, const char *member) \
    {

#define FIELD(name) if (strcmp(member, #name) == 0) data.name = 0;
#define END_STRUCT }

BEGIN_STRUCT(T0) FIELD(x) END_STRUCT
BEGIN_STRUCT(T1) FIELD(x) END_STRUCT
BEGIN_STRUCT(T2) FIELD(x) END_STRUCT
BEGIN_STRUCT(T3) FIELD(a) FIELD(b) FIELD(c) FIELD(d) FIELD(x) END_STRUCT
BEGIN_STRUCT(T4) FIELD(a) FIELD(b) FIELD(c) FIELD(d) FIELD(e) FIELD(f) FIELD(g) FIELD(h) FIELD(x) END_STRUCT
BEGIN_STRUCT(T5) FIELD(a) FIELD(b) FIELD(c) FIELD(d) FIELD(e) FIELD(f) FIELD(g) FIELD(x) END_STRUCT
BEGIN_STRUCT(S1) FIELD(f) END_STRUCT
BEGIN_STRUCT(S2) FIELD(x) FIELD(y) END_STRUCT
BEGIN_STRUCT(S3) FIELD(c) FIELD(x) FIELD(y) END_STRUCT
BEGIN_STRUCT(S4) FIELD(x) FIELD(y) END_STRUCT
BEGIN_STRUCT(S5) FIELD(x) FIELD(y) END_STRUCT
BEGIN_STRUCT(S6) FIELD(x) FIELD(y) END_STRUCT
BEGIN_STRUCT(S7) FIELD(x) FIELD(y) FIELD(z) END_STRUCT
BEGIN_STRUCT(S8) FIELD(a) FIELD(b) FIELD(c) END_STRUCT
BEGIN_STRUCT(S8A) FIELD(b) FIELD(c) END_STRUCT
BEGIN_STRUCT(S8B) FIELD(a) FIELD(b) FIELD(c) END_STRUCT
BEGIN_STRUCT(S8C) FIELD(a) FIELD(b) END_STRUCT
BEGIN_STRUCT(S9) FIELD(a) FIELD(b) FIELD(c) END_STRUCT
//BEGIN_STRUCT(S10) END_STRUCT
//BEGIN_STRUCT(S11) END_STRUCT
BEGIN_STRUCT(S12) FIELD(x) END_STRUCT
BEGIN_STRUCT(S13) FIELD(x) FIELD(x1) FIELD(x2) FIELD(x3) FIELD(x4) FIELD(w) END_STRUCT
BEGIN_STRUCT(S14) FIELD(a) FIELD(b) FIELD(c) END_STRUCT
BEGIN_STRUCT(S15) FIELD(a) FIELD(b) FIELD(c) END_STRUCT
BEGIN_STRUCT(S16) END_STRUCT
BEGIN_STRUCT(S17) FIELD(a) END_STRUCT
BEGIN_STRUCT(S18) FIELD(a) FIELD(b) END_STRUCT
BEGIN_STRUCT(A0) FIELD(a) FIELD(b) FIELD(c) END_STRUCT
BEGIN_STRUCT(A1) FIELD(a) FIELD(b) FIELD(c) END_STRUCT
BEGIN_STRUCT(A2) FIELD(a) FIELD(b) FIELD(c) FIELD(d)
 FIELD(e) END_STRUCT
BEGIN_STRUCT(A3) FIELD(a) FIELD(b) FIELD(c) FIELD(d)
 FIELD(e) END_STRUCT
BEGIN_STRUCT(A4) FIELD(a) FIELD(b)
 FIELD(c) END_STRUCT
BEGIN_STRUCT(A5) FIELD(a) FIELD(b) END_STRUCT
BEGIN_STRUCT(A6) FIELD(a) FIELD(b) END_STRUCT
BEGIN_STRUCT(A7) FIELD(a) FIELD(b) FIELD(c)
 FIELD(d) END_STRUCT
BEGIN_STRUCT(A8) FIELD(a) FIELD(b)
 FIELD(c) END_STRUCT
BEGIN_STRUCT(A9) FIELD(a) FIELD(b)
 FIELD(c) FIELD(d)
 FIELD(e) FIELD(f) END_STRUCT
BEGIN_STRUCT(A10) FIELD(a) FIELD(b) END_STRUCT
BEGIN_STRUCT(A11) FIELD(a) FIELD(b) FIELD(c) FIELD(d)
             END_STRUCT
BEGIN_STRUCT(Issue24592a) FIELD(a) FIELD(b) FIELD(c) END_STRUCT
BEGIN_STRUCT(Issue24592b) FIELD(x) FIELD(a) FIELD(b) FIELD(c) END_STRUCT
BEGIN_STRUCT(Issue24592c) FIELD(a) FIELD(b) FIELD(c) FIELD(d) FIELD(e) FIELD(f) END_STRUCT
BEGIN_STRUCT(Issue24592d) FIELD(a) FIELD(b) FIELD(c) FIELD(d) FIELD(e) FIELD(f) END_STRUCT

BEGIN_STRUCT(Test48a) FIELD(a) FIELD(b) END_STRUCT
BEGIN_STRUCT(Test48b) FIELD(a) FIELD(b) END_STRUCT

BEGIN_STRUCT(Random1)
FIELD(x1)
FIELD(x2)
FIELD(x3)
FIELD(x4)
FIELD(x5)
FIELD(x6)
FIELD(x7)
FIELD(x8)
FIELD(x9)
FIELD(x10)
FIELD(x11)
FIELD(x12)
FIELD(x13)
FIELD(x14)
FIELD(x15)
FIELD(x16)
FIELD(x17)
FIELD(x18)
FIELD(x19)
FIELD(x20)
FIELD(x21)
FIELD(x22)
FIELD(x23)
FIELD(x24)
FIELD(x25)
FIELD(x26)
FIELD(x27)
FIELD(x28)
FIELD(x29)
FIELD(x30)
FIELD(x31)
FIELD(x32)
END_STRUCT

BEGIN_STRUCT(Random2)
FIELD(x1)
FIELD(x2)
FIELD(x3)
FIELD(x4)
FIELD(x5)
FIELD(x6)
FIELD(x7)
FIELD(x8)
FIELD(x9)
FIELD(x10)
FIELD(x11)
FIELD(x12)
FIELD(x13)
FIELD(x14)
FIELD(x15)
FIELD(x16)
FIELD(x17)
FIELD(x18)
FIELD(x19)
FIELD(x20)
FIELD(x21)
FIELD(x22)
FIELD(x23)
FIELD(x24)
FIELD(x25)
FIELD(x26)
FIELD(x27)
FIELD(x28)
FIELD(x29)
FIELD(x30)
FIELD(x31)
FIELD(x32)
END_STRUCT

BEGIN_STRUCT(Random3)
FIELD(x1)
FIELD(x2)
FIELD(x3)
FIELD(x4)
FIELD(x5)
FIELD(x6)
FIELD(x7)
FIELD(x8)
FIELD(x9)
FIELD(x10)
FIELD(x11)
FIELD(x12)
FIELD(x13)
FIELD(x14)
FIELD(x15)
FIELD(x16)
FIELD(x17)
FIELD(x18)
FIELD(x19)
FIELD(x20)
FIELD(x21)
FIELD(x22)
FIELD(x23)
FIELD(x24)
FIELD(x25)
FIELD(x26)
FIELD(x27)
FIELD(x28)
FIELD(x29)
FIELD(x30)
FIELD(x31)
FIELD(x32)
END_STRUCT

BEGIN_STRUCT(Random4)
FIELD(x1)
FIELD(x2)
FIELD(x3)
FIELD(x4)
FIELD(x5)
FIELD(x6)
FIELD(x7)
FIELD(x8)
FIELD(x9)
FIELD(x10)
FIELD(x11)
FIELD(x12)
FIELD(x13)
FIELD(x14)
FIELD(x15)
FIELD(x16)
FIELD(x17)
FIELD(x18)
FIELD(x19)
FIELD(x20)
FIELD(x21)
FIELD(x22)
FIELD(x23)
FIELD(x24)
FIELD(x25)
FIELD(x26)
FIELD(x27)
FIELD(x28)
FIELD(x29)
FIELD(x30)
FIELD(x31)
FIELD(x32)
END_STRUCT

BEGIN_STRUCT(Random5)
FIELD(x1)
FIELD(x2)
FIELD(x3)
FIELD(x4)
FIELD(x5)
FIELD(x6)
FIELD(x7)
FIELD(x8)
FIELD(x9)
FIELD(x10)
FIELD(x11)
FIELD(x12)
FIELD(x13)
FIELD(x14)
FIELD(x15)
FIELD(x16)
FIELD(x17)
FIELD(x18)
FIELD(x19)
FIELD(x20)
FIELD(x21)
FIELD(x22)
FIELD(x23)
FIELD(x24)
FIELD(x25)
FIELD(x26)
FIELD(x27)
FIELD(x28)
FIELD(x29)
FIELD(x30)
FIELD(x31)
FIELD(x32)
END_STRUCT

BEGIN_STRUCT(Random6)
FIELD(x1)
FIELD(x2)
FIELD(x3)
FIELD(x4)
FIELD(x5)
FIELD(x6)
FIELD(x7)
FIELD(x8)
FIELD(x9)
FIELD(x10)
FIELD(x11)
FIELD(x12)
FIELD(x13)
FIELD(x14)
FIELD(x15)
FIELD(x16)
FIELD(x17)
FIELD(x18)
FIELD(x19)
FIELD(x20)
FIELD(x21)
FIELD(x22)
FIELD(x23)
FIELD(x24)
FIELD(x25)
FIELD(x26)
FIELD(x27)
FIELD(x28)
FIELD(x29)
FIELD(x30)
FIELD(x31)
FIELD(x32)
END_STRUCT

BEGIN_STRUCT(Random7)
FIELD(x1)
FIELD(x2)
FIELD(x3)
FIELD(x4)
FIELD(x5)
FIELD(x6)
FIELD(x7)
FIELD(x8)
FIELD(x9)
FIELD(x10)
FIELD(x11)
FIELD(x12)
FIELD(x13)
FIELD(x14)
FIELD(x15)
FIELD(x16)
FIELD(x17)
FIELD(x18)
FIELD(x19)
FIELD(x20)
FIELD(x21)
FIELD(x22)
FIELD(x23)
FIELD(x24)
FIELD(x25)
FIELD(x26)
FIELD(x27)
FIELD(x28)
FIELD(x29)
FIELD(x30)
FIELD(x31)
FIELD(x32)
END_STRUCT

BEGIN_STRUCT(Random8)
FIELD(x1)
FIELD(x2)
FIELD(x3)
FIELD(x4)
FIELD(x5)
FIELD(x6)
FIELD(x7)
FIELD(x8)
FIELD(x9)
FIELD(x10)
FIELD(x11)
FIELD(x12)
FIELD(x13)
FIELD(x14)
FIELD(x15)
FIELD(x16)
FIELD(x17)
FIELD(x18)
FIELD(x19)
FIELD(x20)
FIELD(x21)
FIELD(x22)
FIELD(x23)
FIELD(x24)
FIELD(x25)
FIELD(x26)
FIELD(x27)
FIELD(x28)
FIELD(x29)
FIELD(x30)
FIELD(x31)
FIELD(x32)
END_STRUCT

BEGIN_STRUCT(Random9)
FIELD(x1)
FIELD(x2)
FIELD(x3)
FIELD(x4)
FIELD(x5)
FIELD(x6)
FIELD(x7)
FIELD(x8)
FIELD(x9)
FIELD(x10)
FIELD(x11)
FIELD(x12)
FIELD(x13)
FIELD(x14)
FIELD(x15)
FIELD(x16)
FIELD(x17)
FIELD(x18)
FIELD(x19)
FIELD(x20)
FIELD(x21)
FIELD(x22)
FIELD(x23)
FIELD(x24)
FIELD(x25)
FIELD(x26)
FIELD(x27)
FIELD(x28)
FIELD(x29)
FIELD(x30)
FIELD(x31)
FIELD(x32)
END_STRUCT
