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
struct TYPE_4__ {int flags; int /*<<< orphan*/  read_from_master; } ;
typedef  TYPE_1__ PTYForward ;

/* Variables and functions */
 int PTY_FORWARD_IGNORE_INITIAL_VHANGUP ; 
 int PTY_FORWARD_IGNORE_VHANGUP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static bool ignore_vhangup(PTYForward *f) {
        assert(f);

        if (f->flags & PTY_FORWARD_IGNORE_VHANGUP)
                return true;

        if ((f->flags & PTY_FORWARD_IGNORE_INITIAL_VHANGUP) && !f->read_from_master)
                return true;

        return false;
}