#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* jp2_cdef; } ;
struct TYPE_16__ {int numcl; int* cl; int numcomps; int bpc; int C; int meth; int enumcs; int /*<<< orphan*/  jpip_on; scalar_t__ approx; scalar_t__ precedence; TYPE_1__ color; TYPE_4__* comps; scalar_t__ IPR; scalar_t__ UnkC; scalar_t__ w; scalar_t__ h; scalar_t__ minversion; void* brand; int /*<<< orphan*/  j2k; } ;
typedef  TYPE_3__ opj_jp2_t ;
struct TYPE_17__ {int bpcc; } ;
typedef  TYPE_4__ opj_jp2_comps_t ;
struct TYPE_18__ {TYPE_6__* info; void* n; } ;
typedef  TYPE_5__ opj_jp2_cdef_t ;
struct TYPE_19__ {unsigned int typ; unsigned int asoc; void* cn; } ;
typedef  TYPE_6__ opj_jp2_cdef_info_t ;
struct TYPE_20__ {int numcomps; int color_space; TYPE_2__* comps; scalar_t__ icc_profile_len; scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; scalar_t__ y1; } ;
typedef  TYPE_7__ opj_image_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_21__ {int /*<<< orphan*/  jpip_on; } ;
typedef  TYPE_8__ opj_cparameters_t ;
struct TYPE_15__ {int prec; int sgnd; scalar_t__ alpha; } ;
typedef  int OPJ_UINT32 ;
typedef  void* OPJ_UINT16 ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_WARNING ; 
 void* JP2_JP2 ; 
 scalar_t__ OPJ_FALSE ; 
 scalar_t__ OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ opj_j2k_setup_encoder (int /*<<< orphan*/ ,TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 scalar_t__ opj_malloc (int) ; 

OPJ_BOOL opj_jp2_setup_encoder(opj_jp2_t *jp2,
                               opj_cparameters_t *parameters,
                               opj_image_t *image,
                               opj_event_mgr_t * p_manager)
{
    OPJ_UINT32 i;
    OPJ_UINT32 depth_0;
    OPJ_UINT32 sign;
    OPJ_UINT32 alpha_count;
    OPJ_UINT32 color_channels = 0U;
    OPJ_UINT32 alpha_channel = 0U;


    if (!jp2 || !parameters || !image) {
        return OPJ_FALSE;
    }

    /* setup the J2K codec */
    /* ------------------- */

    /* Check if number of components respects standard */
    if (image->numcomps < 1 || image->numcomps > 16384) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Invalid number of components specified while setting up JP2 encoder\n");
        return OPJ_FALSE;
    }

    if (opj_j2k_setup_encoder(jp2->j2k, parameters, image,
                              p_manager) == OPJ_FALSE) {
        return OPJ_FALSE;
    }

    /* setup the JP2 codec */
    /* ------------------- */

    /* Profile box */

    jp2->brand = JP2_JP2;   /* BR */
    jp2->minversion = 0;    /* MinV */
    jp2->numcl = 1;
    jp2->cl = (OPJ_UINT32*) opj_malloc(jp2->numcl * sizeof(OPJ_UINT32));
    if (!jp2->cl) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Not enough memory when setup the JP2 encoder\n");
        return OPJ_FALSE;
    }
    jp2->cl[0] = JP2_JP2;   /* CL0 : JP2 */

    /* Image Header box */

    jp2->numcomps = image->numcomps;    /* NC */
    jp2->comps = (opj_jp2_comps_t*) opj_malloc(jp2->numcomps * sizeof(
                     opj_jp2_comps_t));
    if (!jp2->comps) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Not enough memory when setup the JP2 encoder\n");
        /* Memory of jp2->cl will be freed by opj_jp2_destroy */
        return OPJ_FALSE;
    }

    jp2->h = image->y1 - image->y0;     /* HEIGHT */
    jp2->w = image->x1 - image->x0;     /* WIDTH */
    /* BPC */
    depth_0 = image->comps[0].prec - 1;
    sign = image->comps[0].sgnd;
    jp2->bpc = depth_0 + (sign << 7);
    for (i = 1; i < image->numcomps; i++) {
        OPJ_UINT32 depth = image->comps[i].prec - 1;
        sign = image->comps[i].sgnd;
        if (depth_0 != depth) {
            jp2->bpc = 255;
        }
    }
    jp2->C = 7;         /* C : Always 7 */
    jp2->UnkC = 0;      /* UnkC, colorspace specified in colr box */
    jp2->IPR = 0;       /* IPR, no intellectual property */

    /* BitsPerComponent box */
    for (i = 0; i < image->numcomps; i++) {
        jp2->comps[i].bpcc = image->comps[i].prec - 1 + (image->comps[i].sgnd << 7);
    }

    /* Colour Specification box */
    if (image->icc_profile_len) {
        jp2->meth = 2;
        jp2->enumcs = 0;
    } else {
        jp2->meth = 1;
        if (image->color_space == 1) {
            jp2->enumcs = 16;    /* sRGB as defined by IEC 61966-2-1 */
        } else if (image->color_space == 2) {
            jp2->enumcs = 17;    /* greyscale */
        } else if (image->color_space == 3) {
            jp2->enumcs = 18;    /* YUV */
        }
    }

    /* Channel Definition box */
    /* FIXME not provided by parameters */
    /* We try to do what we can... */
    alpha_count = 0U;
    for (i = 0; i < image->numcomps; i++) {
        if (image->comps[i].alpha != 0) {
            alpha_count++;
            alpha_channel = i;
        }
    }
    if (alpha_count == 1U) { /* no way to deal with more than 1 alpha channel */
        switch (jp2->enumcs) {
        case 16:
        case 18:
            color_channels = 3;
            break;
        case 17:
            color_channels = 1;
            break;
        default:
            alpha_count = 0U;
            break;
        }
        if (alpha_count == 0U) {
            opj_event_msg(p_manager, EVT_WARNING,
                          "Alpha channel specified but unknown enumcs. No cdef box will be created.\n");
        } else if (image->numcomps < (color_channels + 1)) {
            opj_event_msg(p_manager, EVT_WARNING,
                          "Alpha channel specified but not enough image components for an automatic cdef box creation.\n");
            alpha_count = 0U;
        } else if ((OPJ_UINT32)alpha_channel < color_channels) {
            opj_event_msg(p_manager, EVT_WARNING,
                          "Alpha channel position conflicts with color channel. No cdef box will be created.\n");
            alpha_count = 0U;
        }
    } else if (alpha_count > 1) {
        opj_event_msg(p_manager, EVT_WARNING,
                      "Multiple alpha channels specified. No cdef box will be created.\n");
    }
    if (alpha_count == 1U) { /* if here, we know what we can do */
        jp2->color.jp2_cdef = (opj_jp2_cdef_t*)opj_malloc(sizeof(opj_jp2_cdef_t));
        if (!jp2->color.jp2_cdef) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "Not enough memory to setup the JP2 encoder\n");
            return OPJ_FALSE;
        }
        /* no memset needed, all values will be overwritten except if jp2->color.jp2_cdef->info allocation fails, */
        /* in which case jp2->color.jp2_cdef->info will be NULL => valid for destruction */
        jp2->color.jp2_cdef->info = (opj_jp2_cdef_info_t*) opj_malloc(
                                        image->numcomps * sizeof(opj_jp2_cdef_info_t));
        if (!jp2->color.jp2_cdef->info) {
            /* memory will be freed by opj_jp2_destroy */
            opj_event_msg(p_manager, EVT_ERROR,
                          "Not enough memory to setup the JP2 encoder\n");
            return OPJ_FALSE;
        }
        jp2->color.jp2_cdef->n = (OPJ_UINT16)
                                 image->numcomps; /* cast is valid : image->numcomps [1,16384] */
        for (i = 0U; i < color_channels; i++) {
            jp2->color.jp2_cdef->info[i].cn = (OPJ_UINT16)
                                              i; /* cast is valid : image->numcomps [1,16384] */
            jp2->color.jp2_cdef->info[i].typ = 0U;
            jp2->color.jp2_cdef->info[i].asoc = (OPJ_UINT16)(i +
                                                1U); /* No overflow + cast is valid : image->numcomps [1,16384] */
        }
        for (; i < image->numcomps; i++) {
            if (image->comps[i].alpha != 0) { /* we'll be here exactly once */
                jp2->color.jp2_cdef->info[i].cn = (OPJ_UINT16)
                                                  i; /* cast is valid : image->numcomps [1,16384] */
                jp2->color.jp2_cdef->info[i].typ = 1U; /* Opacity channel */
                jp2->color.jp2_cdef->info[i].asoc =
                    0U; /* Apply alpha channel to the whole image */
            } else {
                /* Unknown channel */
                jp2->color.jp2_cdef->info[i].cn = (OPJ_UINT16)
                                                  i; /* cast is valid : image->numcomps [1,16384] */
                jp2->color.jp2_cdef->info[i].typ = 65535U;
                jp2->color.jp2_cdef->info[i].asoc = 65535U;
            }
        }
    }

    jp2->precedence = 0;    /* PRECEDENCE */
    jp2->approx = 0;        /* APPROX */

    jp2->jpip_on = parameters->jpip_on;

    return OPJ_TRUE;
}