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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {size_t size; int /*<<< orphan*/  const* data; } ;
typedef  TYPE_1__ FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 

FUZZ_dataProducer_t *FUZZ_dataProducer_create(const uint8_t *data, size_t size) {
    FUZZ_dataProducer_t *producer = malloc(sizeof(FUZZ_dataProducer_t));

    FUZZ_ASSERT(producer != NULL);

    producer->data = data;
    producer->size = size;
    return producer;
}