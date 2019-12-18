#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int i_es; int /*<<< orphan*/  lock; TYPE_2__** es; } ;
typedef  TYPE_1__ input_item_t ;
struct TYPE_13__ {scalar_t__ i_id; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (int,TYPE_2__**,TYPE_2__*) ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_2__*) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_2__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_item_UpdateTracksInfo(input_item_t *item, const es_format_t *fmt)
{
    int i;
    es_format_t *fmt_copy = malloc(sizeof *fmt_copy);
    if (!fmt_copy)
        return;

    es_format_Copy(fmt_copy, fmt);

    vlc_mutex_lock( &item->lock );

    for( i = 0; i < item->i_es; i++ )
    {
        if (item->es[i]->i_id != fmt->i_id)
            continue;

        /* We've found the right ES, replace it */
        es_format_Clean(item->es[i]);
        free(item->es[i]);
        item->es[i] = fmt_copy;
        vlc_mutex_unlock( &item->lock );
        return;
    }

    /* ES not found, insert it */
    TAB_APPEND(item->i_es, item->es, fmt_copy);
    vlc_mutex_unlock( &item->lock );
}