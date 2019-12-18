#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_data; int /*<<< orphan*/  p_data; int /*<<< orphan*/  psz_mime; } ;
typedef  TYPE_1__ input_attachment_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ input_FindArtInCache (int /*<<< orphan*/ *) ; 
 TYPE_1__* input_GetAttachment (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  input_SaveArt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ input_item_IsArtFetched (int /*<<< orphan*/ *) ; 
 TYPE_3__* input_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (TYPE_1__*) ; 

void input_ExtractAttachmentAndCacheArt( input_thread_t *p_input,
                                         const char *name )
{
    input_item_t *p_item = input_priv(p_input)->p_item;

    if( input_item_IsArtFetched( p_item ) )
    {   /* XXX Weird, we should not end up with attachment:// art URL
         * unless there is a race condition */
        msg_Warn( p_input, "art already fetched" );
        if( likely(input_FindArtInCache( p_item ) == VLC_SUCCESS) )
            return;
    }

    /* */
    input_attachment_t *p_attachment = input_GetAttachment( p_input, name );
    if( !p_attachment )
    {
        msg_Warn( p_input, "art attachment %s not found", name );
        return;
    }

    /* */
    const char *psz_type = NULL;

    if( !strcmp( p_attachment->psz_mime, "image/jpeg" ) )
        psz_type = ".jpg";
    else if( !strcmp( p_attachment->psz_mime, "image/png" ) )
        psz_type = ".png";
    else if( !strcmp( p_attachment->psz_mime, "image/x-pict" ) )
        psz_type = ".pct";

    input_SaveArt( VLC_OBJECT(p_input), p_item,
                   p_attachment->p_data, p_attachment->i_data, psz_type );
    vlc_input_attachment_Delete( p_attachment );
}