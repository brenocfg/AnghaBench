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
typedef  int /*<<< orphan*/  xspf_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/ * p_sys; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FILE (TYPE_1__*) ; 
 int /*<<< orphan*/  ReadDir ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stream_HasExtension (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stream_IsMimeType (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int Import_xspf(vlc_object_t *p_this)
{
    stream_t *p_stream = (stream_t *)p_this;

    CHECK_FILE(p_stream);

    if( !stream_HasExtension( p_stream, ".xspf" )
     && !stream_IsMimeType( p_stream->s, "application/xspf+xml" ) )
        return VLC_EGENERIC;

    xspf_sys_t *sys = calloc(1, sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    msg_Dbg(p_stream, "using XSPF playlist reader");
    p_stream->p_sys = sys;
    p_stream->pf_readdir = ReadDir;
    p_stream->pf_control = access_vaDirectoryControlHelper;

    return VLC_SUCCESS;
}