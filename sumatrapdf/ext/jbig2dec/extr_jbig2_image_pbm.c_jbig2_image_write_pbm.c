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
struct TYPE_3__ {int width; int height; int stride; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ Jbig2Image ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int
jbig2_image_write_pbm(Jbig2Image *image, FILE *out)
{
    /* pbm header */
    fprintf(out, "P4\n%d %d\n", image->width, image->height);

    /* pbm format pads to a byte boundary, so we can
       just write out the whole data buffer
       NB: this assumes minimal stride for the width */
    fwrite(image->data, 1, image->height * image->stride, out);

    /* success */
    return 0;
}