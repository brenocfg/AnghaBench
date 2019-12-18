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
typedef  size_t uint32_t ;
struct TYPE_3__ {size_t buffer_start; size_t buffer_end; int /*<<< orphan*/ ** buffer; } ;
typedef  TYPE_1__ Packets_Array ;

/* Variables and functions */
 size_t CRYPTO_PACKET_BUFFER_SIZE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clear_buffer(Packets_Array *array)
{
    uint32_t i;

    for (i = array->buffer_start; i != array->buffer_end; ++i) {
        uint32_t num = i % CRYPTO_PACKET_BUFFER_SIZE;

        if (array->buffer[num]) {
            free(array->buffer[num]);
            array->buffer[num] = NULL;
        }
    }

    array->buffer_start = i;
    return 0;
}