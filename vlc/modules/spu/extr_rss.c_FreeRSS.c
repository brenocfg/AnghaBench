#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i_items; struct TYPE_5__* psz_url; int /*<<< orphan*/ * p_pic; struct TYPE_5__* psz_image; struct TYPE_5__* psz_description; struct TYPE_5__* psz_link; struct TYPE_5__* psz_title; struct TYPE_5__* p_items; } ;
typedef  TYPE_1__ rss_item_t ;
typedef  TYPE_1__ rss_feed_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FreeRSS( rss_feed_t *p_feeds, int i_feeds )
{
    for( int i_feed = 0; i_feed < i_feeds; i_feed++ )
    {
        rss_feed_t *p_feed = p_feeds+i_feed;
        for( int i_item = 0; i_item < p_feed->i_items; i_item++ )
        {
            rss_item_t *p_item = p_feed->p_items+i_item;
            free( p_item->psz_title );
            free( p_item->psz_link );
            free( p_item->psz_description );
        }
        free( p_feed->p_items );
        free( p_feed->psz_title);
        free( p_feed->psz_link );
        free( p_feed->psz_description );
        free( p_feed->psz_image );
        if( p_feed->p_pic != NULL )
            picture_Release( p_feed->p_pic );
        free( p_feed->psz_url );
    }
    free( p_feeds );
}