#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  extra; } ;
struct TYPE_9__ {TYPE_1__ brands; int /*<<< orphan*/  tracks; } ;
typedef  TYPE_2__ mp4mux_trackinfo_t ;
typedef  TYPE_2__ mp4mux_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  mp4mux_trackinfo_Clear (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 

void mp4mux_Delete(mp4mux_handle_t *h)
{
    for(size_t i=0; i<vlc_array_count(&h->tracks); i++)
    {
        mp4mux_trackinfo_t *t = vlc_array_item_at_index(&h->tracks, i);
        mp4mux_trackinfo_Clear(t);
        free(t);
    }
    vlc_array_clear(&h->tracks);
    ARRAY_RESET(h->brands.extra);
    free(h);
}