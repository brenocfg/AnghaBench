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
typedef  int int64_t ;
struct TYPE_3__ {size_t buffer_end; size_t buffer_start; int /*<<< orphan*/ ** buffer; } ;
typedef  TYPE_1__ Packets_Array ;
typedef  int /*<<< orphan*/  Packet_Data ;

/* Variables and functions */
 size_t CRYPTO_PACKET_BUFFER_SIZE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int64_t read_data_beg_buffer(Packets_Array *array, Packet_Data *data)
{
    if (array->buffer_end == array->buffer_start)
        return -1;

    uint32_t num = array->buffer_start % CRYPTO_PACKET_BUFFER_SIZE;

    if (!array->buffer[num])
        return -1;

    memcpy(data, array->buffer[num], sizeof(Packet_Data));
    uint32_t id = array->buffer_start;
    ++array->buffer_start;
    free(array->buffer[num]);
    array->buffer[num] = NULL;
    return id;
}