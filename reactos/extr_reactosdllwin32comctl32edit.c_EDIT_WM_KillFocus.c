#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_5__ {int style; int /*<<< orphan*/  hwndSelf; scalar_t__ wheelDeltaRemainder; int /*<<< orphan*/  selection_end; int /*<<< orphan*/  selection_start; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ HTHEME ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyCaret () ; 
 int /*<<< orphan*/  EDIT_InvalidateText (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_NOTIFY_PARENT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF_FOCUSED ; 
 int /*<<< orphan*/  EN_KILLFOCUS ; 
 int ES_NOHIDESEL ; 
 int RDW_FRAME ; 
 int RDW_INVALIDATE ; 
 int RDW_UPDATENOW ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static LRESULT EDIT_WM_KillFocus(HTHEME theme, EDITSTATE *es)
{
    UINT flags = RDW_INVALIDATE | RDW_UPDATENOW;

    es->flags &= ~EF_FOCUSED;
    DestroyCaret();
    if (!(es->style & ES_NOHIDESEL))
        EDIT_InvalidateText(es, es->selection_start, es->selection_end);
    EDIT_NOTIFY_PARENT(es, EN_KILLFOCUS);
    /* Throw away left over scroll when we lose focus */
    es->wheelDeltaRemainder = 0;

    if (theme)
        flags |= RDW_FRAME;

    RedrawWindow(es->hwndSelf, NULL, NULL, flags);
    return 0;
}