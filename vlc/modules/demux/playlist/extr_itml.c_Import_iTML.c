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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  force; } ;
struct TYPE_7__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/  s; TYPE_1__ obj; } ;
typedef  TYPE_2__ stream_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FILE (TYPE_2__*) ; 
 int /*<<< orphan*/  ReadDir ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stream_HasExtension (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  strnstr (char const*,char*,int const) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

int Import_iTML( vlc_object_t *p_this )
{
    stream_t *p_demux = (stream_t *)p_this;
    CHECK_FILE(p_demux);
    if( !stream_HasExtension( p_demux, ".xml" )
     && !p_demux->obj.force )
        return VLC_EGENERIC;

    const uint8_t *p_peek;
    const ssize_t i_peek = vlc_stream_Peek( p_demux->s, &p_peek, 128 );
    if ( i_peek < 32 ||
         !strnstr( (const char *) p_peek, "<!DOCTYPE plist ", i_peek ) )
        return VLC_EGENERIC;

    msg_Dbg( p_demux, "using iTunes Media Library reader" );

    p_demux->pf_readdir = ReadDir;
    p_demux->pf_control = access_vaDirectoryControlHelper;

    return VLC_SUCCESS;
}