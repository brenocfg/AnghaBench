#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  m_default_tcp; } ;
struct TYPE_9__ {TYPE_2__ m_decoder; } ;
struct TYPE_7__ {int tx0; int ty0; int tdx; int tdy; int tw; int th; } ;
struct TYPE_11__ {TYPE_4__* m_private_image; TYPE_3__ m_specific_param; TYPE_1__ m_cp; } ;
typedef  TYPE_5__ opj_j2k_t ;
struct TYPE_10__ {scalar_t__ numcomps; } ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  opj_j2k_dump_tile_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void opj_j2k_dump_MH_info(opj_j2k_t* p_j2k, FILE* out_stream)
{

    fprintf(out_stream, "Codestream info from main header: {\n");

    fprintf(out_stream, "\t tx0=%d, ty0=%d\n", p_j2k->m_cp.tx0, p_j2k->m_cp.ty0);
    fprintf(out_stream, "\t tdx=%d, tdy=%d\n", p_j2k->m_cp.tdx, p_j2k->m_cp.tdy);
    fprintf(out_stream, "\t tw=%d, th=%d\n", p_j2k->m_cp.tw, p_j2k->m_cp.th);
    opj_j2k_dump_tile_info(p_j2k->m_specific_param.m_decoder.m_default_tcp,
                           (OPJ_INT32)p_j2k->m_private_image->numcomps, out_stream);
    fprintf(out_stream, "}\n");
}