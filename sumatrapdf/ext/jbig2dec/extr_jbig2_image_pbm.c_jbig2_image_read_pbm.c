#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int height; int stride; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ Jbig2Image ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (int) ; 
 TYPE_1__* jbig2_image_new (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  jbig2_image_release (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 

Jbig2Image *
jbig2_image_read_pbm(Jbig2Ctx *ctx, FILE *in)
{
    int i, dim[2];
    int done;
    Jbig2Image *image;
    int c;
    char buf[32];

    /* look for 'P4' magic */
    while ((c = fgetc(in)) != 'P') {
        if (feof(in))
            return NULL;
    }
    if ((c = fgetc(in)) != '4') {
        fprintf(stderr, "not a binary pbm file.\n");
        return NULL;
    }
    /* read size. we must find two decimal numbers representing
       the image dimensions. 'done' will index whether we're
       looking for the width or the height and 'i' will be our
       array index for copying strings into our buffer */
    done = 0;
    i = 0;
    while (done < 2) {
        c = fgetc(in);
        /* skip whitespace */
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            continue;
        /* skip comments */
        if (c == '#') {
            while ((c = fgetc(in)) != '\n');
            continue;
        }
        /* report unexpected eof */
        if (c == EOF) {
            fprintf(stderr, "end-of-file parsing pbm header\n");
            return NULL;
        }
        if (isdigit(c)) {
            buf[i++] = c;
            while (isdigit(c = fgetc(in))) {
                if (i >= 32) {
                    fprintf(stderr, "pbm parsing error\n");
                    return NULL;
                }
                buf[i++] = c;
            }
            buf[i] = '\0';
            if (sscanf(buf, "%d", &dim[done]) != 1) {
                fprintf(stderr, "failed to read pbm image dimensions\n");
                return NULL;
            }
            i = 0;
            done++;
        }
    }
    /* allocate image structure */
    image = jbig2_image_new(ctx, dim[0], dim[1]);
    if (image == NULL) {
        fprintf(stderr, "failed to allocate %dx%d image for pbm file\n", dim[0], dim[1]);
        return NULL;
    }
    /* the pbm data is byte-aligned, so we can
       do a simple block read */
    (void)fread(image->data, 1, image->height * image->stride, in);
    if (feof(in)) {
        fprintf(stderr, "unexpected end of pbm file.\n");
        jbig2_image_release(ctx, image);
        return NULL;
    }
    /* success */
    return image;
}