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
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_7__ {int right; int left; int top; int bottom; } ;
struct TYPE_6__ {int lDelta; scalar_t__ pvScan0; } ;
typedef  TYPE_1__ SURFOBJ ;
typedef  TYPE_2__ RECTL ;
typedef  scalar_t__ PULONG ;
typedef  scalar_t__ PBYTE ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DIB_16BPP_HLine (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
DIB_16BPP_ColorFill(SURFOBJ* DestSurface, RECTL* DestRect, ULONG color)
{
  LONG DestY;

#if defined(_M_IX86) && !defined(_MSC_VER)
  /* This is about 10% faster than the generic C code below */
  ULONG delta = DestSurface->lDelta;
  ULONG width = (DestRect->right - DestRect->left) ;
  PULONG pos =  (PULONG) ((PBYTE)DestSurface->pvScan0 + DestRect->top * delta + (DestRect->left<<1));
  color = (color&0xffff);  /* If the color value is "abcd", put "abcdabcd" into color */
  color += (color<<16);

  for (DestY = DestRect->top; DestY< DestRect->bottom; DestY++)
  {
    __asm__ __volatile__ (
      "cld\n\t"
      "mov  %1,%%ebx\n\t"
      "mov  %2,%%edi\n\t"
      "test $0x03, %%edi\n\t"   /* Align to fullword boundary */
      "jz   1f\n\t"
      "stosw\n\t"
      "dec  %%ebx\n\t"
      "jz   2f\n"
      "1:\n\t"
      "mov  %%ebx,%%ecx\n\t"    /* Setup count of fullwords to fill */
      "shr  $1,%%ecx\n\t"
      "rep stosl\n\t"           /* The actual fill */
      "test $0x01, %%ebx\n\t"   /* One left to do at the right side? */
      "jz   2f\n\t"
      "stosw\n"
      "2:"
      :
      : "a" (color), "r" (width), "m" (pos)
      : "%ecx", "%ebx", "%edi");
    pos =(PULONG)((ULONG_PTR)pos + delta);
  }
#else /* _M_IX86 */

  for (DestY = DestRect->top; DestY< DestRect->bottom; DestY++)
  {
    DIB_16BPP_HLine (DestSurface, DestRect->left, DestRect->right, DestY, color);
  }
#endif
  return TRUE;
}