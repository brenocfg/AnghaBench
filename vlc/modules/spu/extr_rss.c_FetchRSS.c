#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_15__ {int /*<<< orphan*/  psz_url; int /*<<< orphan*/ * psz_image; int /*<<< orphan*/ * p_pic; int /*<<< orphan*/ * p_items; scalar_t__ i_items; int /*<<< orphan*/ * psz_link; int /*<<< orphan*/ * psz_description; int /*<<< orphan*/ * psz_title; } ;
typedef  TYPE_1__ rss_feed_t ;
struct TYPE_16__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_17__ {int i_feeds; int b_images; TYPE_1__* p_feeds; } ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeRSS (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * LoadImage (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParseFeed (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_alloc (int,int) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_NewURL (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xml_ReaderCreate (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_ReaderDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static rss_feed_t* FetchRSS( filter_t *p_filter )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    stream_t *p_stream;
    xml_reader_t *p_xml_reader;
    int i_feed;

    /* These data are not modified after the creation of the module so we don't
       need to hold the lock */
    int i_feeds = p_sys->i_feeds;
    bool b_images = p_sys->b_images;

    /* Allocate a new structure */
    rss_feed_t *p_feeds = vlc_alloc( i_feeds, sizeof( rss_feed_t ) );
    if( !p_feeds )
        return NULL;

    /* Fetch all feeds and parse them */
    for( i_feed = 0; i_feed < i_feeds; i_feed++ )
    {
        rss_feed_t *p_feed = p_feeds + i_feed;
        rss_feed_t *p_old_feed = p_sys->p_feeds + i_feed;

        /* Initialize the structure */
        p_feed->psz_title = NULL;
        p_feed->psz_description = NULL;
        p_feed->psz_link = NULL;
        p_feed->psz_image = NULL;
        p_feed->p_pic = NULL;
        p_feed->i_items = 0;
        p_feed->p_items = NULL;

        p_feed->psz_url = strdup( p_old_feed->psz_url );

        /* Fetch the feed */
        msg_Dbg( p_filter, "opening %s RSS/Atom feed ...", p_feed->psz_url );

        p_stream = vlc_stream_NewURL( p_filter, p_feed->psz_url );
        if( !p_stream )
        {
            msg_Err( p_filter, "Failed to open %s for reading", p_feed->psz_url );
            p_xml_reader = NULL;
            goto error;
        }

        p_xml_reader = xml_ReaderCreate( p_filter, p_stream );
        if( !p_xml_reader )
        {
            msg_Err( p_filter, "Failed to open %s for parsing", p_feed->psz_url );
            goto error;
        }

        /* Parse the feed */
        if( !ParseFeed( p_filter, p_xml_reader, p_feed ) )
            goto error;

        /* If we have a image: load it if requiere */
        if( b_images && p_feed->psz_image && !p_feed->p_pic )
        {
            p_feed->p_pic = LoadImage( p_filter, p_feed->psz_image );
        }

        msg_Dbg( p_filter, "done with %s RSS/Atom feed", p_feed->psz_url );
        xml_ReaderDelete( p_xml_reader );
        vlc_stream_Delete( p_stream );
    }

    return p_feeds;

error:
    FreeRSS( p_feeds, i_feed + 1 );
    if( p_xml_reader )
        xml_ReaderDelete( p_xml_reader );
    if( p_stream )
        vlc_stream_Delete( p_stream );

    return NULL;
}