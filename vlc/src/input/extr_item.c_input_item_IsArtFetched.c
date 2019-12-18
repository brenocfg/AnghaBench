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
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ p_meta; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 int ITEM_ART_FETCHED ; 
 int vlc_meta_GetStatus (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool input_item_IsArtFetched( input_item_t *p_item )
{
    vlc_mutex_lock( &p_item->lock );
    bool b_fetched = p_item->p_meta ? ( vlc_meta_GetStatus(p_item->p_meta) & ITEM_ART_FETCHED ) != 0 : false;
    vlc_mutex_unlock( &p_item->lock );

    return b_fetched;
}