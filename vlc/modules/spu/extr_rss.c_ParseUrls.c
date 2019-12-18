#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  psz_url; int /*<<< orphan*/ * p_pic; int /*<<< orphan*/ * psz_image; int /*<<< orphan*/ * psz_description; int /*<<< orphan*/ * psz_link; int /*<<< orphan*/ * psz_title; int /*<<< orphan*/ * p_items; scalar_t__ i_items; } ;
typedef  TYPE_1__ rss_feed_t ;
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_8__ {int i_feeds; TYPE_1__* p_feeds; } ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 TYPE_1__* vlc_alloc (int,int) ; 

__attribute__((used)) static int ParseUrls( filter_t *p_filter, char *psz_urls )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    char *psz_urls2 = psz_urls;

    p_sys->i_feeds = 1;

    /* Count the number of feeds */
    while( *psz_urls )
    {
        if( *psz_urls == '|' )
            p_sys->i_feeds++;
        psz_urls++;
    }

    /* Allocate the structure */
    p_sys->p_feeds = vlc_alloc( p_sys->i_feeds, sizeof( rss_feed_t ) );
    if( !p_sys->p_feeds )
        return VLC_ENOMEM;

    /* Loop on all urls and fill in the struct */
    psz_urls = psz_urls2;
    for( int i = 0; i < p_sys->i_feeds; i++ )
    {
        rss_feed_t* p_feed = p_sys->p_feeds + i;
        char *psz_end;

        if( i < p_sys->i_feeds - 1 )
        {
            psz_end = strchr( psz_urls, '|' );
            *psz_end = '\0';
        }
        else
            psz_end = psz_urls;

        p_feed->i_items = 0;
        p_feed->p_items = NULL;
        p_feed->psz_title = NULL;
        p_feed->psz_link = NULL;
        p_feed->psz_description = NULL;
        p_feed->psz_image = NULL;
        p_feed->p_pic = NULL;
        p_feed->psz_url = strdup( psz_urls );

        psz_urls = psz_end + 1;
    }

    return VLC_SUCCESS;
}