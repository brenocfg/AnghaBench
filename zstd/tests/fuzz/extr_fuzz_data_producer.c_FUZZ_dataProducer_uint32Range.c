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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ size; scalar_t__* data; } ;
typedef  TYPE_1__ FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 

uint32_t FUZZ_dataProducer_uint32Range(FUZZ_dataProducer_t *producer, uint32_t min,
                                  uint32_t max) {
    FUZZ_ASSERT(min <= max);

    uint32_t range = max - min;
    uint32_t rolling = range;
    uint32_t result = 0;

    while (rolling > 0 && producer->size > 0) {
      uint8_t next = *(producer->data + producer->size - 1);
      producer->size -= 1;
      result = (result << 8) | next;
      rolling >>= 8;
    }

    if (range == 0xffffffff) {
      return result;
    }

    return min + result % (range + 1);
}