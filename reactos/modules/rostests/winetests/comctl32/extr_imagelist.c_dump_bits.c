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
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void dump_bits(const BYTE *p, const BYTE *q, int size)
{
  int i, j;

  size /= 8;

  for (i = 0; i < size * 2; i++)
  {
      printf("|");
      for (j = 0; j < size; j++)
          printf("%c%c", p[j] & 0xf0 ? 'X' : ' ', p[j] & 0xf ? 'X' : ' ');
      printf(" -- ");
      for (j = 0; j < size; j++)
          printf("%c%c", q[j] & 0xf0 ? 'X' : ' ', q[j] & 0xf ? 'X' : ' ');
      printf("|\n");
      p += size * 4;
      q += size * 4;
  }
  printf("\n");
}