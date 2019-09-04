#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dwStyle; int /*<<< orphan*/  bRectsValid; scalar_t__ nHeight; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_9__ {TYPE_2__* pwpos; TYPE_1__* prc; } ;
struct TYPE_8__ {scalar_t__ cy; scalar_t__ cx; int /*<<< orphan*/  y; scalar_t__ x; int /*<<< orphan*/  flags; scalar_t__ hwndInsertAfter; int /*<<< orphan*/  hwnd; } ;
struct TYPE_7__ {int /*<<< orphan*/  top; scalar_t__ left; scalar_t__ right; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_3__* LPHDLAYOUT ;
typedef  TYPE_4__ HEADER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HDS_HIDDEN ; 
 int /*<<< orphan*/  SWP_NOZORDER ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
HEADER_Layout (HEADER_INFO *infoPtr, LPHDLAYOUT lpLayout)
{
    lpLayout->pwpos->hwnd = infoPtr->hwndSelf;
    lpLayout->pwpos->hwndInsertAfter = 0;
    lpLayout->pwpos->x = lpLayout->prc->left;
    lpLayout->pwpos->y = lpLayout->prc->top;
    lpLayout->pwpos->cx = lpLayout->prc->right - lpLayout->prc->left;
    if (infoPtr->dwStyle & HDS_HIDDEN)
        lpLayout->pwpos->cy = 0;
    else {
        lpLayout->pwpos->cy = infoPtr->nHeight;
        lpLayout->prc->top += infoPtr->nHeight;
    }
    lpLayout->pwpos->flags = SWP_NOZORDER;

    TRACE("Layout x=%d y=%d cx=%d cy=%d\n",
           lpLayout->pwpos->x, lpLayout->pwpos->y,
           lpLayout->pwpos->cx, lpLayout->pwpos->cy);

    infoPtr->bRectsValid = FALSE;

    return TRUE;
}