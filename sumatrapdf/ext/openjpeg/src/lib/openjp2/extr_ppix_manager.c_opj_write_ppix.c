#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_stream_private_t ;
struct TYPE_7__ {int length; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_8__ {int numcomps; } ;
typedef  TYPE_2__ opj_codestream_info_t ;
typedef  int OPJ_UINT32 ;
typedef  int OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  JPIP_FAIX ; 
 int JPIP_PPIX ; 
 scalar_t__ opj_calloc (size_t,int) ; 
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 
 int /*<<< orphan*/  opj_stream_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_skip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int opj_stream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_write_bytes (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  opj_write_manf (int,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ opj_write_ppixfaix (int,int,TYPE_2__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int opj_write_ppix(int coff, opj_codestream_info_t cstr_info, OPJ_BOOL EPHused,
                   int j2klen, opj_stream_private_t *cio,
                   opj_event_mgr_t * p_manager)
{
    OPJ_BYTE l_data_header [4];
    int compno, i;
    opj_jp2_box_t *box;
    OPJ_OFF_T lenp;
    OPJ_UINT32 len;

    /*  printf("cstr_info.packno %d\n", cstr_info.packno); //NMAX? */

    lenp = -1;
    box = (opj_jp2_box_t *)opj_calloc((size_t)cstr_info.numcomps,
                                      sizeof(opj_jp2_box_t));
    if (box == NULL) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        if (i)

        {
            opj_stream_seek(cio, lenp, p_manager);
        }

        lenp = (OPJ_UINT32)(opj_stream_tell(cio));
        opj_stream_skip(cio, 4, p_manager);        /* L [at the end] */
        opj_write_bytes(l_data_header, JPIP_PPIX, 4); /* PPIX           */
        opj_stream_write_data(cio, l_data_header, 4, p_manager);

        opj_write_manf(i, cstr_info.numcomps, box, cio, p_manager);

        for (compno = 0; compno < cstr_info.numcomps; compno++) {
            box[compno].length = (OPJ_UINT32)opj_write_ppixfaix(coff, compno, cstr_info,
                                 EPHused, j2klen, cio, p_manager);
            box[compno].type = JPIP_FAIX;
        }


        len = (OPJ_UINT32)(opj_stream_tell(cio) - lenp);
        opj_stream_seek(cio, lenp, p_manager);
        opj_write_bytes(l_data_header, len, 4); /* L              */
        opj_stream_write_data(cio, l_data_header, 4, p_manager);
        opj_stream_seek(cio, lenp + len, p_manager);
    }

    opj_free(box);

    return (int)len;
}