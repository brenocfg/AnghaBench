#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__** available_modi ; 
 TYPE_1__** g_realloc (TYPE_1__**,int) ; 
 int num_available_modi ; 
 TYPE_1__* rofi_collect_modi_search (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean rofi_collect_modi_add ( Mode *mode )
{
    Mode *m = rofi_collect_modi_search ( mode->name );
    if ( m == NULL ) {
        available_modi = g_realloc ( available_modi, sizeof ( Mode * ) * ( num_available_modi + 1 ) );
        // Set mode.
        available_modi[num_available_modi] = mode;
        num_available_modi++;
        return TRUE;
    }
    return FALSE;
}