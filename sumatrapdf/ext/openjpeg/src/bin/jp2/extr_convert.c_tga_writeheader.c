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
typedef  unsigned char OPJ_UINT16 ;
typedef  scalar_t__ OPJ_BOOL ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned char swap16 (unsigned char) ; 

__attribute__((used)) static int tga_writeheader(FILE *fp, int bits_per_pixel, int width, int height,
                           OPJ_BOOL flip_image)
{
    OPJ_UINT16 image_w, image_h, us0;
    unsigned char uc0, image_type;
    unsigned char pixel_depth, image_desc;

    if (!bits_per_pixel || !width || !height) {
        return 0;
    }

    pixel_depth = 0;

    if (bits_per_pixel < 256) {
        pixel_depth = (unsigned char)bits_per_pixel;
    } else {
        fprintf(stderr, "ERROR: Wrong bits per pixel inside tga_header");
        return 0;
    }
    uc0 = 0;

    if (fwrite(&uc0, 1, 1, fp) != 1) {
        goto fails;    /* id_length */
    }
    if (fwrite(&uc0, 1, 1, fp) != 1) {
        goto fails;    /* colour_map_type */
    }

    image_type = 2; /* Uncompressed. */
    if (fwrite(&image_type, 1, 1, fp) != 1) {
        goto fails;
    }

    us0 = 0;
    if (fwrite(&us0, 2, 1, fp) != 1) {
        goto fails;    /* colour_map_index */
    }
    if (fwrite(&us0, 2, 1, fp) != 1) {
        goto fails;    /* colour_map_length */
    }
    if (fwrite(&uc0, 1, 1, fp) != 1) {
        goto fails;    /* colour_map_entry_size */
    }

    if (fwrite(&us0, 2, 1, fp) != 1) {
        goto fails;    /* x_origin */
    }
    if (fwrite(&us0, 2, 1, fp) != 1) {
        goto fails;    /* y_origin */
    }

    image_w = (unsigned short)width;
    image_h = (unsigned short) height;

#ifndef OPJ_BIG_ENDIAN
    if (fwrite(&image_w, 2, 1, fp) != 1) {
        goto fails;
    }
    if (fwrite(&image_h, 2, 1, fp) != 1) {
        goto fails;
    }
#else
    image_w = swap16(image_w);
    image_h = swap16(image_h);
    if (fwrite(&image_w, 2, 1, fp) != 1) {
        goto fails;
    }
    if (fwrite(&image_h, 2, 1, fp) != 1) {
        goto fails;
    }
#endif

    if (fwrite(&pixel_depth, 1, 1, fp) != 1) {
        goto fails;
    }

    image_desc = 8; /* 8 bits per component. */

    if (flip_image) {
        image_desc |= 32;
    }
    if (fwrite(&image_desc, 1, 1, fp) != 1) {
        goto fails;
    }

    return 1;

fails:
    fputs("\nwrite_tgaheader: write ERROR\n", stderr);
    return 0;
}