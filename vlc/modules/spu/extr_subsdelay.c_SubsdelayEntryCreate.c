#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int b_update_stop; int b_update_position; int b_check_empty; int b_last_region_saved; scalar_t__ i_last_region_align; scalar_t__ i_last_region_y; scalar_t__ i_last_region_x; int /*<<< orphan*/  i_new_stop; int /*<<< orphan*/  b_update_ephemer; int /*<<< orphan*/ * p_next; int /*<<< orphan*/ * p_filter; TYPE_3__* p_source; TYPE_3__* p_subpic; } ;
typedef  TYPE_1__ subsdelay_heap_entry_t ;
struct TYPE_11__ {int /*<<< orphan*/  pf_destroy; int /*<<< orphan*/  pf_update; int /*<<< orphan*/  pf_validate; TYPE_1__* p_sys; } ;
typedef  TYPE_2__ subpicture_updater_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_stop; int /*<<< orphan*/  b_ephemer; } ;
typedef  TYPE_3__ subpicture_t ;
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 TYPE_3__* SubpicClone (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SubpicDestroyWrapper ; 
 int /*<<< orphan*/  SubpicUpdateWrapper ; 
 int /*<<< orphan*/  SubpicValidateWrapper ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static subsdelay_heap_entry_t * SubsdelayEntryCreate( subpicture_t *p_source, filter_t *p_filter )
{
    subsdelay_heap_entry_t *p_entry;

    subpicture_t *p_new_subpic;

    subpicture_updater_t updater;

    /* allocate structure */

    p_entry = (subsdelay_heap_entry_t *) malloc( sizeof( subsdelay_heap_entry_t ) );

    if( !p_entry )
    {
        return NULL;
    }

    /* initialize local updater */

    updater.p_sys = p_entry;
    updater.pf_validate = SubpicValidateWrapper;
    updater.pf_update = SubpicUpdateWrapper;
    updater.pf_destroy = SubpicDestroyWrapper;

    /* create new subpic */

    p_new_subpic = SubpicClone( p_source,  &updater );

    if( !p_new_subpic )
    {
        free( p_entry );
        return NULL;
    }

    /* initialize entry */

    p_entry->p_subpic = p_new_subpic;
    p_entry->p_source = p_source;
    p_entry->p_filter = p_filter;
    p_entry->p_next = NULL;
    p_entry->b_update_stop = true;
    p_entry->b_update_ephemer = p_source->b_ephemer;
    p_entry->b_update_position = true;
    p_entry->b_check_empty = true;
    p_entry->i_new_stop = p_source->i_stop;
    p_entry->b_last_region_saved = false;
    p_entry->i_last_region_x = 0;
    p_entry->i_last_region_y = 0;
    p_entry->i_last_region_align = 0;

    return p_entry;
}