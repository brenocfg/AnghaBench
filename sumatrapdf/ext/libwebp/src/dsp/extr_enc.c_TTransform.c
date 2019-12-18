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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPS ; 
 int const abs (int const) ; 

__attribute__((used)) static int TTransform(const uint8_t* in, const uint16_t* w) {
  int sum = 0;
  int tmp[16];
  int i;
  // horizontal pass
  for (i = 0; i < 4; ++i, in += BPS) {
    const int a0 = in[0] + in[2];
    const int a1 = in[1] + in[3];
    const int a2 = in[1] - in[3];
    const int a3 = in[0] - in[2];
    tmp[0 + i * 4] = a0 + a1;
    tmp[1 + i * 4] = a3 + a2;
    tmp[2 + i * 4] = a3 - a2;
    tmp[3 + i * 4] = a0 - a1;
  }
  // vertical pass
  for (i = 0; i < 4; ++i, ++w) {
    const int a0 = tmp[0 + i] + tmp[8 + i];
    const int a1 = tmp[4 + i] + tmp[12+ i];
    const int a2 = tmp[4 + i] - tmp[12+ i];
    const int a3 = tmp[0 + i] - tmp[8 + i];
    const int b0 = a0 + a1;
    const int b1 = a3 + a2;
    const int b2 = a3 - a2;
    const int b3 = a0 - a1;

    sum += w[ 0] * abs(b0);
    sum += w[ 4] * abs(b1);
    sum += w[ 8] * abs(b2);
    sum += w[12] * abs(b3);
  }
  return sum;
}