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
typedef  int /*<<< orphan*/  vlc_plugin_t ;
struct vlc_logger {int dummy; } ;

/* Variables and functions */

void *module_Symbol(struct vlc_logger *log,
                    vlc_plugin_t *plugin, const char *name)
{
    (void) log; (void) plugin; (void) name;
    return NULL;
}