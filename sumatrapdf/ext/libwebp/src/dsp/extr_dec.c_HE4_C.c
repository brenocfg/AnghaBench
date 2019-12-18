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
typedef  int uint8_t ;

/* Variables and functions */
 int AVG3 (int const,int const,int const) ; 
 int BPS ; 
 int /*<<< orphan*/  WebPUint32ToMem (int*,int) ; 

__attribute__((used)) static void HE4_C(uint8_t* dst) {    // horizontal
  const int A = dst[-1 - BPS];
  const int B = dst[-1];
  const int C = dst[-1 + BPS];
  const int D = dst[-1 + 2 * BPS];
  const int E = dst[-1 + 3 * BPS];
  WebPUint32ToMem(dst + 0 * BPS, 0x01010101U * AVG3(A, B, C));
  WebPUint32ToMem(dst + 1 * BPS, 0x01010101U * AVG3(B, C, D));
  WebPUint32ToMem(dst + 2 * BPS, 0x01010101U * AVG3(C, D, E));
  WebPUint32ToMem(dst + 3 * BPS, 0x01010101U * AVG3(D, E, E));
}