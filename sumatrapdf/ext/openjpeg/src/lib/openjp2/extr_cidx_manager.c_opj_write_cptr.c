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
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 scalar_t__ JPIP_CPTR ; 
 int /*<<< orphan*/  opj_stream_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_skip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ opj_stream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_write_bytes (int /*<<< orphan*/ *,scalar_t__,int) ; 

void opj_write_cptr(int coff, int clen, opj_stream_private_t *cio,
                    opj_event_mgr_t * p_manager)
{
    OPJ_BYTE l_data_header [3 * 8];
    OPJ_UINT32 len;
    OPJ_OFF_T lenp;


    lenp = opj_stream_tell(cio);
    opj_stream_skip(cio, 4, p_manager);                /* L [at the end]     */
    opj_write_bytes(l_data_header, JPIP_CPTR, 4);    /* T                  */
    opj_write_bytes(l_data_header + 4, 0, 2);          /* DR  A PRECISER !!  */
    opj_write_bytes(l_data_header + 6, 0, 2);          /* CONT               */
    opj_write_bytes(l_data_header + 8, (OPJ_UINT32)coff,
                    8);   /* COFF A PRECISER !! */
    opj_write_bytes(l_data_header + 16, (OPJ_UINT32)clen,
                    8);   /* CLEN               */
    opj_stream_write_data(cio, l_data_header, 3 * 8, p_manager);

    len = (OPJ_UINT32)(opj_stream_tell(cio) - lenp);
    opj_stream_seek(cio, lenp, p_manager);
    opj_write_bytes(l_data_header, len, 4);         /* L                  */
    opj_stream_write_data(cio, l_data_header, 4, p_manager);
    opj_stream_seek(cio, lenp + len, p_manager);

}