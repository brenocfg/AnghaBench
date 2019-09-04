#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum CachedBrush { ____Placeholder_CachedBrush } CachedBrush ;
typedef  size_t UINT ;
struct TYPE_4__ {int* colors; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/ * pens; int /*<<< orphan*/ * brushes; } ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  int LRESULT ;
typedef  int COLORREF ;

/* Variables and functions */
 int BrushBackground ; 
 int BrushLast ; 
 int BrushMonth ; 
 int BrushTitle ; 
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateSolidBrush (int) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
#define  MCSC_BACKGROUND 130 
#define  MCSC_MONTHBK 129 
 size_t MCSC_TEXT ; 
#define  MCSC_TITLEBK 128 
 size_t MCSC_TRAILINGTEXT ; 
 int /*<<< orphan*/  PS_SOLID ; 
 size_t PenText ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,size_t,int) ; 

__attribute__((used)) static LRESULT
MONTHCAL_SetColor(MONTHCAL_INFO *infoPtr, UINT index, COLORREF color)
{
  enum CachedBrush type;
  COLORREF prev;

  TRACE("%p, %d: color %08x\n", infoPtr, index, color);

  if (index > MCSC_TRAILINGTEXT) return -1;

  prev = infoPtr->colors[index];
  infoPtr->colors[index] = color;

  /* update cached brush */
  switch (index)
  {
  case MCSC_BACKGROUND:
    type = BrushBackground;
    break;
  case MCSC_TITLEBK:
    type = BrushTitle;
    break;
  case MCSC_MONTHBK:
    type = BrushMonth;
    break;
  default:
    type = BrushLast;
  }

  if (type != BrushLast)
  {
    DeleteObject(infoPtr->brushes[type]);
    infoPtr->brushes[type] = CreateSolidBrush(color);
  }

  /* update cached pen */
  if (index == MCSC_TEXT)
  {
    DeleteObject(infoPtr->pens[PenText]);
    infoPtr->pens[PenText] = CreatePen(PS_SOLID, 1, infoPtr->colors[index]);
  }

  InvalidateRect(infoPtr->hwndSelf, NULL, index == MCSC_BACKGROUND);
  return prev;
}