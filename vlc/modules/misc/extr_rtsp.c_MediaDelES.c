#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vod_t ;
struct TYPE_10__ {int i_es; int /*<<< orphan*/  lock; TYPE_2__** es; } ;
typedef  TYPE_1__ vod_media_t ;
struct TYPE_13__ {scalar_t__ i_cat; scalar_t__ i_codec; scalar_t__ i_id; } ;
struct TYPE_11__ {TYPE_5__ fmt; scalar_t__ p_rtsp_url; struct TYPE_11__* psz_fmtp; } ;
typedef  TYPE_2__ media_es_t ;
struct TYPE_12__ {scalar_t__ i_cat; scalar_t__ i_codec; scalar_t__ i_id; } ;
typedef  TYPE_3__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_REMOVE (int,TYPE_2__**,TYPE_2__*) ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_5__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  httpd_UrlDelete (scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MediaDelES( vod_t *p_vod, vod_media_t *p_media, es_format_t *p_fmt)
{
    media_es_t *p_es = NULL;

    /* Find the ES */
    for( int i = 0; i < p_media->i_es; i++ )
    {
        if( p_media->es[i]->fmt.i_cat == p_fmt->i_cat &&
            p_media->es[i]->fmt.i_codec == p_fmt->i_codec &&
            p_media->es[i]->fmt.i_id == p_fmt->i_id )
        {
            p_es = p_media->es[i];
        }
    }
    if( !p_es ) return;

    msg_Dbg( p_vod, "  - Removing ES %4.4s", (char *)&p_fmt->i_codec );

    vlc_mutex_lock( &p_media->lock );
    TAB_REMOVE( p_media->i_es, p_media->es, p_es );
    vlc_mutex_unlock( &p_media->lock );

    free( p_es->psz_fmtp );

    if( p_es->p_rtsp_url ) httpd_UrlDelete( p_es->p_rtsp_url );
    es_format_Clean( &p_es->fmt );
    free( p_es );
}