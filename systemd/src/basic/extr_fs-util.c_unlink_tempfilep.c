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
 int /*<<< orphan*/  endswith (char*,char*) ; 
 int /*<<< orphan*/  unlink_noerrno (char*) ; 

void unlink_tempfilep(char (*p)[]) {
        /* If the file is created with mkstemp(), it will (almost always)
         * change the suffix. Treat this as a sign that the file was
         * successfully created. We ignore both the rare case where the
         * original suffix is used and unlink failures. */
        if (!endswith(*p, ".XXXXXX"))
                (void) unlink_noerrno(*p);
}