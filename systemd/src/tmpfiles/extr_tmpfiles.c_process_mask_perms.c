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
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int) ; 

__attribute__((used)) static mode_t process_mask_perms(mode_t mode, mode_t current) {

        if ((current & 0111) == 0)
                mode &= ~0111;
        if ((current & 0222) == 0)
                mode &= ~0222;
        if ((current & 0444) == 0)
                mode &= ~0444;
        if (!S_ISDIR(current))
                mode &= ~07000; /* remove sticky/sgid/suid bit, unless directory */

        return mode;
}