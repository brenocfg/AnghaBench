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
struct TYPE_3__ {int GRREFERENCEDX; int GRREFERENCEDY; int /*<<< orphan*/ * GRREFERENCE; } ;
typedef  TYPE_1__ Jbig2RefinementRegionParams ;
typedef  int /*<<< orphan*/  Jbig2Image ;

/* Variables and functions */
 int jbig2_image_get_pixel (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
implicit_value(const Jbig2RefinementRegionParams *params, Jbig2Image *image, int x, int y)
{
    Jbig2Image *ref = params->GRREFERENCE;
    int i = x - params->GRREFERENCEDX;
    int j = y - params->GRREFERENCEDY;
    int m = jbig2_image_get_pixel(ref, i, j);

    return ((jbig2_image_get_pixel(ref, i - 1, j - 1) == m) &&
            (jbig2_image_get_pixel(ref, i, j - 1) == m) &&
            (jbig2_image_get_pixel(ref, i + 1, j - 1) == m) &&
            (jbig2_image_get_pixel(ref, i - 1, j) == m) &&
            (jbig2_image_get_pixel(ref, i + 1, j) == m) &&
            (jbig2_image_get_pixel(ref, i - 1, j + 1) == m) &&
            (jbig2_image_get_pixel(ref, i, j + 1) == m) &&
            (jbig2_image_get_pixel(ref, i + 1, j + 1) == m)
           )? m : -1;
}