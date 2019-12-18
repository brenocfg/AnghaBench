#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_stream_private_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_5__ {TYPE_1__* marker; scalar_t__ marknum; scalar_t__ main_head_start; scalar_t__ main_head_end; } ;
typedef  TYPE_2__ opj_codestream_info_t ;
struct TYPE_4__ {size_t type; int pos; scalar_t__ len; } ;
typedef  size_t OPJ_UINT32 ;
typedef  size_t OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 size_t JPIP_MHIX ; 
 int /*<<< orphan*/  opj_stream_seek (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_skip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 size_t opj_stream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_write_bytes (int /*<<< orphan*/ *,size_t,int) ; 

int opj_write_mainmhix(int coff, opj_codestream_info_t cstr_info,
                       opj_stream_private_t *cio,
                       opj_event_mgr_t * p_manager)
{
    OPJ_BYTE l_data_header [8];
    OPJ_UINT32 i;
    OPJ_UINT32 len;
    OPJ_OFF_T lenp;

    lenp = opj_stream_tell(cio);
    opj_stream_skip(cio, 4,
                    p_manager);               /* L [at the end]                    */
    opj_write_bytes(l_data_header, JPIP_MHIX,
                    4);     /* MHIX                              */
    opj_stream_write_data(cio, l_data_header, 4, p_manager);

    opj_write_bytes(l_data_header,
                    (OPJ_UINT32)(cstr_info.main_head_end - cstr_info.main_head_start + 1),
                    8);        /* TLEN                              */
    opj_stream_write_data(cio, l_data_header, 8, p_manager);

    for (i = 1; i < (OPJ_UINT32)cstr_info.marknum;
            i++) {  /* Marker restricted to 1 apparition, skip SOC marker */
        opj_write_bytes(l_data_header, cstr_info.marker[i].type, 2);
        opj_write_bytes(l_data_header + 2, 0, 2);
        opj_stream_write_data(cio, l_data_header, 4, p_manager);
        opj_write_bytes(l_data_header, (OPJ_UINT32)(cstr_info.marker[i].pos - coff), 8);
        opj_stream_write_data(cio, l_data_header, 8, p_manager);
        opj_write_bytes(l_data_header, (OPJ_UINT32)cstr_info.marker[i].len, 2);
        opj_stream_write_data(cio, l_data_header, 2, p_manager);
    }

    len = (OPJ_UINT32)(opj_stream_tell(cio) - lenp);
    opj_stream_seek(cio, lenp, p_manager);
    opj_write_bytes(l_data_header, len, 4); /* L  */
    opj_stream_write_data(cio, l_data_header, 4, p_manager);
    opj_stream_seek(cio, lenp + len, p_manager);

    return (int)len;
}