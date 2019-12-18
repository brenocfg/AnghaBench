#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vlc_player_timer_point {int dummy; } ;
struct timer_state {int /*<<< orphan*/  vec; } ;
struct report_timer {struct vlc_player_timer_point const point; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_TIMER_POINT ; 
 int /*<<< orphan*/  assert (int) ; 
 int vlc_vector_push (int /*<<< orphan*/ *,struct report_timer) ; 

__attribute__((used)) static void
timers_on_update(const struct vlc_player_timer_point *point, void *data)
{
    struct timer_state *timer = data;
    struct report_timer report =
    {
        .type = REPORT_TIMER_POINT,
        .point = *point,
    };
    bool success = vlc_vector_push(&timer->vec, report);
    assert(success);
}