#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  opj_stream_private_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  int /*<<< orphan*/  opj_codestream_info_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 scalar_t__ JPIP_TPIX ; 
 int /*<<< orphan*/  opj_stream_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_skip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int opj_stream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_write_bytes (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  opj_write_tpixfaix (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int opj_write_tpix(int coff,
                   opj_codestream_info_t cstr_info,
                   int j2klen, opj_stream_private_t *cio,
                   opj_event_mgr_t * p_manager)
{
    OPJ_BYTE l_data_header [4];
    OPJ_UINT32 len;
    OPJ_OFF_T lenp;

    lenp = opj_stream_tell(cio);
    opj_stream_skip(cio, 4, p_manager);
    opj_write_bytes(l_data_header, JPIP_TPIX, 4); /* TPIX */
    opj_stream_write_data(cio, l_data_header, 4, p_manager);

    opj_write_tpixfaix(coff, 0, cstr_info, j2klen, cio, p_manager);

    len = (OPJ_UINT32)(opj_stream_tell(cio) - lenp);

    opj_stream_skip(cio, lenp, p_manager);
    opj_write_bytes(l_data_header, len, 4); /* L              */
    opj_stream_write_data(cio, l_data_header, 4, p_manager);
    opj_stream_seek(cio, lenp + len, p_manager);

    return (int)len;
}