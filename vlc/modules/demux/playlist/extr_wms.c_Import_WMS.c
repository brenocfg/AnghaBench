#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FILE (TYPE_1__*) ; 
 int /*<<< orphan*/  ReadDir ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

int Import_WMS(vlc_object_t *obj)
{
    stream_t *demux = (stream_t *)obj;
    const uint8_t *peek;

    CHECK_FILE(demux);

    if (vlc_stream_Peek(demux->s, &peek, 10) < 10
     || strncmp((const char *)peek, "[Reference]", 11))
        return VLC_EGENERIC;

    msg_Dbg(demux, "found WMS metafile");
    demux->pf_readdir = ReadDir;
    demux->pf_control = access_vaDirectoryControlHelper;
    return VLC_SUCCESS;
}