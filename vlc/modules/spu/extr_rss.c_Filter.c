#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_31__ {int i_sar_num; int i_sar_den; scalar_t__ i_visible_width; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_height; scalar_t__ i_width; } ;
typedef  TYPE_5__ video_format_t ;
struct TYPE_32__ {int b_ephemer; int b_absolute; TYPE_4__* p_region; scalar_t__ i_stop; scalar_t__ i_start; } ;
typedef  TYPE_6__ subpicture_t ;
struct TYPE_33__ {int /*<<< orphan*/  p_picture; int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; } ;
typedef  TYPE_7__ subpicture_region_t ;
struct TYPE_34__ {scalar_t__* psz_title; size_t i_items; TYPE_9__* p_pic; TYPE_1__* p_items; } ;
typedef  TYPE_8__ rss_feed_t ;
struct TYPE_35__ {TYPE_3__* p; } ;
typedef  TYPE_9__ picture_t ;
struct TYPE_23__ {TYPE_11__* p_sys; } ;
typedef  TYPE_10__ filter_t ;
struct TYPE_24__ {int i_feeds; scalar_t__ last_date; size_t i_cur_char; int i_cur_item; scalar_t__ i_title; int i_speed; size_t i_cur_feed; char* psz_marquee; int i_pos; int /*<<< orphan*/  lock; TYPE_13__* p_style; int /*<<< orphan*/  i_yoff; int /*<<< orphan*/  i_xoff; TYPE_8__* p_feeds; scalar_t__ i_length; int /*<<< orphan*/  b_fetched; } ;
typedef  TYPE_11__ filter_sys_t ;
struct TYPE_28__ {scalar_t__ i_visible_height; } ;
struct TYPE_30__ {int i_align; int /*<<< orphan*/  i_x; TYPE_7__* p_next; int /*<<< orphan*/  i_y; TYPE_14__* p_text; TYPE_2__ fmt; } ;
struct TYPE_29__ {int /*<<< orphan*/  i_visible_lines; scalar_t__ i_visible_pitch; } ;
struct TYPE_27__ {scalar_t__* psz_title; } ;
struct TYPE_26__ {int /*<<< orphan*/  style; } ;
struct TYPE_25__ {scalar_t__ i_font_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnsureUTF8 (char*) ; 
 int SUBPICTURE_ALIGN_LEFT ; 
 int SUBPICTURE_ALIGN_TOP ; 
 int /*<<< orphan*/  VLC_CODEC_TEXT ; 
 int /*<<< orphan*/  VLC_CODEC_YUVA ; 
 size_t Y_PLANE ; 
 scalar_t__ default_title ; 
 TYPE_6__* filter_NewSubpicture (TYPE_10__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hide_title ; 
 int /*<<< orphan*/  msg_Err (TYPE_10__*,char*) ; 
 int /*<<< orphan*/  picture_Copy (int /*<<< orphan*/ ,TYPE_9__*) ; 
 scalar_t__ prepend_title ; 
 scalar_t__ scroll_title ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,...) ; 
 char* strchr (char*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 unsigned int strlen (char*) ; 
 int /*<<< orphan*/  subpicture_Delete (TYPE_6__*) ; 
 void* subpicture_region_New (TYPE_5__*) ; 
 TYPE_14__* text_segment_New (char*) ; 
 int /*<<< orphan*/  text_style_Duplicate (TYPE_13__*) ; 
 int /*<<< orphan*/  video_format_Init (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static subpicture_t *Filter( filter_t *p_filter, vlc_tick_t date )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    subpicture_t *p_spu;
    video_format_t fmt;
    subpicture_region_t *p_region;

    int i_feed, i_item;
    rss_feed_t *p_feed;

    vlc_mutex_lock( &p_sys->lock );

    /* Check if the feeds have been fetched and that we have some feeds */
    /* TODO: check that we have items for each feeds */
    if( !p_sys->b_fetched && p_sys->i_feeds > 0 )
    {
        vlc_mutex_unlock( &p_sys->lock );
        return NULL;
    }

    if( p_sys->last_date
       + ( p_sys->i_cur_char == 0 &&
           p_sys->i_cur_item == ( p_sys->i_title == scroll_title ? -1 : 0 ) ? 5 : 1 )
           /* ( ... ? 5 : 1 ) means "wait 5 times more for the 1st char" */
       * p_sys->i_speed > date )
    {
        vlc_mutex_unlock( &p_sys->lock );
        return NULL;
    }

    p_sys->last_date = date;
    p_sys->i_cur_char++;

    if( p_sys->i_cur_item == -1 ?
            p_sys->p_feeds[p_sys->i_cur_feed].psz_title[p_sys->i_cur_char] == 0 :
            p_sys->p_feeds[p_sys->i_cur_feed].p_items[p_sys->i_cur_item].psz_title[p_sys->i_cur_char] == 0 )
    {
        p_sys->i_cur_char = 0;
        p_sys->i_cur_item++;
        if( p_sys->i_cur_item >= p_sys->p_feeds[p_sys->i_cur_feed].i_items )
        {
            if( p_sys->i_title == scroll_title )
                p_sys->i_cur_item = -1;
            else
                p_sys->i_cur_item = 0;
            p_sys->i_cur_feed = (p_sys->i_cur_feed + 1)%p_sys->i_feeds;
        }
    }

    p_spu = filter_NewSubpicture( p_filter );
    if( !p_spu )
    {
        vlc_mutex_unlock( &p_sys->lock );
        return NULL;
    }

    video_format_Init( &fmt, VLC_CODEC_TEXT );

    p_spu->p_region = subpicture_region_New( &fmt );
    if( !p_spu->p_region )
    {
        subpicture_Delete( p_spu );
        vlc_mutex_unlock( &p_sys->lock );
        return NULL;
    }

    /* Generate the string that will be displayed. This string is supposed to
       be p_sys->i_length characters long. */
    i_item = p_sys->i_cur_item;
    i_feed = p_sys->i_cur_feed;
    p_feed = &p_sys->p_feeds[i_feed];

    if( ( p_feed->p_pic && p_sys->i_title == default_title )
        || p_sys->i_title == hide_title )
    {
        /* Don't display the feed's title if we have an image */
        snprintf( p_sys->psz_marquee, p_sys->i_length, "%s",
                  p_sys->p_feeds[i_feed].p_items[i_item].psz_title
                  +p_sys->i_cur_char );
    }
    else if( ( !p_feed->p_pic && p_sys->i_title == default_title )
             || p_sys->i_title == prepend_title )
    {
        snprintf( p_sys->psz_marquee, p_sys->i_length, "%s : %s",
                  p_sys->p_feeds[i_feed].psz_title,
                  p_sys->p_feeds[i_feed].p_items[i_item].psz_title
                  +p_sys->i_cur_char );
    }
    else /* scrolling title */
    {
        if( i_item == -1 )
            snprintf( p_sys->psz_marquee, p_sys->i_length, "%s : %s",
                      p_sys->p_feeds[i_feed].psz_title + p_sys->i_cur_char,
                      p_sys->p_feeds[i_feed].p_items[i_item+1].psz_title );
        else
            snprintf( p_sys->psz_marquee, p_sys->i_length, "%s",
                      p_sys->p_feeds[i_feed].p_items[i_item].psz_title
                      +p_sys->i_cur_char );
    }

    while( strlen( p_sys->psz_marquee ) < (unsigned int)p_sys->i_length )
    {
        i_item++;
        if( i_item == p_sys->p_feeds[i_feed].i_items ) break;
        snprintf( strchr( p_sys->psz_marquee, 0 ),
                  p_sys->i_length - strlen( p_sys->psz_marquee ),
                  " - %s",
                  p_sys->p_feeds[i_feed].p_items[i_item].psz_title );
    }

    /* Calls to snprintf might split multibyte UTF8 chars ...
     * which freetype doesn't like. */
    {
        char *a = strdup( p_sys->psz_marquee );
        char *a2 = a;
        char *b = p_sys->psz_marquee;
        EnsureUTF8( p_sys->psz_marquee );
        /* we want to use ' ' instead of '?' for erroneous chars */
        while( *b != '\0' )
        {
            if( *b != *a ) *b = ' ';
            b++;a++;
        }
        free( a2 );
    }

    p_spu->p_region->p_text = text_segment_New(p_sys->psz_marquee);
    if( p_sys->p_style->i_font_size > 0 )
        p_spu->p_region->fmt.i_visible_height = p_sys->p_style->i_font_size;
    p_spu->i_start = date;
    p_spu->i_stop  = 0;
    p_spu->b_ephemer = true;

    /*  where to locate the string: */
    if( p_sys->i_pos < 0 )
    {   /*  set to an absolute xy */
        p_spu->p_region->i_align = SUBPICTURE_ALIGN_LEFT | SUBPICTURE_ALIGN_TOP;
        p_spu->b_absolute = true;
    }
    else
    {   /* set to one of the 9 relative locations */
        p_spu->p_region->i_align = p_sys->i_pos;
        p_spu->b_absolute = false;
    }
    p_spu->p_region->i_x = p_sys->i_xoff;
    p_spu->p_region->i_y = p_sys->i_yoff;

    p_spu->p_region->p_text->style = text_style_Duplicate( p_sys->p_style );

    if( p_feed->p_pic )
    {
        /* Display the feed's image */
        picture_t *p_pic = p_feed->p_pic;
        video_format_t fmt_out;

        video_format_Init( &fmt_out, VLC_CODEC_YUVA );

        fmt_out.i_sar_num = fmt_out.i_sar_den = 1;
        fmt_out.i_width =
            fmt_out.i_visible_width = p_pic->p[Y_PLANE].i_visible_pitch;
        fmt_out.i_height =
            fmt_out.i_visible_height = p_pic->p[Y_PLANE].i_visible_lines;

        p_region = subpicture_region_New( &fmt_out );
        if( !p_region )
        {
            msg_Err( p_filter, "cannot allocate SPU region" );
        }
        else
        {
            p_region->i_x = p_spu->p_region->i_x;
            p_region->i_y = p_spu->p_region->i_y;
            /* FIXME the copy is probably not needed anymore */
            picture_Copy( p_region->p_picture, p_pic );
            p_spu->p_region->p_next = p_region;

            /* Offset text to display right next to the image */
            p_spu->p_region->i_x += fmt_out.i_visible_width;
        }
    }

    vlc_mutex_unlock( &p_sys->lock );
    return p_spu;
}