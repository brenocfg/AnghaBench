#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * locale; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int _VARIABLE_LC_MAX ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_free_locale(Context *c) {
        int p;

        for (p = 0; p < _VARIABLE_LC_MAX; p++)
                c->locale[p] = mfree(c->locale[p]);
}