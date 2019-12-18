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

/* Variables and functions */
 int /*<<< orphan*/ * label_hnd ; 
 int /*<<< orphan*/  selabel_close (int /*<<< orphan*/ *) ; 

void mac_selinux_finish(void) {

#if HAVE_SELINUX
        if (!label_hnd)
                return;

        selabel_close(label_hnd);
        label_hnd = NULL;
#endif
}