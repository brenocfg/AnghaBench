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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_logger_operations {int dummy; } ;

/* Variables and functions */
 scalar_t__ VLC_MSG_ERR ; 
 struct vlc_logger_operations const ops ; 
 int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static const struct vlc_logger_operations *Open(vlc_object_t *obj, void **sysp)
{
    int verbosity = var_InheritInteger(obj, "verbose");

    if (verbosity < 0)
        return NULL;

    verbosity += VLC_MSG_ERR;
    *sysp = (void *)(uintptr_t)verbosity;

    return &ops;
}