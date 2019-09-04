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
typedef  int WORD ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int PCHAR ;
typedef  int DWORD ;

/* Variables and functions */
#define  BMF_16BPP_555 134 
#define  BMF_16BPP_565 133 
#define  BMF_1BPP 132 
#define  BMF_24BPP_BGR 131 
#define  BMF_24BPP_RGB 130 
#define  BMF_32BPP_BGR 129 
#define  BMF_32BPP_RGB 128 

ULONG
GetDIBPixel(ULONG iFormat, PVOID pvBits, ULONG x)
{
    switch (iFormat)
    {
        case BMF_1BPP:
            // 
        case BMF_16BPP_555:
        case BMF_16BPP_565:
            return *(WORD*)((PCHAR)pvBits + x * sizeof(WORD));

        case BMF_24BPP_RGB:
        case BMF_24BPP_BGR:
            return (*(DWORD*)((PCHAR)pvBits + x * 3)) & 0xffffff;

        case BMF_32BPP_RGB:
        case BMF_32BPP_BGR:
            return *(DWORD*)((PCHAR)pvBits + x * sizeof(DWORD));
    }
    return 0;
}