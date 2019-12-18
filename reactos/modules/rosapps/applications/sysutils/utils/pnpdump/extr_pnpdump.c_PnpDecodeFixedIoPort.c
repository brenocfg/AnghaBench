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
PnpDecodeFixedIoPort(unsigned char *Ptr)
{
  USHORT IoPort;
  UCHAR Length;

  IoPort = *Ptr;
  Ptr++;
  IoPort += (*Ptr << 8);
  Ptr++;
  Length = *Ptr;

  printf("  Fixed I/O Port descriptor\n");
  printf("    PortBase 0x%hx  Length 0x%x\n",
	 IoPort, Length);

#if 0
  if (Length == 1)
    {
      printf("  Fixed location I/O Port descriptor: 0x%x\n",
	     IoPort);
    }
  else
    {
      printf("  Fixed location I/O Port descriptor: 0x%x - 0x%x\n",
	     IoPort,
	     IoPort + Length - 1);
    }
#endif
}