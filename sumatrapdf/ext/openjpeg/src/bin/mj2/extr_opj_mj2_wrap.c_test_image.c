#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int numcomps; scalar_t__ color_space; unsigned char* icc_profile_buf; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
typedef  int /*<<< orphan*/  opj_dparameters_t ;
typedef  int /*<<< orphan*/  opj_dinfo_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
struct TYPE_13__ {int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_3__ opj_cio_t ;
struct TYPE_14__ {int numcomps; int CbCr_subsampling_dx; int CbCr_subsampling_dy; int meth; void* enumcs; int /*<<< orphan*/  prec; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_4__ mj2_cparameters_t ;
struct TYPE_11__ {int dx; int dy; int /*<<< orphan*/  prec; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CLRSPC_SRGB ; 
 int /*<<< orphan*/  CODEC_J2K ; 
 void* ENUMCS_GRAY ; 
 void* ENUMCS_SRGB ; 
 void* ENUMCS_SYCC ; 
 int /*<<< orphan*/  J2K_CODESTREAM_MAGIC ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (long) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_cio_close (TYPE_3__*) ; 
 TYPE_3__* opj_cio_open (int /*<<< orphan*/ ,unsigned char*,long) ; 
 int /*<<< orphan*/ * opj_create_decompress (int /*<<< orphan*/ ) ; 
 TYPE_2__* opj_decode (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  opj_destroy_decompress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_image_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  opj_set_default_decoder_parameters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_setup_decoder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_image(const char *fname, mj2_cparameters_t *cp)
{
    FILE *reader;
    opj_image_t *image;
    unsigned char *src;
    opj_dinfo_t *dinfo;
    opj_cio_t *cio;
    opj_dparameters_t dparameters;
    int success;
    long src_len;

    success = 0;

    if ((reader = fopen(fname, "rb")) == NULL) {
        return success;
    }

    fseek(reader, 0, SEEK_END);
    src_len = ftell(reader);
    fseek(reader, 0, SEEK_SET);
    src = (unsigned char*) malloc(src_len);
    fread(src, 1, src_len, reader);
    fclose(reader);

    if (memcmp(src, J2K_CODESTREAM_MAGIC, 4) != 0) {
        free(src);
        return success;
    }
    memset(&dparameters, 0, sizeof(opj_dparameters_t));

    opj_set_default_decoder_parameters(&dparameters);

    dinfo = opj_create_decompress(CODEC_J2K);

    opj_setup_decoder(dinfo, &dparameters);

    cio = opj_cio_open((opj_common_ptr)dinfo, src, src_len);

    image = opj_decode(dinfo, cio);

    free(src);
    cio->buffer = NULL;
    opj_cio_close(cio);

    if (image == NULL) {
        goto fin;
    }

    cp->numcomps = image->numcomps;
    cp->w = image->comps[0].w;
    cp->h = image->comps[0].h;
    cp->prec = image->comps[0].prec;

    if (image->numcomps > 2) {
        if ((image->comps[0].dx == 1)
                && (image->comps[1].dx == 2)
                && (image->comps[2].dx == 2)
                && (image->comps[0].dy == 1)
                && (image->comps[1].dy == 2)
                && (image->comps[2].dy == 2)) { /* horizontal and vertical*/
            /*   Y420*/
            cp->enumcs = ENUMCS_SYCC;
            cp->CbCr_subsampling_dx = 2;
            cp->CbCr_subsampling_dy = 2;
        } else if ((image->comps[0].dx == 1)
                   && (image->comps[1].dx == 2)
                   && (image->comps[2].dx == 2)
                   && (image->comps[0].dy == 1)
                   && (image->comps[1].dy == 1)
                   && (image->comps[2].dy == 1)) { /* horizontal only*/
            /*   Y422*/
            cp->enumcs = ENUMCS_SYCC;
            cp->CbCr_subsampling_dx = 2;
            cp->CbCr_subsampling_dy = 1;
        } else if ((image->comps[0].dx == 1)
                   && (image->comps[1].dx == 1)
                   && (image->comps[2].dx == 1)
                   && (image->comps[0].dy == 1)
                   && (image->comps[1].dy == 1)
                   && (image->comps[2].dy == 1)) {
            /*   Y444 or RGB */

            if (image->color_space ==  CLRSPC_SRGB) {
                cp->enumcs = ENUMCS_SRGB;

                /*    cp->CbCr_subsampling_dx = 0; */
                /*    cp->CbCr_subsampling_dy = 0; */
            } else {
                cp->enumcs = ENUMCS_SYCC;

                cp->CbCr_subsampling_dx = 1;
                cp->CbCr_subsampling_dy = 1;
            }
        } else {
            goto fin;
        }
    } else {
        cp->enumcs = ENUMCS_GRAY;
        /*  cp->CbCr_subsampling_dx = 0; */
        /*  cp->CbCr_subsampling_dy = 0; */
    }
    if (image->icc_profile_buf) {
        cp->meth = 2;
        free(image->icc_profile_buf);
        image->icc_profile_buf = NULL;
    } else {
        cp->meth = 1;
    }

    success = 1;
fin:
    if (dinfo) {
        opj_destroy_decompress(dinfo);
    }

    if (image) {
        opj_image_destroy(image);
    }

    return success;
}