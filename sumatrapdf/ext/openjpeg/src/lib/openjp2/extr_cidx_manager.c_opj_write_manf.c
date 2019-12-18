#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_stream_private_t ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ length; } ;
typedef  TYPE_1__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 scalar_t__ JPIP_MANF ; 
 int /*<<< orphan*/  opj_stream_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_skip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ opj_stream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_write_bytes (int /*<<< orphan*/ *,scalar_t__,int) ; 

void opj_write_manf(int second,
                    int v,
                    opj_jp2_box_t *box,
                    opj_stream_private_t *cio,
                    opj_event_mgr_t * p_manager)
{
    OPJ_BYTE l_data_header [4];
    int i;
    OPJ_UINT32 len;
    OPJ_OFF_T lenp;

    lenp = opj_stream_tell(cio);
    opj_stream_skip(cio, 4, p_manager);              /* L [at the end]     */
    opj_write_bytes(l_data_header, JPIP_MANF, 4);    /* T                  */
    opj_stream_write_data(cio, l_data_header, 4, p_manager);

    if (second) {                         /* Write only during the second pass */
        for (i = 0; i < v; i++) {
            opj_write_bytes(l_data_header, box[i].length,
                            4);  /* Box length                     */
            opj_stream_write_data(cio, l_data_header, 4, p_manager);
            opj_write_bytes(l_data_header, box[i].type,
                            4);  /* Box type                       */
            opj_stream_write_data(cio, l_data_header, 4, p_manager);
        }
    }

    len = (OPJ_UINT32)(opj_stream_tell(cio) - lenp);
    opj_stream_seek(cio, lenp, p_manager);
    opj_write_bytes(l_data_header, len, 4);/* L                                 */
    opj_stream_write_data(cio, l_data_header, 4, p_manager);
    opj_stream_seek(cio, lenp + len, p_manager);
}