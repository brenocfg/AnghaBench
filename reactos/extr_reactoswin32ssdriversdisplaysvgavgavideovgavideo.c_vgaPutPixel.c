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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  size_t INT ;

/* Variables and functions */
 scalar_t__ GRA_D ; 
 scalar_t__ GRA_I ; 
 int /*<<< orphan*/  READ_REGISTER_UCHAR (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_REGISTER_UCHAR (scalar_t__,int /*<<< orphan*/ ) ; 
 int* maskbit ; 
 scalar_t__ vidmem ; 
 scalar_t__* xconv ; 
 scalar_t__* y80 ; 

VOID vgaPutPixel(INT x, INT y, UCHAR c)
{
    ULONG offset;

    offset = xconv[x]+y80[y];

    WRITE_PORT_UCHAR((PUCHAR)GRA_I,0x08);
    WRITE_PORT_UCHAR((PUCHAR)GRA_D,maskbit[x]);

    READ_REGISTER_UCHAR(vidmem + offset);
    WRITE_REGISTER_UCHAR(vidmem + offset, c);
}