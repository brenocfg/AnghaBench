#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  vimTextArea; } ;
struct TYPE_17__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_14__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_13__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_16__ {TYPE_2__ ul; TYPE_1__ lr; } ;
struct TYPE_15__ {TYPE_4__ rect; struct TYPE_15__* next; } ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  TYPE_3__ PhTile_t ;
typedef  TYPE_4__ PhRect_t ;
typedef  TYPE_5__ PhPoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  PgClearTranslation () ; 
 int /*<<< orphan*/  PgGetTranslation (TYPE_5__*) ; 
 int /*<<< orphan*/  PgSetTranslation (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PhTranslatePoint (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtBasic ; 
 int /*<<< orphan*/  PtSuperClassDraw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  PtWidgetOffset (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  PtWidgetPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 TYPE_7__ gui ; 
 int /*<<< orphan*/  gui_redraw (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ is_ignore_draw ; 
 int /*<<< orphan*/  out_flush () ; 

__attribute__((used)) static void
gui_ph_handle_raw_draw(PtWidget_t *widget, PhTile_t *damage)
{
    PhRect_t	*r;
    PhPoint_t	offset;
    PhPoint_t	translation;

    if (is_ignore_draw == TRUE)
	return;

    PtSuperClassDraw(PtBasic, widget, damage);
    PgGetTranslation(&translation);
    PgClearTranslation();

#if 0
    /*
     * This causes some weird problems, with drawing being done from
     * within this raw drawing function (rather than just simple clearing
     * and text drawing done by gui_redraw)
     *
     * The main problem is when PhBlit is used, and the cursor appearing
     * in places where it shouldn't
     */
    out_flush();
#endif

    PtWidgetOffset(widget, &offset);
    PhTranslatePoint(&offset, PtWidgetPos(gui.vimTextArea, NULL));

#if 1
    /* Redraw individual damage regions */
    if (damage->next != NULL)
	damage = damage->next;

    while (damage != NULL)
    {
	r = &damage->rect;
	gui_redraw(
		r->ul.x - offset.x, r->ul.y - offset.y,
		r->lr.x - r->ul.x + 1,
		r->lr.y - r->ul.y + 1);
	damage = damage->next;
    }
#else
    /* Redraw the rectangle that covers all the damaged regions */
    r = &damage->rect;
    gui_redraw(
	    r->ul.x - offset.x, r->ul.y - offset.y,
	    r->lr.x - r->ul.x + 1,
	    r->lr.y - r->ul.y + 1);
#endif

    PgSetTranslation(&translation, 0);
}