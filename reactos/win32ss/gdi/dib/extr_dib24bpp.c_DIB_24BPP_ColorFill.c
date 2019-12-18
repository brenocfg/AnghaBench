#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_7__ {int top; int left; int right; int bottom; } ;
struct TYPE_6__ {int lDelta; scalar_t__ pvScan0; } ;
typedef  TYPE_1__ SURFOBJ ;
typedef  TYPE_2__ RECTL ;
typedef  int* PUSHORT ;
typedef  int* PBYTE ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DIB_24BPP_HLine (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
DIB_24BPP_ColorFill(SURFOBJ* DestSurface, RECTL* DestRect, ULONG color)
{
  LONG DestY;

#if defined(_M_IX86) && !defined(_MSC_VER)
  PBYTE xaddr = (PBYTE)DestSurface->pvScan0 + DestRect->top * DestSurface->lDelta + (DestRect->left << 1) + DestRect->left;
  PBYTE addr;
  ULONG Count;
  ULONG xCount=DestRect->right - DestRect->left;

  for (DestY = DestRect->top; DestY< DestRect->bottom; DestY++)
  {
    Count = xCount;
    addr = xaddr;
    xaddr = (PBYTE)((ULONG_PTR)addr + DestSurface->lDelta);

    if (Count < 8)
    {
      /* For small fills, don't bother doing anything fancy */
      while (Count--)
        {
          *(PUSHORT)(addr) = color;
          addr += 2;
          *(addr) = color >> 16;
          addr += 1;
        }
    }
    else
    {
      /* Align to 4-byte address */
      while (0 != ((ULONG_PTR) addr & 0x3))
      {
        *(PUSHORT)(addr) = color;
        addr += 2;
        *(addr) = color >> 16;
        addr += 1;
        Count--;
      }
      /* If the color we need to fill with is 0ABC, then the final mem pattern
       * (note little-endianness) would be:
       *
       * |C.B.A|C.B.A|C.B.A|C.B.A|   <- pixel borders
       * |C.B.A.C|B.A.C.B|A.C.B.A|   <- ULONG borders
       *
       * So, taking endianness into account again, we need to fill with these
       * ULONGs: CABC BCAB ABCA */

      /* This is about 30% faster than the generic C code below */
      __asm__ __volatile__ (
        "movl %1, %%ecx\n\t"
        "andl $0xffffff, %%ecx\n\t"     /* 0ABC */
        "movl %%ecx, %%ebx\n\t"         /* Construct BCAB in ebx */
        "shrl $8, %%ebx\n\t"
        "movl %%ecx, %%eax\n\t"
        "shll $16, %%eax\n\t"
        "orl  %%eax, %%ebx\n\t"
        "movl %%ecx, %%edx\n\t"         /* Construct ABCA in edx */
        "shll $8, %%edx\n\t"
        "movl %%ecx, %%eax\n\t"
        "shrl $16, %%eax\n\t"
        "orl  %%eax, %%edx\n\t"
        "movl %%ecx, %%eax\n\t"         /* Construct CABC in eax */
        "shll $24, %%eax\n\t"
        "orl  %%ecx, %%eax\n\t"
        "movl %2, %%ecx\n\t"            /* Load count */
        "shr  $2, %%ecx\n\t"
        "movl %3, %%edi\n"              /* Load dest */
        "1:\n\t"
        "movl %%eax, (%%edi)\n\t"       /* Store 4 pixels, 12 bytes */
        "movl %%ebx, 4(%%edi)\n\t"
        "movl %%edx, 8(%%edi)\n\t"
        "addl $12, %%edi\n\t"
        "dec  %%ecx\n\t"
        "jnz  1b\n\t"
        "movl %%edi, %0"
        : "=m"(addr)
        : "m"(color), "m"(Count), "m"(addr)
        : "%eax", "%ebx", "%ecx", "%edx", "%edi");
      Count = Count & 0x03;
      while (0 != Count--)
      {
        *(PUSHORT)(addr) = color;
        addr += 2;
        *(addr) = color >> 16;
        addr += 1;
      }
    }
  }
#else

  for (DestY = DestRect->top; DestY< DestRect->bottom; DestY++)
  {
    DIB_24BPP_HLine(DestSurface, DestRect->left, DestRect->right, DestY, color);
  }
#endif
  return TRUE;
}