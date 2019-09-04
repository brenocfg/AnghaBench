#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong32 ;
struct TYPE_3__ {int Nr; int* dK; } ;
typedef  TYPE_1__ aes_key ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD32H (int,unsigned char const*) ; 
 int /*<<< orphan*/  STORE32H (int,unsigned char*) ; 
 int Td0 (size_t) ; 
 int Td1 (size_t) ; 
 int Td2 (size_t) ; 
 int Td3 (size_t) ; 
 int* Td4 ; 
 size_t byte (int,int) ; 

void aes_ecb_decrypt(const unsigned char *ct, unsigned char *pt, aes_key *skey)
{
    ulong32 s0, s1, s2, s3, t0, t1, t2, t3, *rk;
    int Nr, r;

    Nr = skey->Nr;
    rk = skey->dK;

    LOAD32H(s0, ct      ); s0 ^= rk[0];
    LOAD32H(s1, ct  +  4); s1 ^= rk[1];
    LOAD32H(s2, ct  +  8); s2 ^= rk[2];
    LOAD32H(s3, ct  + 12); s3 ^= rk[3];

    r = Nr >> 1;
    for (;;) {

        t0 =
            Td0(byte(s0, 3)) ^
            Td1(byte(s3, 2)) ^
            Td2(byte(s2, 1)) ^
            Td3(byte(s1, 0)) ^
            rk[4];
        t1 =
            Td0(byte(s1, 3)) ^
            Td1(byte(s0, 2)) ^
            Td2(byte(s3, 1)) ^
            Td3(byte(s2, 0)) ^
            rk[5];
        t2 =
            Td0(byte(s2, 3)) ^
            Td1(byte(s1, 2)) ^
            Td2(byte(s0, 1)) ^
            Td3(byte(s3, 0)) ^
            rk[6];
        t3 =
            Td0(byte(s3, 3)) ^
            Td1(byte(s2, 2)) ^
            Td2(byte(s1, 1)) ^
            Td3(byte(s0, 0)) ^
            rk[7];

        rk += 8;
        if (--r == 0) {
            break;
        }


        s0 =
            Td0(byte(t0, 3)) ^
            Td1(byte(t3, 2)) ^
            Td2(byte(t2, 1)) ^
            Td3(byte(t1, 0)) ^
            rk[0];
        s1 =
            Td0(byte(t1, 3)) ^
            Td1(byte(t0, 2)) ^
            Td2(byte(t3, 1)) ^
            Td3(byte(t2, 0)) ^
            rk[1];
        s2 =
            Td0(byte(t2, 3)) ^
            Td1(byte(t1, 2)) ^
            Td2(byte(t0, 1)) ^
            Td3(byte(t3, 0)) ^
            rk[2];
        s3 =
            Td0(byte(t3, 3)) ^
            Td1(byte(t2, 2)) ^
            Td2(byte(t1, 1)) ^
            Td3(byte(t0, 0)) ^
            rk[3];
    }

    s0 =
        (Td4[byte(t0, 3)] & 0xff000000) ^
        (Td4[byte(t3, 2)] & 0x00ff0000) ^
        (Td4[byte(t2, 1)] & 0x0000ff00) ^
        (Td4[byte(t1, 0)] & 0x000000ff) ^
        rk[0];
    STORE32H(s0, pt);
    s1 =
        (Td4[byte(t1, 3)] & 0xff000000) ^
        (Td4[byte(t0, 2)] & 0x00ff0000) ^
        (Td4[byte(t3, 1)] & 0x0000ff00) ^
        (Td4[byte(t2, 0)] & 0x000000ff) ^
        rk[1];
    STORE32H(s1, pt+4);
    s2 =
        (Td4[byte(t2, 3)] & 0xff000000) ^
        (Td4[byte(t1, 2)] & 0x00ff0000) ^
        (Td4[byte(t0, 1)] & 0x0000ff00) ^
        (Td4[byte(t3, 0)] & 0x000000ff) ^
        rk[2];
    STORE32H(s2, pt+8);
    s3 =
        (Td4[byte(t3, 3)] & 0xff000000) ^
        (Td4[byte(t2, 2)] & 0x00ff0000) ^
        (Td4[byte(t1, 1)] & 0x0000ff00) ^
        (Td4[byte(t0, 0)] & 0x000000ff) ^
        rk[3];
    STORE32H(s3, pt+12);
}