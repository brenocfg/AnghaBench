#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_5__ {int /*<<< orphan*/  icon_cache_uid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * surface; } ;
typedef  TYPE_1__ IconFetcherEntry ;

/* Variables and functions */
 int /*<<< orphan*/  GINT_TO_POINTER (int /*<<< orphan*/  const) ; 
 TYPE_1__* g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* rofi_icon_fetcher_data ; 

cairo_surface_t * rofi_icon_fetcher_get  ( const uint32_t uid )
{
    IconFetcherEntry *sentry = g_hash_table_lookup ( rofi_icon_fetcher_data->icon_cache_uid, GINT_TO_POINTER ( uid ) );
    if ( sentry ) {
        return sentry->surface;
    }
    return NULL;
}