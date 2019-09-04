#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {scalar_t__ top; scalar_t__ bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  int /*<<< orphan*/  SURFOBJ ;
typedef  TYPE_1__ RECTL ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DIB_32BPP_HLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
DIB_32BPP_ColorFill(SURFOBJ* DestSurface, RECTL* DestRect, ULONG color)
{
  ULONG DestY;

  for (DestY = DestRect->top; DestY< DestRect->bottom; DestY++)
  {
    DIB_32BPP_HLine (DestSurface, DestRect->left, DestRect->right, DestY, color);
  }

  return TRUE;
}