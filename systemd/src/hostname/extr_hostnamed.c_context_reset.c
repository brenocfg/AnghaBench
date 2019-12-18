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
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int _PROP_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_reset(Context *c) {
        int p;

        assert(c);

        for (p = 0; p < _PROP_MAX; p++)
                c->data[p] = mfree(c->data[p]);
}