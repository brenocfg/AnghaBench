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
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t stbds_hash_bytes (unsigned char*,int,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
  unsigned char mem[64];
  int i,j;
  for (i=0; i < 64; ++i) mem[i] = i;
  for (i=0; i < 64; ++i) {
    size_t hash = stbds_hash_bytes(mem, i, 0);
    printf("  { ");
    for (j=0; j < 8; ++j)
      printf("0x%02x, ", (unsigned char) ((hash >> (j*8)) & 255));
    printf(" },\n");
  }
  return 0;
}