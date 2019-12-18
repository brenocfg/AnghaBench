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
struct TYPE_4__ {int /*<<< orphan*/  stopping; scalar_t__ started; int /*<<< orphan*/  class; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SESSION_GREETER ; 
 int /*<<< orphan*/  SESSION_USER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static bool elect_display_filter(Session *s) {
        /* Return true if the session is a candidate for the user’s ‘primary session’ or ‘display’. */
        assert(s);

        return IN_SET(s->class, SESSION_USER, SESSION_GREETER) && s->started && !s->stopping;
}