#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  png_voidp ;
typedef  int /*<<< orphan*/ * png_structp ;
typedef  int /*<<< orphan*/ ** png_infopp ;
typedef  int /*<<< orphan*/ * png_infop ;
typedef  scalar_t__ png_bytep ;
struct TYPE_3__ {scalar_t__ height; scalar_t__ stride; scalar_t__ data; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ Jbig2Image ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_COLOR_TYPE_GRAY ; 
 int /*<<< orphan*/  PNG_COMPRESSION_TYPE_DEFAULT ; 
 int /*<<< orphan*/  PNG_FILTER_TYPE_DEFAULT ; 
 int /*<<< orphan*/  PNG_INTERLACE_NONE ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jbig2_png_flush ; 
 int /*<<< orphan*/  jbig2_png_write_data ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_write_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_destroy_write_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  png_jmpbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_IHDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_invert_mono (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_write_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_write_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_write_row (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
jbig2_image_write_png(Jbig2Image *image, FILE *out)
{
    uint32_t i;
    png_structp png;
    png_infop info;
    png_bytep rowpointer;

    png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png == NULL) {
        fprintf(stderr, "unable to create png structure\n");
        return 2;
    }

    info = png_create_info_struct(png);
    if (info == NULL) {
        fprintf(stderr, "unable to create png info structure\n");
        png_destroy_write_struct(&png, (png_infopp) NULL);
        return 3;
    }

    /* set/check error handling */
    if (setjmp(png_jmpbuf(png))) {
        /* we've returned here after an internal error */
        fprintf(stderr, "internal error in libpng saving file\n");
        png_destroy_write_struct(&png, &info);
        return 4;
    }

    /* png_init_io() doesn't work linking dynamically to libpng on win32
       one has to either link statically or use callbacks because of runtime
       variations */
    /* png_init_io(png, out); */
    png_set_write_fn(png, (png_voidp) out, jbig2_png_write_data, jbig2_png_flush);

    /* now we fill out the info structure with our format data */
    png_set_IHDR(png, info, image->width, image->height, 1, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    /* png natively treats 0 as black. This will convert for us */
    png_set_invert_mono(png);

    /* write out each row in turn */
    rowpointer = (png_bytep) image->data;
    for (i = 0; i < image->height; i++) {
        png_write_row(png, rowpointer);
        rowpointer += image->stride;
    }

    /* finish and clean up */
    png_write_end(png, info);
    png_destroy_write_struct(&png, &info);

    return 0;
}