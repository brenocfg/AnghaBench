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
typedef  int uint32_t ;
struct TYPE_3__ {int GRREFERENCEDX; int GRREFERENCEDY; int /*<<< orphan*/ * GRREFERENCE; } ;
typedef  TYPE_1__ Jbig2RefinementRegionParams ;
typedef  int /*<<< orphan*/  Jbig2Image ;

/* Variables and functions */
 int jbig2_image_get_pixel (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static uint32_t
mkctx1(const Jbig2RefinementRegionParams *params, Jbig2Image *image, int x, int y)
{
    Jbig2Image *ref = params->GRREFERENCE;
    const int dx = params->GRREFERENCEDX;
    const int dy = params->GRREFERENCEDY;
    uint32_t CONTEXT;

    CONTEXT = jbig2_image_get_pixel(image, x - 1, y + 0);
    CONTEXT |= jbig2_image_get_pixel(image, x + 1, y - 1) << 1;
    CONTEXT |= jbig2_image_get_pixel(image, x + 0, y - 1) << 2;
    CONTEXT |= jbig2_image_get_pixel(image, x - 1, y - 1) << 3;
    CONTEXT |= jbig2_image_get_pixel(ref, x - dx + 1, y - dy + 1) << 4;
    CONTEXT |= jbig2_image_get_pixel(ref, x - dx + 0, y - dy + 1) << 5;
    CONTEXT |= jbig2_image_get_pixel(ref, x - dx + 1, y - dy + 0) << 6;
    CONTEXT |= jbig2_image_get_pixel(ref, x - dx + 0, y - dy + 0) << 7;
    CONTEXT |= jbig2_image_get_pixel(ref, x - dx - 1, y - dy + 0) << 8;
    CONTEXT |= jbig2_image_get_pixel(ref, x - dx + 0, y - dy - 1) << 9;
    return CONTEXT;
}