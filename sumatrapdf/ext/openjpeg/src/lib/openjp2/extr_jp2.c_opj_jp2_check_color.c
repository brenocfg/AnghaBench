#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* jp2_pclr; TYPE_1__* jp2_cdef; } ;
typedef  TYPE_3__ opj_jp2_color_t ;
struct TYPE_12__ {unsigned int cmp; int mtyp; int pcol; } ;
typedef  TYPE_4__ opj_jp2_cmap_comp_t ;
struct TYPE_13__ {unsigned int cn; unsigned int asoc; } ;
typedef  TYPE_5__ opj_jp2_cdef_info_t ;
struct TYPE_14__ {unsigned int numcomps; } ;
typedef  TYPE_6__ opj_image_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_10__ {size_t nr_channels; TYPE_4__* cmap; } ;
struct TYPE_9__ {size_t n; TYPE_5__* info; } ;
typedef  unsigned int OPJ_UINT32 ;
typedef  size_t OPJ_UINT16 ;
typedef  int OPJ_BYTE ;
typedef  unsigned int OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_WARNING ; 
 unsigned int OPJ_FALSE ; 
 unsigned int OPJ_TRUE ; 
 scalar_t__ opj_calloc (size_t,int) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  opj_free (unsigned int*) ; 

__attribute__((used)) static OPJ_BOOL opj_jp2_check_color(opj_image_t *image, opj_jp2_color_t *color,
                                    opj_event_mgr_t *p_manager)
{
    OPJ_UINT16 i;

    /* testcase 4149.pdf.SIGSEGV.cf7.3501 */
    if (color->jp2_cdef) {
        opj_jp2_cdef_info_t *info = color->jp2_cdef->info;
        OPJ_UINT16 n = color->jp2_cdef->n;
        OPJ_UINT32 nr_channels =
            image->numcomps; /* FIXME image->numcomps == jp2->numcomps before color is applied ??? */

        /* cdef applies to cmap channels if any */
        if (color->jp2_pclr && color->jp2_pclr->cmap) {
            nr_channels = (OPJ_UINT32)color->jp2_pclr->nr_channels;
        }

        for (i = 0; i < n; i++) {
            if (info[i].cn >= nr_channels) {
                opj_event_msg(p_manager, EVT_ERROR, "Invalid component index %d (>= %d).\n",
                              info[i].cn, nr_channels);
                return OPJ_FALSE;
            }
            if (info[i].asoc == 65535U) {
                continue;
            }

            if (info[i].asoc > 0 && (OPJ_UINT32)(info[i].asoc - 1) >= nr_channels) {
                opj_event_msg(p_manager, EVT_ERROR, "Invalid component index %d (>= %d).\n",
                              info[i].asoc - 1, nr_channels);
                return OPJ_FALSE;
            }
        }

        /* issue 397 */
        /* ISO 15444-1 states that if cdef is present, it shall contain a complete list of channel definitions. */
        while (nr_channels > 0) {
            for (i = 0; i < n; ++i) {
                if ((OPJ_UINT32)info[i].cn == (nr_channels - 1U)) {
                    break;
                }
            }
            if (i == n) {
                opj_event_msg(p_manager, EVT_ERROR, "Incomplete channel definitions.\n");
                return OPJ_FALSE;
            }
            --nr_channels;
        }
    }

    /* testcases 451.pdf.SIGSEGV.f4c.3723, 451.pdf.SIGSEGV.5b5.3723 and
       66ea31acbb0f23a2bbc91f64d69a03f5_signal_sigsegv_13937c0_7030_5725.pdf */
    if (color->jp2_pclr && color->jp2_pclr->cmap) {
        OPJ_UINT16 nr_channels = color->jp2_pclr->nr_channels;
        opj_jp2_cmap_comp_t *cmap = color->jp2_pclr->cmap;
        OPJ_BOOL *pcol_usage, is_sane = OPJ_TRUE;

        /* verify that all original components match an existing one */
        for (i = 0; i < nr_channels; i++) {
            if (cmap[i].cmp >= image->numcomps) {
                opj_event_msg(p_manager, EVT_ERROR, "Invalid component index %d (>= %d).\n",
                              cmap[i].cmp, image->numcomps);
                is_sane = OPJ_FALSE;
            }
        }

        pcol_usage = (OPJ_BOOL *) opj_calloc(nr_channels, sizeof(OPJ_BOOL));
        if (!pcol_usage) {
            opj_event_msg(p_manager, EVT_ERROR, "Unexpected OOM.\n");
            return OPJ_FALSE;
        }
        /* verify that no component is targeted more than once */
        for (i = 0; i < nr_channels; i++) {
            OPJ_BYTE mtyp = cmap[i].mtyp;
            OPJ_BYTE pcol = cmap[i].pcol;
            /* See ISO 15444-1 Table I.14 – MTYPi field values */
            if (mtyp != 0 && mtyp != 1) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Invalid value for cmap[%d].mtyp = %d.\n", i,
                              mtyp);
                is_sane = OPJ_FALSE;
            } else if (pcol >= nr_channels) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Invalid component/palette index for direct mapping %d.\n", pcol);
                is_sane = OPJ_FALSE;
            } else if (pcol_usage[pcol] && mtyp == 1) {
                opj_event_msg(p_manager, EVT_ERROR, "Component %d is mapped twice.\n", pcol);
                is_sane = OPJ_FALSE;
            } else if (mtyp == 0 && pcol != 0) {
                /* I.5.3.5 PCOL: If the value of the MTYP field for this channel is 0, then
                 * the value of this field shall be 0. */
                opj_event_msg(p_manager, EVT_ERROR, "Direct use at #%d however pcol=%d.\n", i,
                              pcol);
                is_sane = OPJ_FALSE;
            } else if (mtyp == 1 && pcol != i) {
                /* OpenJPEG implementation limitation. See assert(i == pcol); */
                /* in opj_jp2_apply_pclr() */
                opj_event_msg(p_manager, EVT_ERROR,
                              "Implementation limitation: for palette mapping, "
                              "pcol[%d] should be equal to %d, but is equal "
                              "to %d.\n", i, i, pcol);
                is_sane = OPJ_FALSE;
            } else {
                pcol_usage[pcol] = OPJ_TRUE;
            }
        }
        /* verify that all components are targeted at least once */
        for (i = 0; i < nr_channels; i++) {
            if (!pcol_usage[i] && cmap[i].mtyp != 0) {
                opj_event_msg(p_manager, EVT_ERROR, "Component %d doesn't have a mapping.\n",
                              i);
                is_sane = OPJ_FALSE;
            }
        }
        /* Issue 235/447 weird cmap */
        if (1 && is_sane && (image->numcomps == 1U)) {
            for (i = 0; i < nr_channels; i++) {
                if (!pcol_usage[i]) {
                    is_sane = 0U;
                    opj_event_msg(p_manager, EVT_WARNING,
                                  "Component mapping seems wrong. Trying to correct.\n", i);
                    break;
                }
            }
            if (!is_sane) {
                is_sane = OPJ_TRUE;
                for (i = 0; i < nr_channels; i++) {
                    cmap[i].mtyp = 1U;
                    cmap[i].pcol = (OPJ_BYTE) i;
                }
            }
        }
        opj_free(pcol_usage);
        if (!is_sane) {
            return OPJ_FALSE;
        }
    }

    return OPJ_TRUE;
}