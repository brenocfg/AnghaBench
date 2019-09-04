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
typedef  int /*<<< orphan*/  VOID ;
typedef  unsigned char ULONG ;
typedef  unsigned char UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static VOID
PnpDecodeMemory32(unsigned char *Ptr)
{
  UCHAR Info;
  ULONG MinBase;
  ULONG MaxBase;
  ULONG Align;
  ULONG Length;

  Info = *Ptr;
  Ptr++;

  MinBase = *Ptr;
  Ptr++;
  MinBase += (*Ptr << 8);
  Ptr++;
  MinBase += (*Ptr << 16);
  Ptr++;
  MinBase += (*Ptr << 24);
  Ptr++;

  MaxBase = *Ptr;
  Ptr++;
  MaxBase += (*Ptr << 8);
  Ptr++;
  MaxBase += (*Ptr << 16);
  Ptr++;
  MaxBase += (*Ptr << 24);
  Ptr++;

  Align = *Ptr;
  Ptr++;
  Align += (*Ptr << 8);
  Ptr++;
  Align += (*Ptr << 16);
  Ptr++;
  Align += (*Ptr << 24);
  Ptr++;

  Length = *Ptr;
  Ptr++;
  Length += (*Ptr << 8);
  Ptr++;
  Length += (*Ptr << 16);
  Ptr++;
  Length += (*Ptr << 24);

  printf("  32-Bit memory range descriptor\n");
  printf("    MinBase 0x%lx  MaxBase 0x%lx  Align 0x%lx  Length 0x%lx  Flags 0x%02x\n",
	 MinBase, MaxBase, Align,Length, Info);
}