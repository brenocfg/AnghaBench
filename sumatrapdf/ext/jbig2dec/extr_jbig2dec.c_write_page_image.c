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
struct TYPE_3__ {int output_format; } ;
typedef  TYPE_1__ jbig2dec_params_t ;
typedef  int /*<<< orphan*/  Jbig2Image ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int jbig2_image_write_pbm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jbig2_image_write_png (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  jbig2dec_format_pbm 129 
#define  jbig2dec_format_png 128 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
write_page_image(jbig2dec_params_t *params, FILE *out, Jbig2Image *image)
{
    switch (params->output_format) {
#ifdef HAVE_LIBPNG
    case jbig2dec_format_png:
        return jbig2_image_write_png(image, out);
#endif
    case jbig2dec_format_pbm:
        return jbig2_image_write_pbm(image, out);
    default:
        fprintf(stderr, "unsupported output format.\n");
        return 1;
    }

    return 0;
}