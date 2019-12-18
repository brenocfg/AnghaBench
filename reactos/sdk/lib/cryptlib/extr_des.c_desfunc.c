#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ulong64 ;
typedef  int ulong32 ;

/* Variables and functions */
 int ROR (int,int) ; 
 int* SP1 ; 
 int* SP2 ; 
 int* SP3 ; 
 int* SP4 ; 
 int* SP5 ; 
 int* SP6 ; 
 int* SP7 ; 
 int* SP8 ; 
 size_t byte (int,int) ; 
 int** des_fp ; 
 int** des_ip ; 

__attribute__((used)) static void desfunc(ulong32 *block, const ulong32 *keys)
{
    ulong64 tmp;
    ulong32 work, right, leftt;
    int cur_round;

    leftt = block[0];
    right = block[1];

    tmp = des_ip[0][byte(leftt, 0)] ^
          des_ip[1][byte(leftt, 1)] ^
          des_ip[2][byte(leftt, 2)] ^
          des_ip[3][byte(leftt, 3)] ^
          des_ip[4][byte(right, 0)] ^
          des_ip[5][byte(right, 1)] ^
          des_ip[6][byte(right, 2)] ^
          des_ip[7][byte(right, 3)];
    leftt = (ulong32)(tmp >> 32);
    right = (ulong32)(tmp & 0xFFFFFFFFUL);

    for (cur_round = 0; cur_round < 8; cur_round++) {
        work  = ROR(right, 4) ^ *keys++;
        leftt ^= SP7[work        & 0x3fL]
              ^ SP5[(work >>  8) & 0x3fL]
              ^ SP3[(work >> 16) & 0x3fL]
              ^ SP1[(work >> 24) & 0x3fL];
        work  = right ^ *keys++;
        leftt ^= SP8[ work        & 0x3fL]
              ^  SP6[(work >>  8) & 0x3fL]
              ^  SP4[(work >> 16) & 0x3fL]
              ^  SP2[(work >> 24) & 0x3fL];

        work = ROR(leftt, 4) ^ *keys++;
        right ^= SP7[ work        & 0x3fL]
              ^  SP5[(work >>  8) & 0x3fL]
              ^  SP3[(work >> 16) & 0x3fL]
              ^  SP1[(work >> 24) & 0x3fL];
        work  = leftt ^ *keys++;
        right ^= SP8[ work        & 0x3fL]
              ^  SP6[(work >>  8) & 0x3fL]
              ^  SP4[(work >> 16) & 0x3fL]
              ^  SP2[(work >> 24) & 0x3fL];
    }

    tmp = des_fp[0][byte(leftt, 0)] ^
          des_fp[1][byte(leftt, 1)] ^
          des_fp[2][byte(leftt, 2)] ^
          des_fp[3][byte(leftt, 3)] ^
          des_fp[4][byte(right, 0)] ^
          des_fp[5][byte(right, 1)] ^
          des_fp[6][byte(right, 2)] ^
          des_fp[7][byte(right, 3)];
    leftt = (ulong32)(tmp >> 32);
    right = (ulong32)(tmp & 0xFFFFFFFFUL);
    
    block[0] = right;
    block[1] = leftt;
}