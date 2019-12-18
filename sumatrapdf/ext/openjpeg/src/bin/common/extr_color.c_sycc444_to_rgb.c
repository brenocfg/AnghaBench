#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  color_space; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_4__ {int* data; scalar_t__ h; scalar_t__ w; scalar_t__ prec; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_CLRSPC_SRGB ; 
 scalar_t__ opj_image_data_alloc (int) ; 
 int /*<<< orphan*/  opj_image_data_free (int*) ; 
 int /*<<< orphan*/  sycc_to_rgb (int,int,int const,int const,int const,int*,int*,int*) ; 

__attribute__((used)) static void sycc444_to_rgb(opj_image_t *img)
{
    int *d0, *d1, *d2, *r, *g, *b;
    const int *y, *cb, *cr;
    size_t maxw, maxh, max, i;
    int offset, upb;

    upb = (int)img->comps[0].prec;
    offset = 1 << (upb - 1);
    upb = (1 << upb) - 1;

    maxw = (size_t)img->comps[0].w;
    maxh = (size_t)img->comps[0].h;
    max = maxw * maxh;

    y = img->comps[0].data;
    cb = img->comps[1].data;
    cr = img->comps[2].data;

    d0 = r = (int*)opj_image_data_alloc(sizeof(int) * max);
    d1 = g = (int*)opj_image_data_alloc(sizeof(int) * max);
    d2 = b = (int*)opj_image_data_alloc(sizeof(int) * max);

    if (r == NULL || g == NULL || b == NULL) {
        goto fails;
    }

    for (i = 0U; i < max; ++i) {
        sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
        ++y;
        ++cb;
        ++cr;
        ++r;
        ++g;
        ++b;
    }
    opj_image_data_free(img->comps[0].data);
    img->comps[0].data = d0;
    opj_image_data_free(img->comps[1].data);
    img->comps[1].data = d1;
    opj_image_data_free(img->comps[2].data);
    img->comps[2].data = d2;
    img->color_space = OPJ_CLRSPC_SRGB;
    return;

fails:
    opj_image_data_free(r);
    opj_image_data_free(g);
    opj_image_data_free(b);
}