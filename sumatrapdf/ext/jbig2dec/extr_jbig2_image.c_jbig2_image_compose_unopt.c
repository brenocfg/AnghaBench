#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int width; int height; } ;
typedef  TYPE_1__ Jbig2Image ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int Jbig2ComposeOp ;

/* Variables and functions */
#define  JBIG2_COMPOSE_AND 132 
#define  JBIG2_COMPOSE_OR 131 
#define  JBIG2_COMPOSE_REPLACE 130 
#define  JBIG2_COMPOSE_XNOR 129 
#define  JBIG2_COMPOSE_XOR 128 
 int jbig2_image_get_pixel (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  jbig2_image_set_pixel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
jbig2_image_compose_unopt(Jbig2Ctx *ctx, Jbig2Image *dst, Jbig2Image *src, int x, int y, Jbig2ComposeOp op)
{
    uint32_t i, j;
    uint32_t sw = src->width;
    uint32_t sh = src->height;
    uint32_t sx = 0;
    uint32_t sy = 0;

    /* clip to the dst image boundaries */
    if (x < 0) {
        sx += -x;
        if (sw < (uint32_t) -x)
            sw = 0;
        else
            sw -= -x;
        x = 0;
    }
    if (y < 0) {
        sy += -y;
        if (sh < (uint32_t) -y)
            sh = 0;
        else
            sh -= -y;
        y = 0;
    }
    if ((uint32_t) x + sw >= dst->width) {
        if (dst->width >= (uint32_t) x)
            sw = dst->width - x;
        else
            sw = 0;
    }
    if ((uint32_t) y + sh >= dst->height) {
        if (dst->height >= (uint32_t) y)
            sh = dst->height - y;
        else
            sh = 0;
    }

    switch (op) {
    case JBIG2_COMPOSE_OR:
        for (j = 0; j < sh; j++) {
            for (i = 0; i < sw; i++) {
                jbig2_image_set_pixel(dst, i + x, j + y, jbig2_image_get_pixel(src, i + sx, j + sy) | jbig2_image_get_pixel(dst, i + x, j + y));
            }
        }
        break;
    case JBIG2_COMPOSE_AND:
        for (j = 0; j < sh; j++) {
            for (i = 0; i < sw; i++) {
                jbig2_image_set_pixel(dst, i + x, j + y, jbig2_image_get_pixel(src, i + sx, j + sy) & jbig2_image_get_pixel(dst, i + x, j + y));
            }
        }
        break;
    case JBIG2_COMPOSE_XOR:
        for (j = 0; j < sh; j++) {
            for (i = 0; i < sw; i++) {
                jbig2_image_set_pixel(dst, i + x, j + y, jbig2_image_get_pixel(src, i + sx, j + sy) ^ jbig2_image_get_pixel(dst, i + x, j + y));
            }
        }
        break;
    case JBIG2_COMPOSE_XNOR:
        for (j = 0; j < sh; j++) {
            for (i = 0; i < sw; i++) {
                jbig2_image_set_pixel(dst, i + x, j + y, (jbig2_image_get_pixel(src, i + sx, j + sy) == jbig2_image_get_pixel(dst, i + x, j + y)));
            }
        }
        break;
    case JBIG2_COMPOSE_REPLACE:
        for (j = 0; j < sh; j++) {
            for (i = 0; i < sw; i++) {
                jbig2_image_set_pixel(dst, i + x, j + y, jbig2_image_get_pixel(src, i + sx, j + sy));
            }
        }
        break;
    }

    return 0;
}