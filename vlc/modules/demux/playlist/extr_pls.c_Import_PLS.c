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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FILE (TYPE_1__*) ; 
 int /*<<< orphan*/  ReadDir ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stream_HasExtension (TYPE_1__*,char*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

int Import_PLS( vlc_object_t *p_this )
{
    stream_t *p_demux = (stream_t *)p_this;
    const uint8_t *p_peek;

    CHECK_FILE(p_demux);

    if( vlc_stream_Peek( p_demux->s, &p_peek, 10 ) < 10 ) {
        msg_Dbg( p_demux, "not enough data" );
        return VLC_EGENERIC;
    }

    if( strncasecmp( (const char *)p_peek, "[playlist]", 10 )
     && !stream_HasExtension( p_demux, ".pls" ) )
        return VLC_EGENERIC;

    msg_Dbg( p_demux, "found valid PLS playlist file");
    p_demux->pf_readdir = ReadDir;
    p_demux->pf_control = access_vaDirectoryControlHelper;

    return VLC_SUCCESS;
}