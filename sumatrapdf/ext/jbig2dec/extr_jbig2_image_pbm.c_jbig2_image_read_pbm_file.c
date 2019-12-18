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
typedef  int /*<<< orphan*/  Jbig2Image ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * jbig2_image_read_pbm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

Jbig2Image *
jbig2_image_read_pbm_file(Jbig2Ctx *ctx, char *filename)
{
    FILE *in;
    Jbig2Image *image;

    if ((in = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "unable to open '%s' for reading\n", filename);
        return NULL;
    }

    image = jbig2_image_read_pbm(ctx, in);

    fclose(in);

    return (image);
}