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

__attribute__((used)) static void HE4(uint8_t* dst, const uint8_t* top) {    // horizontal
  const int X = top[-1];
  const int I = top[-2];
  const int J = top[-3];
  const int K = top[-4];
  const int L = top[-5];
  WebPUint32ToMem(dst + 0 * BPS, 0x01010101U * AVG3(X, I, J));
  WebPUint32ToMem(dst + 1 * BPS, 0x01010101U * AVG3(I, J, K));
  WebPUint32ToMem(dst + 2 * BPS, 0x01010101U * AVG3(J, K, L));
  WebPUint32ToMem(dst + 3 * BPS, 0x01010101U * AVG3(K, L, L));
}