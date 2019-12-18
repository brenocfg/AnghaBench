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
struct TYPE_4__ {scalar_t__ matches; } ;
typedef  TYPE_1__ Match ;

/* Variables and functions */
 int /*<<< orphan*/  match_free (TYPE_1__*) ; 

__attribute__((used)) static void match_free_if_empty(Match *m) {
        if (!m || m->matches)
                return;

        match_free(m);
}