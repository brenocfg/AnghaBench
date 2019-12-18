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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ buffer_end; scalar_t__ buffer_start; int /*<<< orphan*/ ** buffer; } ;
typedef  TYPE_1__ Packets_Array ;
typedef  int /*<<< orphan*/  Packet_Data ;

/* Variables and functions */
 scalar_t__ CRYPTO_PACKET_BUFFER_SIZE ; 

__attribute__((used)) static int get_data_pointer(const Packets_Array *array, Packet_Data **data, uint32_t number)
{
    uint32_t num_spots = array->buffer_end - array->buffer_start;

    if (array->buffer_end - number > num_spots || number - array->buffer_start >= num_spots)
        return -1;

    uint32_t num = number % CRYPTO_PACKET_BUFFER_SIZE;

    if (!array->buffer[num])
        return 0;

    *data = array->buffer[num];
    return 1;
}