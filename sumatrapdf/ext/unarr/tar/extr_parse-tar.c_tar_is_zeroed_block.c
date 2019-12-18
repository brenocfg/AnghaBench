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
 size_t TAR_BLOCK_SIZE ; 

__attribute__((used)) static bool tar_is_zeroed_block(const char *data)
{
    size_t i;
    for (i = 0; i < TAR_BLOCK_SIZE; i++) {
        if (data[i] != 0)
            return false;
    }
    return true;
}