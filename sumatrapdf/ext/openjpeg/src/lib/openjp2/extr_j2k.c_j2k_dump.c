#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tcp_t ;
struct TYPE_7__ {scalar_t__ th; scalar_t__ tw; int /*<<< orphan*/ * tcps; } ;
struct TYPE_8__ {TYPE_5__* m_private_image; TYPE_1__ m_cp; } ;
typedef  TYPE_2__ opj_j2k_t ;
struct TYPE_9__ {scalar_t__ numcomps; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int OPJ_INT32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int OPJ_IMG_INFO ; 
 int OPJ_J2K_MH_IND ; 
 int OPJ_J2K_MH_INFO ; 
 int OPJ_J2K_TCH_INFO ; 
 int OPJ_J2K_TH_IND ; 
 int OPJ_J2K_TH_INFO ; 
 int OPJ_JP2_IND ; 
 int OPJ_JP2_INFO ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  j2k_dump_image_header (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_j2k_dump_MH_index (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_j2k_dump_MH_info (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_j2k_dump_tile_info (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void j2k_dump(opj_j2k_t* p_j2k, OPJ_INT32 flag, FILE* out_stream)
{
    /* Check if the flag is compatible with j2k file*/
    if ((flag & OPJ_JP2_INFO) || (flag & OPJ_JP2_IND)) {
        fprintf(out_stream, "Wrong flag\n");
        return;
    }

    /* Dump the image_header */
    if (flag & OPJ_IMG_INFO) {
        if (p_j2k->m_private_image) {
            j2k_dump_image_header(p_j2k->m_private_image, 0, out_stream);
        }
    }

    /* Dump the codestream info from main header */
    if (flag & OPJ_J2K_MH_INFO) {
        if (p_j2k->m_private_image) {
            opj_j2k_dump_MH_info(p_j2k, out_stream);
        }
    }
    /* Dump all tile/codestream info */
    if (flag & OPJ_J2K_TCH_INFO) {
        OPJ_UINT32 l_nb_tiles = p_j2k->m_cp.th * p_j2k->m_cp.tw;
        OPJ_UINT32 i;
        opj_tcp_t * l_tcp = p_j2k->m_cp.tcps;
        if (p_j2k->m_private_image) {
            for (i = 0; i < l_nb_tiles; ++i) {
                opj_j2k_dump_tile_info(l_tcp, (OPJ_INT32)p_j2k->m_private_image->numcomps,
                                       out_stream);
                ++l_tcp;
            }
        }
    }

    /* Dump the codestream info of the current tile */
    if (flag & OPJ_J2K_TH_INFO) {

    }

    /* Dump the codestream index from main header */
    if (flag & OPJ_J2K_MH_IND) {
        opj_j2k_dump_MH_index(p_j2k, out_stream);
    }

    /* Dump the codestream index of the current tile */
    if (flag & OPJ_J2K_TH_IND) {

    }

}