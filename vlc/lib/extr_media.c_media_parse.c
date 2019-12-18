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
struct TYPE_7__ {int has_asked_preparse; int is_parsed; int /*<<< orphan*/  parsed_lock; int /*<<< orphan*/  parsed_cond; int /*<<< orphan*/ * p_input_item; TYPE_1__* p_libvlc_instance; scalar_t__ parsed_status; } ;
typedef  TYPE_2__ libvlc_media_t ;
typedef  int libvlc_media_parse_flag_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_meta_request_option_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_libvlc_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  META_REQUEST_OPTION_DO_INTERACT ; 
 int /*<<< orphan*/  META_REQUEST_OPTION_FETCH_LOCAL ; 
 int /*<<< orphan*/  META_REQUEST_OPTION_FETCH_NETWORK ; 
 int /*<<< orphan*/  META_REQUEST_OPTION_SCOPE_LOCAL ; 
 int /*<<< orphan*/  META_REQUEST_OPTION_SCOPE_NETWORK ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  input_preparser_callbacks ; 
 int libvlc_MetadataRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int,TYPE_2__*) ; 
 int libvlc_media_do_interact ; 
 int libvlc_media_fetch_local ; 
 int libvlc_media_fetch_network ; 
 int libvlc_media_parse_network ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int media_parse(libvlc_media_t *media, bool b_async,
                       libvlc_media_parse_flag_t parse_flag, int timeout)
{
    bool needed;

    vlc_mutex_lock(&media->parsed_lock);
    needed = !media->has_asked_preparse;
    media->has_asked_preparse = true;
    if (needed)
    {
        media->is_parsed = false;
        media->parsed_status = 0;
    }
    vlc_mutex_unlock(&media->parsed_lock);

    if (needed)
    {
        libvlc_int_t *libvlc = media->p_libvlc_instance->p_libvlc_int;
        input_item_t *item = media->p_input_item;
        input_item_meta_request_option_t parse_scope = META_REQUEST_OPTION_SCOPE_LOCAL;
        int ret;

        if (parse_flag & libvlc_media_parse_network)
            parse_scope |= META_REQUEST_OPTION_SCOPE_NETWORK;
        if (parse_flag & libvlc_media_fetch_local)
            parse_scope |= META_REQUEST_OPTION_FETCH_LOCAL;
        if (parse_flag & libvlc_media_fetch_network)
            parse_scope |= META_REQUEST_OPTION_FETCH_NETWORK;
        if (parse_flag & libvlc_media_do_interact)
            parse_scope |= META_REQUEST_OPTION_DO_INTERACT;

        ret = libvlc_MetadataRequest(libvlc, item, parse_scope,
                                     &input_preparser_callbacks, media,
                                     timeout, media);
        if (ret != VLC_SUCCESS)
            return ret;
    }
    else
        return VLC_EGENERIC;

    if (!b_async)
    {
        vlc_mutex_lock(&media->parsed_lock);
        while (!media->is_parsed)
            vlc_cond_wait(&media->parsed_cond, &media->parsed_lock);
        vlc_mutex_unlock(&media->parsed_lock);
    }
    return VLC_SUCCESS;
}