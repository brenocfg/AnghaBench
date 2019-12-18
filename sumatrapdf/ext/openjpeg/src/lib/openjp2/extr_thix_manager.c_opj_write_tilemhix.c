#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ tp_start_pos; scalar_t__ tp_end_header; } ;
typedef  TYPE_1__ opj_tp_info_t ;
struct TYPE_7__ {int marknum; TYPE_3__* marker; TYPE_1__* tp; } ;
typedef  TYPE_2__ opj_tile_info_t ;
typedef  int /*<<< orphan*/  opj_stream_private_t ;
struct TYPE_8__ {int pos; scalar_t__ len; scalar_t__ type; } ;
typedef  TYPE_3__ opj_marker_info_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_9__ {TYPE_2__* tile; } ;
typedef  TYPE_4__ opj_codestream_info_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 scalar_t__ JPIP_MHIX ; 
 int /*<<< orphan*/  opj_stream_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_skip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ opj_stream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_write_bytes (int /*<<< orphan*/ *,scalar_t__,int) ; 

int opj_write_tilemhix(int coff, opj_codestream_info_t cstr_info, int tileno,
                       opj_stream_private_t *cio,
                       opj_event_mgr_t * p_manager)
{
    OPJ_BYTE l_data_header [8];
    int i;
    opj_tile_info_t tile;
    opj_tp_info_t tp;
    opj_marker_info_t *marker;
    OPJ_UINT32 len;
    OPJ_OFF_T lenp;

    lenp = opj_stream_tell(cio);
    opj_stream_skip(cio, 4,
                    p_manager);               /* L [at the end]                    */
    opj_write_bytes(l_data_header, JPIP_MHIX,
                    4);     /* MHIX                              */
    opj_stream_write_data(cio, l_data_header, 4, p_manager);

    tile = cstr_info.tile[tileno];
    tp = tile.tp[0];

    opj_write_bytes(l_data_header,
                    (OPJ_UINT32)(tp.tp_end_header - tp.tp_start_pos + 1),
                    8);        /* TLEN                              */
    opj_stream_write_data(cio, l_data_header, 8, p_manager);

    marker = cstr_info.tile[tileno].marker;

    for (i = 0; i < cstr_info.tile[tileno].marknum;
            i++) {        /* Marker restricted to 1 apparition */
        opj_write_bytes(l_data_header, marker[i].type, 2);
        opj_write_bytes(l_data_header + 2, 0, 2);
        opj_stream_write_data(cio, l_data_header, 4, p_manager);
        opj_write_bytes(l_data_header, (OPJ_UINT32)(marker[i].pos - coff), 8);
        opj_stream_write_data(cio, l_data_header, 8, p_manager);
        opj_write_bytes(l_data_header, (OPJ_UINT32)marker[i].len, 2);
        opj_stream_write_data(cio, l_data_header, 2, p_manager);
    }

    /*  free( marker);*/

    len = (OPJ_UINT32)(opj_stream_tell(cio) - lenp);
    opj_stream_seek(cio, lenp, p_manager);
    opj_write_bytes(l_data_header, len, 4); /* L  */
    opj_stream_write_data(cio, l_data_header, 4, p_manager);
    opj_stream_seek(cio, lenp + len, p_manager);

    return (int)len;
}