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
typedef  unsigned char USHORT ;
typedef  unsigned char UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static VOID
PnpDecodeMemory16(unsigned char *Ptr)
{
  UCHAR Info;
  USHORT MinBase;
  USHORT MaxBase;
  USHORT Align;
  USHORT Length;

  Info = *Ptr;
  Ptr++;

  MinBase = *Ptr;
  Ptr++;
  MinBase += (*Ptr << 8);
  Ptr++;

  MaxBase = *Ptr;
  Ptr++;
  MaxBase += (*Ptr << 8);
  Ptr++;

  Align = *Ptr;
  Ptr++;
  Align += (*Ptr << 8);
  Ptr++;

  Length = *Ptr;
  Ptr++;
  Length += (*Ptr << 8);

  printf("  16-Bit memory range descriptor\n");
  printf("    MinBase 0x%hx  MaxBase 0x%hx  Align 0x%hx  Length 0x%hx  Flags 0x%02x\n",
	 MinBase, MaxBase, Align,Length, Info);
}