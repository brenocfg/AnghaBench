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
struct TYPE_4__ {struct TYPE_4__* psz_demux_filter; struct TYPE_4__* psz_icon_uri; struct TYPE_4__* psz_sout; struct TYPE_4__* psz_type; struct TYPE_4__* psz_name; } ;
typedef  TYPE_1__ vlc_renderer_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
item_free(vlc_renderer_item_t *p_item)
{
    free(p_item->psz_name);
    free(p_item->psz_type);
    free(p_item->psz_sout);
    free(p_item->psz_icon_uri);
    free(p_item->psz_demux_filter);
    free(p_item);
}