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
 char DIFF_STATUS_ADDED ; 
 char DIFF_STATUS_DELETED ; 
 char DIFF_STATUS_DIR_ADDED ; 
 char DIFF_STATUS_DIR_DELETED ; 
 char DIFF_STATUS_MODIFIED ; 
 char DIFF_STATUS_RENAMED ; 

__attribute__((used)) inline static const char*
get_diff_status_str(char status)
{
    if (status == DIFF_STATUS_ADDED)
        return "add";
    if (status == DIFF_STATUS_DELETED)
        return "del";
    if (status == DIFF_STATUS_MODIFIED)
        return "mod";
    if (status == DIFF_STATUS_RENAMED)
        return "mov";
    if (status == DIFF_STATUS_DIR_ADDED)
        return "newdir";
    if (status == DIFF_STATUS_DIR_DELETED)
        return "deldir";
    return NULL;
}