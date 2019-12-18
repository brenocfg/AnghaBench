#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* y1; void* x1; void* y0; void* x0; } ;
typedef  TYPE_5__ fz_rect ;
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_14__ {TYPE_4__ ur; TYPE_3__ ul; TYPE_2__ lr; TYPE_1__ ll; } ;
typedef  TYPE_6__ fz_quad ;

/* Variables and functions */
 void* MAX4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* MIN4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

fz_rect
fz_rect_from_quad(fz_quad q)
{
	fz_rect r;
	r.x0 = MIN4(q.ll.x, q.lr.x, q.ul.x, q.ur.x);
	r.y0 = MIN4(q.ll.y, q.lr.y, q.ul.y, q.ur.y);
	r.x1 = MAX4(q.ll.x, q.lr.x, q.ul.x, q.ur.x);
	r.y1 = MAX4(q.ll.y, q.lr.y, q.ul.y, q.ur.y);
	return r;
}