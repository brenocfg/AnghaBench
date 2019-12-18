#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_module; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ video_splitter_t ;
typedef  int /*<<< orphan*/  video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  module_need (TYPE_1__*,char*,char const*,int) ; 
 int /*<<< orphan*/  video_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  video_splitter_Delete (TYPE_1__*) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 

video_splitter_t *video_splitter_New( vlc_object_t *p_this,
                                      const char *psz_name,
                                      const video_format_t *p_fmt )
{
    video_splitter_t *p_splitter = vlc_custom_create( p_this,
                                       sizeof(*p_splitter), "video splitter" );
    if( !p_splitter )
        return NULL;

    video_format_Copy( &p_splitter->fmt, p_fmt );

    /* */
    p_splitter->p_module = module_need( p_splitter, "video splitter", psz_name, true );
    if( ! p_splitter->p_module )
    {
        video_splitter_Delete( p_splitter );
        return NULL;
    }

    return p_splitter;
}