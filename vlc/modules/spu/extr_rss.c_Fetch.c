#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rss_feed_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_7__ {int b_fetched; int i_cur_item; scalar_t__ i_title; int /*<<< orphan*/  i_feeds; int /*<<< orphan*/  lock; scalar_t__ i_cur_char; scalar_t__ i_cur_feed; int /*<<< orphan*/ * p_feeds; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/ * FetchRSS (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeRSS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 scalar_t__ scroll_title ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Fetch( void *p_data )
{
    filter_t *p_filter = p_data;
    filter_sys_t *p_sys = p_filter->p_sys;

    msg_Dbg( p_filter, "Updating the rss feeds" );
    rss_feed_t *p_feeds = FetchRSS( p_filter );
    if( !p_feeds )
    {
        msg_Err( p_filter, "Unable to fetch the feeds" );
        return;
    }

    rss_feed_t *p_old_feeds = p_sys->p_feeds;

    vlc_mutex_lock( &p_sys->lock );
    /* Update the feeds */
    p_sys->p_feeds = p_feeds;
    p_sys->b_fetched = true;
    /* Set all current info to the original values */
    p_sys->i_cur_feed = 0;
    p_sys->i_cur_item = p_sys->i_title == scroll_title ? -1 : 0;
    p_sys->i_cur_char = 0;
    vlc_mutex_unlock( &p_sys->lock );

    if( p_old_feeds )
        FreeRSS( p_old_feeds, p_sys->i_feeds );
}