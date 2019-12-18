#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_8__ {scalar_t__ stride; scalar_t__ height; int /*<<< orphan*/  width; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {int word; int bit_index; scalar_t__ data_index; } ;
typedef  TYPE_1__ Jbig2MmrCtx ;
typedef  TYPE_2__ Jbig2Image ;
typedef  int /*<<< orphan*/  Jbig2GenericRegionParams ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int /*<<< orphan*/  jbig2_decode_mmr_consume (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jbig2_decode_mmr_init (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 int jbig2_decode_mmr_line (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__ const) ; 

int
jbig2_decode_halftone_mmr(Jbig2Ctx *ctx, const Jbig2GenericRegionParams *params, const byte *data, size_t size, Jbig2Image *image, size_t *consumed_bytes)
{
    Jbig2MmrCtx mmr;
    const uint32_t rowstride = image->stride;
    byte *dst = image->data;
    byte *ref = NULL;
    uint32_t y;
    int code = 0;
    const uint32_t EOFB = 0x001001;
    int eofb = 0;

    jbig2_decode_mmr_init(&mmr, image->width, image->height, data, size);

    for (y = 0; !eofb && y < image->height; y++) {
        memset(dst, 0, rowstride);
        code = jbig2_decode_mmr_line(ctx, &mmr, ref, dst, &eofb);
        if (code < 0)
            return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1, "failed to decode halftone mmr line");
        ref = dst;
        dst += rowstride;
    }

    if (eofb && y < image->height) {
        memset(dst, 0, rowstride * (image->height - y));
    }

    /* test for EOFB (see section 6.2.6) */
    if (mmr.word >> 8 == EOFB) {
        jbig2_decode_mmr_consume(&mmr, 24);
    }

    *consumed_bytes += mmr.data_index + (mmr.bit_index >> 3) + (mmr.bit_index > 0 ? 1 : 0);
    return code;
}