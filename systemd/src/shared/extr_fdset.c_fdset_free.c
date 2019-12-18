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
typedef  int /*<<< orphan*/  FDSet ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdset_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 

FDSet* fdset_free(FDSet *s) {
        fdset_close(s);
        set_free(MAKE_SET(s));
        return NULL;
}