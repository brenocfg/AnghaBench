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
struct cvpxpic_ctx {int /*<<< orphan*/  cvpx; } ;
typedef  int /*<<< orphan*/  picture_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVPixelBufferUnlockBaseAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvpxpic_destroy_cb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kCVPixelBufferLock_ReadOnly ; 

__attribute__((used)) static void
cvpxpic_destroy_mapped_ro_cb(picture_context_t *opaque)
{
    struct cvpxpic_ctx *ctx = (struct cvpxpic_ctx *)opaque;

    CVPixelBufferUnlockBaseAddress(ctx->cvpx, kCVPixelBufferLock_ReadOnly);
    cvpxpic_destroy_cb(opaque);
}