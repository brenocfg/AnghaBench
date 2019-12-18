#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int is_external_memory; int /*<<< orphan*/ * private_memory; } ;
typedef  TYPE_1__ WebPDecBuffer ;

/* Variables and functions */

void WebPCopyDecBuffer(const WebPDecBuffer* const src,
                       WebPDecBuffer* const dst) {
  if (src != NULL && dst != NULL) {
    *dst = *src;
    if (src->private_memory != NULL) {
      dst->is_external_memory = 1;   // dst buffer doesn't own the memory.
      dst->private_memory = NULL;
    }
  }
}