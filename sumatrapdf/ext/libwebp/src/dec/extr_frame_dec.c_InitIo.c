#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * a; int /*<<< orphan*/  uv_stride; int /*<<< orphan*/  y_stride; int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  y; scalar_t__ mb_y; } ;
typedef  TYPE_1__ VP8Io ;
struct TYPE_6__ {int /*<<< orphan*/  cache_uv_stride_; int /*<<< orphan*/  cache_y_stride_; int /*<<< orphan*/  cache_v_; int /*<<< orphan*/  cache_u_; int /*<<< orphan*/  cache_y_; } ;
typedef  TYPE_2__ VP8Decoder ;

/* Variables and functions */

__attribute__((used)) static void InitIo(VP8Decoder* const dec, VP8Io* io) {
  // prepare 'io'
  io->mb_y = 0;
  io->y = dec->cache_y_;
  io->u = dec->cache_u_;
  io->v = dec->cache_v_;
  io->y_stride = dec->cache_y_stride_;
  io->uv_stride = dec->cache_uv_stride_;
  io->a = NULL;
}