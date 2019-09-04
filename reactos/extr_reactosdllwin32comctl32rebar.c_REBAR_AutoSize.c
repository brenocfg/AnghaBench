#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {void* rcTarget; void* rcActual; int /*<<< orphan*/  fChanged; } ;
struct TYPE_8__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  void* RECT ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ NMRBAUTOSIZE ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EqualRect (void**,void**) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  RBN_AUTOSIZE ; 
 int /*<<< orphan*/  REBAR_Layout (TYPE_1__*) ; 
 int /*<<< orphan*/  REBAR_Notify (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REBAR_SizeToHeight (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rect_cy (TYPE_1__*,void**) ; 

__attribute__((used)) static VOID
REBAR_AutoSize(REBAR_INFO *infoPtr, BOOL needsLayout)
{
    RECT rc, rcNew;
    NMRBAUTOSIZE autosize;

    if (needsLayout)
        REBAR_Layout(infoPtr);
    GetClientRect(infoPtr->hwndSelf, &rc);
    REBAR_SizeToHeight(infoPtr, get_rect_cy(infoPtr, &rc));
    GetClientRect(infoPtr->hwndSelf, &rcNew);

    GetClientRect(infoPtr->hwndSelf, &autosize.rcTarget);
    autosize.fChanged = EqualRect(&rc, &rcNew);
    autosize.rcTarget = rc;
    autosize.rcActual = rcNew;
    REBAR_Notify((NMHDR *)&autosize, infoPtr, RBN_AUTOSIZE);
}