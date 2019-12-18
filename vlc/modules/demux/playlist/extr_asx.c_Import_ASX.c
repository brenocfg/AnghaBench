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
struct TYPE_6__ {int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FILE (TYPE_1__*) ; 
 scalar_t__ PeekASX (TYPE_1__*) ; 
 int /*<<< orphan*/  ReadDir ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ stream_HasExtension (TYPE_1__*,char*) ; 
 char* stream_MimeType (int /*<<< orphan*/ ) ; 

int Import_ASX( vlc_object_t *p_this )
{
    stream_t *p_demux = (stream_t *)p_this;

    CHECK_FILE(p_demux);

    char *type = stream_MimeType( p_demux->s );

    if( stream_HasExtension( p_demux, ".asx" )
     || stream_HasExtension( p_demux, ".wax" )
     || stream_HasExtension( p_demux, ".wvx" )
     || (type != NULL && (strcasecmp(type, "video/x-ms-asf") == 0
                       || strcasecmp(type, "audio/x-ms-wax") == 0)
                      && PeekASX( p_demux ) ) )
    {
        msg_Dbg( p_demux, "found valid ASX playlist" );
        free(type);
    }
    else
    {
        free(type);
        return VLC_EGENERIC;
    }

    p_demux->pf_control = access_vaDirectoryControlHelper;
    p_demux->pf_readdir = ReadDir;
    return VLC_SUCCESS;
}