#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* id; } ;
struct TYPE_6__ {scalar_t__ fdname; } ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 TYPE_4__* UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

char *socket_fdname(Socket *s) {
        assert(s);

        /* Returns the name to use for $LISTEN_NAMES. If the user
         * didn't specify anything specifically, use the socket unit's
         * name as fallback. */

        return s->fdname ?: UNIT(s)->id;
}