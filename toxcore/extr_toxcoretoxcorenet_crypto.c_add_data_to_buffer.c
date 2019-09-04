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
typedef  int /*<<< orphan*/  Packet_Data ;

/* Variables and functions */
 size_t CRYPTO_PACKET_BUFFER_SIZE ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int add_data_to_buffer(Packets_Array *array, uint32_t number, const Packet_Data *data)
{
    if (number - array->buffer_start > CRYPTO_PACKET_BUFFER_SIZE)
        return -1;

    uint32_t num = number % CRYPTO_PACKET_BUFFER_SIZE;

    if (array->buffer[num])
        return -1;

    Packet_Data *new_d = malloc(sizeof(Packet_Data));

    if (new_d == NULL)
        return -1;

    memcpy(new_d, data, sizeof(Packet_Data));
    array->buffer[num] = new_d;

    if ((number - array->buffer_start) >= (array->buffer_end - array->buffer_start))
        array->buffer_end = number + 1;

    return 0;
}