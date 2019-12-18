#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char gchar ;
struct TYPE_5__ {char const* icon_theme; } ;
struct TYPE_4__ {int /*<<< orphan*/  icon_cache; int /*<<< orphan*/  icon_cache_uid; int /*<<< orphan*/  xdg_context; } ;
typedef  int /*<<< orphan*/  IconFetcher ;

/* Variables and functions */
 TYPE_3__ config ; 
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_direct_equal ; 
 int /*<<< orphan*/  g_direct_hash ; 
 int /*<<< orphan*/  g_hash_table_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_malloc0 (int) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 int /*<<< orphan*/  nk_xdg_theme_context_new (char const* const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_xdg_theme_preload_themes_icon (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  rofi_icon_fetch_entry_free ; 
 TYPE_1__* rofi_icon_fetcher_data ; 

void rofi_icon_fetcher_init ( void )
{
    g_assert ( rofi_icon_fetcher_data == NULL );

    static const gchar * const icon_fallback_themes[] = {
        "Adwaita",
        "gnome",
        NULL
    };
    const char                 *themes[2] = { config.icon_theme, NULL };

    rofi_icon_fetcher_data = g_malloc0 ( sizeof ( IconFetcher ) );

    rofi_icon_fetcher_data->xdg_context = nk_xdg_theme_context_new ( icon_fallback_themes, NULL );
    nk_xdg_theme_preload_themes_icon ( rofi_icon_fetcher_data->xdg_context, themes );

    rofi_icon_fetcher_data->icon_cache_uid = g_hash_table_new ( g_direct_hash, g_direct_equal );
    rofi_icon_fetcher_data->icon_cache     = g_hash_table_new_full ( g_str_hash, g_str_equal, NULL, rofi_icon_fetch_entry_free );
}