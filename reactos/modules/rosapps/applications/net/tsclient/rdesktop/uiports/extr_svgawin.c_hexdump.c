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
typedef  int uint8 ;
typedef  int uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void hexdump(uint8* p, uint32 len)
{
  uint8* line;
  int i;
  int thisline;
  int offset;

  line = p;
  offset = 0;
  while (offset < len)
  {
    printf("%04x ", offset);
    thisline = len - offset;
    if (thisline > 16)
      thisline = 16;

    for (i = 0; i < thisline; i++)
      printf("%02x ", line[i]);

    for (; i < 16; i++)
      printf("   ");

    for (i = 0; i < thisline; i++)
      printf("%c", (line[i] >= 0x20 && line[i] < 0x7f) ? line[i] : '.');

    printf("\n");
    offset += thisline;
    line += thisline;
  }
}