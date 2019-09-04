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
 int SYNC_ERROR_NUM ; 
 int /*<<< orphan*/  seaf_warning (char*,int) ; 
 char const** sync_error_str ; 

const char *
sync_error_to_str (int error)
{
    if (error < 0 || error >= SYNC_ERROR_NUM) {
        seaf_warning ("illegal sync error: %d\n", error); 
        return NULL;
    }

    return sync_error_str[error];
}