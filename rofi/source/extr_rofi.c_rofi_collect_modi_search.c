#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 TYPE_1__** available_modi ; 
 scalar_t__ g_strcmp0 (char const*,int /*<<< orphan*/ ) ; 
 unsigned int num_available_modi ; 

Mode * rofi_collect_modi_search ( const char *name )
{
    for ( unsigned int i = 0; i < num_available_modi; i++ ) {
        if ( g_strcmp0 ( name, available_modi[i]->name ) == 0 ) {
            return available_modi[i];
        }
    }
    return NULL;
}