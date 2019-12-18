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

/* Variables and functions */

__attribute__((used)) static unsigned int checksum(const char *zIn, size_t N){
  const unsigned char *z = (const unsigned char *)zIn;
  unsigned sum0 = 0;
  unsigned sum1 = 0;
  unsigned sum2 = 0;
  unsigned sum3 = 0;
  while(N >= 16){
    sum0 += ((unsigned)z[0] + z[4] + z[8] + z[12]);
    sum1 += ((unsigned)z[1] + z[5] + z[9] + z[13]);
    sum2 += ((unsigned)z[2] + z[6] + z[10]+ z[14]);
    sum3 += ((unsigned)z[3] + z[7] + z[11]+ z[15]);
    z += 16;
    N -= 16;
  }
  while(N >= 4){
    sum0 += z[0];
    sum1 += z[1];
    sum2 += z[2];
    sum3 += z[3];
    z += 4;
    N -= 4;
  }
  sum3 += (sum2 << 8) + (sum1 << 16) + (sum0 << 24);
  switch(N){
    case 3:   sum3 += (z[2] << 8);
    case 2:   sum3 += (z[1] << 16);
    case 1:   sum3 += (z[0] << 24);
    default:  ;
  }
  return sum3;
}