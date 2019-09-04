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
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static VOID
PnpDecodeIoPort(unsigned char *Ptr)
{
  USHORT MinBase;
  USHORT MaxBase;
  UCHAR Align;
  UCHAR Length;

  // Info = *Ptr;
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
  Length = *Ptr;

  printf("  I/O Port descriptor\n");
  printf("    MinBase 0x%x  MaxBase 0x%x  Align %u  Length %u\n",
	 MinBase, MaxBase, Align, Length);
}