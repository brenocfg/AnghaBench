#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget ;
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {TYPE_1__ widget; } ;
typedef  TYPE_2__ textbox ;

/* Variables and functions */
 int /*<<< orphan*/  textbox_moveresize (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,short) ; 

__attribute__((used)) static void textbox_resize ( widget *wid, short w, short h )
{
    textbox *tb = (textbox *) wid;
    textbox_moveresize ( tb, tb->widget.x, tb->widget.y, w, h );
}