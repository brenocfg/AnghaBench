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
struct cvpxpic_ctx {int /*<<< orphan*/  cvpx; } ;
struct TYPE_3__ {int /*<<< orphan*/ * context; } ;
typedef  TYPE_1__ picture_t ;
typedef  int /*<<< orphan*/  CVPixelBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

CVPixelBufferRef
cvpxpic_get_ref(picture_t *pic)
{
    assert(pic->context != NULL);
    return ((struct cvpxpic_ctx *)pic->context)->cvpx;
}