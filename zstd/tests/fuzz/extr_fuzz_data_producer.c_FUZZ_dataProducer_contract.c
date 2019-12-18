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
struct TYPE_3__ {size_t size; scalar_t__ data; } ;
typedef  TYPE_1__ FUZZ_dataProducer_t ;

/* Variables and functions */

size_t FUZZ_dataProducer_contract(FUZZ_dataProducer_t *producer, size_t newSize)
{
    newSize = newSize > producer->size ? producer->size : newSize;

    size_t remaining = producer->size - newSize;
    producer->data = producer->data + remaining;
    producer->size = newSize;
    return remaining;
}