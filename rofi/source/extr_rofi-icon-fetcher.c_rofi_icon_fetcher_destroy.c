#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  icon_cache; int /*<<< orphan*/  icon_cache_uid; int /*<<< orphan*/  xdg_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_xdg_theme_context_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* rofi_icon_fetcher_data ; 

void rofi_icon_fetcher_destroy ( void )
{
    if ( rofi_icon_fetcher_data == NULL ) {
        return;
    }

    nk_xdg_theme_context_free ( rofi_icon_fetcher_data->xdg_context );

    g_hash_table_unref ( rofi_icon_fetcher_data->icon_cache_uid );
    g_hash_table_unref ( rofi_icon_fetcher_data->icon_cache );

    g_free ( rofi_icon_fetcher_data );
}