#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_4__ {TYPE_1__* cmd_list; } ;
struct TYPE_3__ {scalar_t__ icon_fetch_uid; int /*<<< orphan*/ * icon_name; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_1__ DmenuScriptEntry ;
typedef  TYPE_2__ DmenuModePrivateData ;

/* Variables and functions */
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mode_get_private_data (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * rofi_icon_fetcher_get (scalar_t__) ; 
 scalar_t__ rofi_icon_fetcher_query (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static cairo_surface_t *dmenu_get_icon ( const Mode *sw, unsigned int selected_line, int height )
{
    DmenuModePrivateData *pd = (DmenuModePrivateData *) mode_get_private_data ( sw );
    g_return_val_if_fail ( pd->cmd_list != NULL, NULL );
    DmenuScriptEntry *dr = &( pd->cmd_list[selected_line] );
    if ( dr->icon_name == NULL ) {
        return NULL;
    }
    if ( dr->icon_fetch_uid > 0 ) {
        return rofi_icon_fetcher_get ( dr->icon_fetch_uid );
    }
    dr->icon_fetch_uid = rofi_icon_fetcher_query ( dr->icon_name, height );
    return rofi_icon_fetcher_get ( dr->icon_fetch_uid );
}