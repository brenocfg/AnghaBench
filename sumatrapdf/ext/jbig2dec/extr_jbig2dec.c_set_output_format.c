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
struct TYPE_3__ {int /*<<< orphan*/  output_format; } ;
typedef  TYPE_1__ jbig2dec_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  jbig2dec_format_pbm ; 
 int /*<<< orphan*/  jbig2dec_format_png ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
set_output_format(jbig2dec_params_t *params, const char *format)
{
#ifdef HAVE_LIBPNG
    /* this should really by strncasecmp()
       TODO: we need to provide our own for portability */
    if (!strncmp(format, "png", 3) || !strncmp(format, "PNG", 3)) {
        params->output_format = jbig2dec_format_png;
        return 0;
    }
#endif
    /* default to pbm */
    params->output_format = jbig2dec_format_pbm;

    return 0;
}