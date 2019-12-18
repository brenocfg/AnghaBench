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
struct TYPE_3__ {scalar_t__ a_stride; scalar_t__ uv_stride; scalar_t__ y_stride; int /*<<< orphan*/ * a; int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  y; int /*<<< orphan*/ * memory_; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */

__attribute__((used)) static void WebPPictureResetBufferYUVA(WebPPicture* const picture) {
  picture->memory_ = NULL;
  picture->y = picture->u = picture->v = picture->a = NULL;
  picture->y_stride = picture->uv_stride = 0;
  picture->a_stride = 0;
}