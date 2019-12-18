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
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ WebPData ;
struct TYPE_6__ {int /*<<< orphan*/  end_; scalar_t__ start_; int /*<<< orphan*/  buf_; } ;
typedef  TYPE_2__ MemBuffer ;

/* Variables and functions */

__attribute__((used)) static void InitMemBuffer(MemBuffer* const mem, const WebPData* webp_data) {
  mem->buf_ = webp_data->bytes;
  mem->start_ = 0;
  mem->end_ = webp_data->size;
}