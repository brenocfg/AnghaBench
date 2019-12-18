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
typedef  int /*<<< orphan*/  Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  varlink_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  varlink_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * varlink_unref (int /*<<< orphan*/ *) ; 

Varlink* varlink_flush_close_unref(Varlink *v) {

        if (!v)
                return NULL;

        (void) varlink_flush(v);
        (void) varlink_close(v);

        return varlink_unref(v);
}