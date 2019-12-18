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
struct TYPE_3__ {int dx; int dy; int prec; int sgnd; } ;
typedef  TYPE_1__ opj_image_comp_t ;
typedef  scalar_t__ OPJ_BOOL ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * stdout ; 

void j2k_dump_image_comp_header(opj_image_comp_t* comp_header,
                                OPJ_BOOL dev_dump_flag, FILE* out_stream)
{
    char tab[3];

    if (dev_dump_flag) {
        fprintf(stdout, "[DEV] Dump an image_comp_header struct {\n");
        tab[0] = '\0';
    }       else {
        tab[0] = '\t';
        tab[1] = '\t';
        tab[2] = '\0';
    }

    fprintf(out_stream, "%s dx=%d, dy=%d\n", tab, comp_header->dx, comp_header->dy);
    fprintf(out_stream, "%s prec=%d\n", tab, comp_header->prec);
    fprintf(out_stream, "%s sgnd=%d\n", tab, comp_header->sgnd);

    if (dev_dump_flag) {
        fprintf(out_stream, "}\n");
    }
}