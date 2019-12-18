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
struct TYPE_3__ {scalar_t__ type; scalar_t__ pos; } ;
typedef  TYPE_1__ opj_marker_info_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 scalar_t__ J2K_MS_COD ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_read_bytes (int /*<<< orphan*/ *,unsigned int*,int) ; 
 int /*<<< orphan*/  opj_stream_read_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ opj_stream_tell (int /*<<< orphan*/ *) ; 

OPJ_BOOL opj_check_EPHuse(int coff, opj_marker_info_t *markers, int marknum,
                          opj_stream_private_t *cio,
                          opj_event_mgr_t * p_manager)
{
    OPJ_BYTE l_data_header [4];
    OPJ_BOOL EPHused = OPJ_FALSE;
    int i = 0;
    OPJ_OFF_T org_pos;
    unsigned int Scod;

    for (i = 0; i < marknum; i++) {
        if (markers[i].type == J2K_MS_COD) {
            org_pos = opj_stream_tell(cio);
            opj_stream_seek(cio, coff + markers[i].pos + 2, p_manager);

            opj_stream_read_data(cio, l_data_header, 1, p_manager);
            opj_read_bytes(l_data_header, &Scod, 1);
            if (((Scod >> 2) & 1)) {
                EPHused = OPJ_TRUE;
            }
            opj_stream_seek(cio, org_pos, p_manager);

            break;
        }
    }
    return EPHused;
}