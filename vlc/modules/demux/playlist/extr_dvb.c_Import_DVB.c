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
struct TYPE_7__ {int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  s; TYPE_1__ obj; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FILE (TYPE_2__*) ; 
 int /*<<< orphan*/ * ParseLine (char*) ; 
 int /*<<< orphan*/  ReadDir ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/  const*,char,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stream_HasExtension (TYPE_2__*,char*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

int Import_DVB(vlc_object_t *p_this)
{
    stream_t *demux = (stream_t *)p_this;

    CHECK_FILE(demux);
    if (!stream_HasExtension(demux, ".conf" ) && !demux->obj.force )
        return VLC_EGENERIC;

    /* Check if this really is a channels file */
    const uint8_t *peek;
    int len = vlc_stream_Peek(demux->s, &peek, 1023);
    if (len <= 0)
        return VLC_EGENERIC;

    const uint8_t *eol = memchr(peek, '\n', len);
    if (eol == NULL)
        return VLC_EGENERIC;
    len = eol - peek;

    char line[len + 1];
    memcpy(line, peek, len);
    line[len] = '\0';

    input_item_t *item = ParseLine(line);
    if (item == NULL)
        return VLC_EGENERIC;
    input_item_Release(item);

    msg_Dbg(demux, "found valid channels.conf file");
    demux->pf_control = access_vaDirectoryControlHelper;
    demux->pf_readdir = ReadDir;

    return VLC_SUCCESS;
}