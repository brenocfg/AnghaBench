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
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;

/* Variables and functions */
 scalar_t__ isprint (unsigned char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void HexDump(char *buffer, ULONG size)
{
  ULONG offset = 0;
  unsigned char *ptr;

  while (offset < (size & ~15))
    {
      ptr = (unsigned char*)((ULONG_PTR)buffer + offset);
      printf("%08lx  %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx-%02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx",
	     offset,
	     ptr[0],
	     ptr[1],
	     ptr[2],
	     ptr[3],
	     ptr[4],
	     ptr[5],
	     ptr[6],
	     ptr[7],
	     ptr[8],
	     ptr[9],
	     ptr[10],
	     ptr[11],
	     ptr[12],
	     ptr[13],
	     ptr[14],
	     ptr[15]);

      printf("  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
	     isprint(ptr[0])?ptr[0]:'.',
	     isprint(ptr[1])?ptr[1]:'.',
	     isprint(ptr[2])?ptr[2]:'.',
	     isprint(ptr[3])?ptr[3]:'.',
	     isprint(ptr[4])?ptr[4]:'.',
	     isprint(ptr[5])?ptr[5]:'.',
	     isprint(ptr[6])?ptr[6]:'.',
	     isprint(ptr[7])?ptr[7]:'.',
	     isprint(ptr[8])?ptr[8]:'.',
	     isprint(ptr[9])?ptr[9]:'.',
	     isprint(ptr[10])?ptr[10]:'.',
	     isprint(ptr[11])?ptr[11]:'.',
	     isprint(ptr[12])?ptr[12]:'.',
	     isprint(ptr[13])?ptr[13]:'.',
	     isprint(ptr[14])?ptr[14]:'.',
	     isprint(ptr[15])?ptr[15]:'.');

      offset += 16;
    }

  ptr = (unsigned char*)((ULONG_PTR)buffer + offset);
  if (offset < size)
    {
      printf("%08lx ", offset);
      while (offset < size)
	{
	  printf(" %02hx", *ptr);
	  offset++;
	  ptr++;
	}
    }

  printf("\n\n");
}