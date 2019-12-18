#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {int m_numcomps_to_decode; size_t* m_comps_indices_to_decode; } ;
struct TYPE_14__ {TYPE_1__ m_decoder; } ;
struct TYPE_16__ {TYPE_3__* m_output_image; TYPE_2__ m_specific_param; int /*<<< orphan*/ * m_private_image; } ;
typedef  TYPE_4__ opj_j2k_t ;
struct TYPE_17__ {size_t numcomps; TYPE_6__* comps; } ;
typedef  TYPE_5__ opj_image_t ;
struct TYPE_18__ {int w; int h; int /*<<< orphan*/ * data; int /*<<< orphan*/  resno_decoded; } ;
typedef  TYPE_6__ opj_image_comp_t ;
struct TYPE_15__ {TYPE_11__* comps; } ;
struct TYPE_12__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  resno_decoded; } ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_11__*,int) ; 
 int /*<<< orphan*/  opj_free (TYPE_6__*) ; 
 int /*<<< orphan*/  opj_image_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_image_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ opj_malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,size_t) ; 

__attribute__((used)) static OPJ_BOOL opj_j2k_move_data_from_codec_to_output_image(opj_j2k_t * p_j2k,
        opj_image_t * p_image)
{
    OPJ_UINT32 compno;

    /* Move data and copy one information from codec to output image*/
    if (p_j2k->m_specific_param.m_decoder.m_numcomps_to_decode > 0) {
        opj_image_comp_t* newcomps =
            (opj_image_comp_t*) opj_malloc(
                p_j2k->m_specific_param.m_decoder.m_numcomps_to_decode *
                sizeof(opj_image_comp_t));
        if (newcomps == NULL) {
            opj_image_destroy(p_j2k->m_private_image);
            p_j2k->m_private_image = NULL;
            return OPJ_FALSE;
        }
        for (compno = 0; compno < p_image->numcomps; compno++) {
            opj_image_data_free(p_image->comps[compno].data);
            p_image->comps[compno].data = NULL;
        }
        for (compno = 0;
                compno < p_j2k->m_specific_param.m_decoder.m_numcomps_to_decode; compno++) {
            OPJ_UINT32 src_compno =
                p_j2k->m_specific_param.m_decoder.m_comps_indices_to_decode[compno];
            memcpy(&(newcomps[compno]),
                   &(p_j2k->m_output_image->comps[src_compno]),
                   sizeof(opj_image_comp_t));
            newcomps[compno].resno_decoded =
                p_j2k->m_output_image->comps[src_compno].resno_decoded;
            newcomps[compno].data = p_j2k->m_output_image->comps[src_compno].data;
            p_j2k->m_output_image->comps[src_compno].data = NULL;
        }
        for (compno = 0; compno < p_image->numcomps; compno++) {
            assert(p_j2k->m_output_image->comps[compno].data == NULL);
            opj_image_data_free(p_j2k->m_output_image->comps[compno].data);
            p_j2k->m_output_image->comps[compno].data = NULL;
        }
        p_image->numcomps = p_j2k->m_specific_param.m_decoder.m_numcomps_to_decode;
        opj_free(p_image->comps);
        p_image->comps = newcomps;
    } else {
        for (compno = 0; compno < p_image->numcomps; compno++) {
            p_image->comps[compno].resno_decoded =
                p_j2k->m_output_image->comps[compno].resno_decoded;
            opj_image_data_free(p_image->comps[compno].data);
            p_image->comps[compno].data = p_j2k->m_output_image->comps[compno].data;
#if 0
            char fn[256];
            sprintf(fn, "/tmp/%d.raw", compno);
            FILE *debug = fopen(fn, "wb");
            fwrite(p_image->comps[compno].data, sizeof(OPJ_INT32),
                   p_image->comps[compno].w * p_image->comps[compno].h, debug);
            fclose(debug);
#endif
            p_j2k->m_output_image->comps[compno].data = NULL;
        }
    }
    return OPJ_TRUE;
}