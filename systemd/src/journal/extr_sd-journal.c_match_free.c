#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* data; TYPE_1__* parent; struct TYPE_8__* matches; } ;
struct TYPE_7__ {int /*<<< orphan*/  matches; } ;
typedef  TYPE_2__ Match ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  matches ; 

__attribute__((used)) static void match_free(Match *m) {
        assert(m);

        while (m->matches)
                match_free(m->matches);

        if (m->parent)
                LIST_REMOVE(matches, m->parent->matches, m);

        free(m->data);
        free(m);
}