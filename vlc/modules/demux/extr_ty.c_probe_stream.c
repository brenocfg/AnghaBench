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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {scalar_t__ tivo_series; scalar_t__ audio_type; scalar_t__ tivo_type; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int CHUNK_PEEK_COUNT ; 
 int CHUNK_SIZE ; 
 scalar_t__ TIVO_AUDIO_UNKNOWN ; 
 scalar_t__ TIVO_SERIES_UNKNOWN ; 
 scalar_t__ TIVO_TYPE_UNKNOWN ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  analyze_chunk (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static int probe_stream(demux_t *p_demux)
{
    demux_sys_t *p_sys = p_demux->p_sys;
    const uint8_t *p_buf;
    int i;
    bool b_probe_error = false;

    /* we need CHUNK_PEEK_COUNT chunks of data, first one might be a Part header, so ... */
    if (vlc_stream_Peek( p_demux->s, &p_buf, CHUNK_PEEK_COUNT * CHUNK_SIZE ) <
            CHUNK_PEEK_COUNT * CHUNK_SIZE) {
        msg_Err(p_demux, "Can't peek %d chunks", CHUNK_PEEK_COUNT);
        /* TODO: if seekable, then loop reading chunks into a temp buffer */
        return VLC_EGENERIC;
    }

    /* the real work: analyze this chunk */
    for (i = 0; i < CHUNK_PEEK_COUNT; i++) {
        analyze_chunk(p_demux, p_buf);
        if (p_sys->tivo_series != TIVO_SERIES_UNKNOWN &&
            p_sys->audio_type  != TIVO_AUDIO_UNKNOWN &&
            p_sys->tivo_type   != TIVO_TYPE_UNKNOWN)
            break;
        p_buf += CHUNK_SIZE;
    }

    /* the final tally */
    if (p_sys->tivo_series == TIVO_SERIES_UNKNOWN) {
        msg_Err(p_demux, "Can't determine Tivo Series.");
        b_probe_error = true;
    }
    if (p_sys->audio_type == TIVO_AUDIO_UNKNOWN) {
        msg_Err(p_demux, "Can't determine Tivo Audio Type.");
        b_probe_error = true;
    }
    if (p_sys->tivo_type == TIVO_TYPE_UNKNOWN) {
        msg_Err(p_demux, "Can't determine Tivo Type (SA/DTivo).");
        b_probe_error = true;
    }
    return b_probe_error?VLC_EGENERIC:VLC_SUCCESS;
}