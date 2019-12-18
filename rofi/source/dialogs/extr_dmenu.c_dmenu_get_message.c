#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ message; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_1__ DmenuModePrivateData ;

/* Variables and functions */
 char* g_strdup (scalar_t__) ; 
 scalar_t__ mode_get_private_data (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static char *dmenu_get_message ( const Mode *sw )
{
    DmenuModePrivateData *pd = (DmenuModePrivateData *) mode_get_private_data ( sw );
    if ( pd->message ) {
        return g_strdup ( pd->message );
    }
    return NULL;
}