#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  psz_language; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_1__ es_format_t ;
struct TYPE_9__ {int /*<<< orphan*/  pl_info_lock; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {scalar_t__ lang; } ;
typedef  TYPE_3__ BLURAY_STREAM_INFO ;

/* Variables and functions */
 TYPE_3__* blurayGetStreamInfoByPIDUnlocked (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strndup (char const*,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setStreamLang(demux_sys_t *p_sys, es_format_t *p_fmt)
{
    vlc_mutex_lock(&p_sys->pl_info_lock);

    BLURAY_STREAM_INFO *p_stream = blurayGetStreamInfoByPIDUnlocked(p_sys, p_fmt->i_id);
    if(p_stream)
    {
        free(p_fmt->psz_language);
        p_fmt->psz_language = strndup((const char *)p_stream->lang, 3);
    }

    vlc_mutex_unlock(&p_sys->pl_info_lock);
}