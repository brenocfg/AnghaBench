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
struct TYPE_12__ {unsigned int x0; unsigned int y0; unsigned int x1; unsigned int y1; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_13__ {int prec; int bpp; int dx; int dy; unsigned int w; unsigned int h; scalar_t__ sgnd; } ;
typedef  TYPE_3__ opj_image_cmptparm_t ;
struct TYPE_14__ {int subsampling_dx; int subsampling_dy; unsigned int image_offset_x0; unsigned int image_offset_y0; } ;
typedef  TYPE_4__ opj_cparameters_t ;
typedef  int opj_bool ;
struct TYPE_11__ {unsigned char* data; } ;
typedef  int /*<<< orphan*/  OPJ_COLOR_SPACE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CLRSPC_GRAY ; 
 int /*<<< orphan*/  CLRSPC_SRGB ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* opj_image_create (int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_image_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tga_readheader (int /*<<< orphan*/ *,unsigned int*,unsigned int*,unsigned int*,int*) ; 

opj_image_t* tgatoimage(const char *filename, opj_cparameters_t *parameters)
{
    FILE *f;
    opj_image_t *image;
    unsigned int image_width, image_height, pixel_bit_depth;
    unsigned int x, y;
    int flip_image = 0;
    opj_image_cmptparm_t cmptparm[4];   /* maximum 4 components */
    int numcomps;
    OPJ_COLOR_SPACE color_space;
    opj_bool mono ;
    opj_bool save_alpha;
    int subsampling_dx, subsampling_dy;
    int i;

    f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Failed to open %s for reading !!\n", filename);
        return 0;
    }

    if (!tga_readheader(f, &pixel_bit_depth, &image_width, &image_height,
                        &flip_image)) {
        return NULL;
    }

    /* We currently only support 24 & 32 bit tga's ... */
    if (!((pixel_bit_depth == 24) || (pixel_bit_depth == 32))) {
        return NULL;
    }

    /* initialize image components */
    memset(&cmptparm[0], 0, 4 * sizeof(opj_image_cmptparm_t));

    mono = (pixel_bit_depth == 8) ||
           (pixel_bit_depth == 16);  /* Mono with & without alpha. */
    save_alpha = (pixel_bit_depth == 16) ||
                 (pixel_bit_depth == 32); /* Mono with alpha, or RGB with alpha */

    if (mono) {
        color_space = CLRSPC_GRAY;
        numcomps = save_alpha ? 2 : 1;
    } else {
        numcomps = save_alpha ? 4 : 3;
        color_space = CLRSPC_SRGB;
    }

    subsampling_dx = parameters->subsampling_dx;
    subsampling_dy = parameters->subsampling_dy;

    for (i = 0; i < numcomps; i++) {
        cmptparm[i].prec = 8;
        cmptparm[i].bpp = 8;
        cmptparm[i].sgnd = 0;
        cmptparm[i].dx = subsampling_dx;
        cmptparm[i].dy = subsampling_dy;
        cmptparm[i].w = image_width;
        cmptparm[i].h = image_height;
    }

    /* create the image */
    image = opj_image_create(numcomps, &cmptparm[0], color_space);

    if (!image) {
        return NULL;
    }

    /* set image offset and reference grid */
    image->x0 = parameters->image_offset_x0;
    image->y0 = parameters->image_offset_y0;
    image->x1 = !image->x0 ? (image_width - 1) * subsampling_dx + 1 : image->x0 +
                (image_width - 1) * subsampling_dx + 1;
    image->y1 = !image->y0 ? (image_height - 1) * subsampling_dy + 1 : image->y0 +
                (image_height - 1) * subsampling_dy + 1;

    /* set image data */
    for (y = 0; y < image_height; y++) {
        int index;

        if (flip_image) {
            index = (image_height - y - 1) * image_width;
        } else {
            index = y * image_width;
        }

        if (numcomps == 3) {
            for (x = 0; x < image_width; x++) {
                unsigned char r, g, b;

                if (!fread(&b, 1, 1, f)) {
                    fprintf(stderr,
                            "\nError: fread return a number of element different from the expected.\n");
                    opj_image_destroy(image);
                    return NULL;
                }
                if (!fread(&g, 1, 1, f)) {
                    fprintf(stderr,
                            "\nError: fread return a number of element different from the expected.\n");
                    opj_image_destroy(image);
                    return NULL;
                }
                if (!fread(&r, 1, 1, f)) {
                    fprintf(stderr,
                            "\nError: fread return a number of element different from the expected.\n");
                    opj_image_destroy(image);
                    return NULL;
                }

                image->comps[0].data[index] = r;
                image->comps[1].data[index] = g;
                image->comps[2].data[index] = b;
                index++;
            }
        } else if (numcomps == 4) {
            for (x = 0; x < image_width; x++) {
                unsigned char r, g, b, a;
                if (!fread(&b, 1, 1, f)) {
                    fprintf(stderr,
                            "\nError: fread return a number of element different from the expected.\n");
                    opj_image_destroy(image);
                    return NULL;
                }
                if (!fread(&g, 1, 1, f)) {
                    fprintf(stderr,
                            "\nError: fread return a number of element different from the expected.\n");
                    opj_image_destroy(image);
                    return NULL;
                }
                if (!fread(&r, 1, 1, f)) {
                    fprintf(stderr,
                            "\nError: fread return a number of element different from the expected.\n");
                    opj_image_destroy(image);
                    return NULL;
                }
                if (!fread(&a, 1, 1, f)) {
                    fprintf(stderr,
                            "\nError: fread return a number of element different from the expected.\n");
                    opj_image_destroy(image);
                    return NULL;
                }

                image->comps[0].data[index] = r;
                image->comps[1].data[index] = g;
                image->comps[2].data[index] = b;
                image->comps[3].data[index] = a;
                index++;
            }
        } else {
            fprintf(stderr, "Currently unsupported bit depth : %s\n", filename);
        }
    }
    return image;
}