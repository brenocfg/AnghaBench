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
struct TYPE_3__ {scalar_t__ is_external_memory; int /*<<< orphan*/ * private_memory; } ;
typedef  TYPE_1__ WebPDecBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 

void WebPFreeDecBuffer(WebPDecBuffer* buffer) {
  if (buffer != NULL) {
    if (buffer->is_external_memory <= 0) {
      WebPSafeFree(buffer->private_memory);
    }
    buffer->private_memory = NULL;
  }
}