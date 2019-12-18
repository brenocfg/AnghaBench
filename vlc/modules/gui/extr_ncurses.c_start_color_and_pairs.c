#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_7__ {int color; int /*<<< orphan*/  yellow_b; int /*<<< orphan*/  yellow_g; int /*<<< orphan*/  yellow_r; } ;
typedef  TYPE_2__ intf_sys_t ;
struct TYPE_8__ {int /*<<< orphan*/  b; int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int C_DEFAULT ; 
 int C_MAX ; 
 scalar_t__ can_change_color () ; 
 int /*<<< orphan*/  color_content (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* color_pairs ; 
 int /*<<< orphan*/  has_colors () ; 
 int /*<<< orphan*/  init_color (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_pair (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  start_color () ; 

__attribute__((used)) static void start_color_and_pairs(intf_thread_t *intf)
{
    intf_sys_t *sys = intf->p_sys;

    if (!has_colors()) {
        sys->color = false;
        msg_Warn(intf, "Terminal doesn't support colors");
        return;
    }

    start_color();
    for (int i = C_DEFAULT + 1; i < C_MAX; i++)
        init_pair(i, color_pairs[i].f, color_pairs[i].b);

    /* untested, in all my terminals, !can_change_color() --funman */
    if (can_change_color()) {
        color_content(COLOR_YELLOW, &sys->yellow_r, &sys->yellow_g, &sys->yellow_b);
        init_color(COLOR_YELLOW, 960, 500, 0); /* YELLOW -> ORANGE */
    }
}