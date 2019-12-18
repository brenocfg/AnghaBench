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
typedef  int OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 scalar_t__ J2K_MS_SOT ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  opj_j2k_get_sot_values (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_read_bytes (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  opj_stream_has_seek (int /*<<< orphan*/ *) ; 
 scalar_t__ opj_stream_read_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int opj_stream_skip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int opj_stream_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPJ_BOOL opj_j2k_need_nb_tile_parts_correction(opj_stream_private_t
        *p_stream, OPJ_UINT32 tile_no, OPJ_BOOL* p_correction_needed,
        opj_event_mgr_t * p_manager)
{
    OPJ_BYTE   l_header_data[10];
    OPJ_OFF_T  l_stream_pos_backup;
    OPJ_UINT32 l_current_marker;
    OPJ_UINT32 l_marker_size;
    OPJ_UINT32 l_tile_no, l_tot_len, l_current_part, l_num_parts;

    /* initialize to no correction needed */
    *p_correction_needed = OPJ_FALSE;

    if (!opj_stream_has_seek(p_stream)) {
        /* We can't do much in this case, seek is needed */
        return OPJ_TRUE;
    }

    l_stream_pos_backup = opj_stream_tell(p_stream);
    if (l_stream_pos_backup == -1) {
        /* let's do nothing */
        return OPJ_TRUE;
    }

    for (;;) {
        /* Try to read 2 bytes (the next marker ID) from stream and copy them into the buffer */
        if (opj_stream_read_data(p_stream, l_header_data, 2, p_manager) != 2) {
            /* assume all is OK */
            if (! opj_stream_seek(p_stream, l_stream_pos_backup, p_manager)) {
                return OPJ_FALSE;
            }
            return OPJ_TRUE;
        }

        /* Read 2 bytes from buffer as the new marker ID */
        opj_read_bytes(l_header_data, &l_current_marker, 2);

        if (l_current_marker != J2K_MS_SOT) {
            /* assume all is OK */
            if (! opj_stream_seek(p_stream, l_stream_pos_backup, p_manager)) {
                return OPJ_FALSE;
            }
            return OPJ_TRUE;
        }

        /* Try to read 2 bytes (the marker size) from stream and copy them into the buffer */
        if (opj_stream_read_data(p_stream, l_header_data, 2, p_manager) != 2) {
            opj_event_msg(p_manager, EVT_ERROR, "Stream too short\n");
            return OPJ_FALSE;
        }

        /* Read 2 bytes from the buffer as the marker size */
        opj_read_bytes(l_header_data, &l_marker_size, 2);

        /* Check marker size for SOT Marker */
        if (l_marker_size != 10) {
            opj_event_msg(p_manager, EVT_ERROR, "Inconsistent marker size\n");
            return OPJ_FALSE;
        }
        l_marker_size -= 2;

        if (opj_stream_read_data(p_stream, l_header_data, l_marker_size,
                                 p_manager) != l_marker_size) {
            opj_event_msg(p_manager, EVT_ERROR, "Stream too short\n");
            return OPJ_FALSE;
        }

        if (! opj_j2k_get_sot_values(l_header_data, l_marker_size, &l_tile_no,
                                     &l_tot_len, &l_current_part, &l_num_parts, p_manager)) {
            return OPJ_FALSE;
        }

        if (l_tile_no == tile_no) {
            /* we found what we were looking for */
            break;
        }

        if (l_tot_len < 14U) {
            /* last SOT until EOC or invalid Psot value */
            /* assume all is OK */
            if (! opj_stream_seek(p_stream, l_stream_pos_backup, p_manager)) {
                return OPJ_FALSE;
            }
            return OPJ_TRUE;
        }
        l_tot_len -= 12U;
        /* look for next SOT marker */
        if (opj_stream_skip(p_stream, (OPJ_OFF_T)(l_tot_len),
                            p_manager) != (OPJ_OFF_T)(l_tot_len)) {
            /* assume all is OK */
            if (! opj_stream_seek(p_stream, l_stream_pos_backup, p_manager)) {
                return OPJ_FALSE;
            }
            return OPJ_TRUE;
        }
    }

    /* check for correction */
    if (l_current_part == l_num_parts) {
        *p_correction_needed = OPJ_TRUE;
    }

    if (! opj_stream_seek(p_stream, l_stream_pos_backup, p_manager)) {
        return OPJ_FALSE;
    }
    return OPJ_TRUE;
}