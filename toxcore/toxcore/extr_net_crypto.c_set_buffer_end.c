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
struct TYPE_3__ {scalar_t__ buffer_start; scalar_t__ buffer_end; } ;
typedef  TYPE_1__ Packets_Array ;

/* Variables and functions */
 scalar_t__ CRYPTO_PACKET_BUFFER_SIZE ; 

__attribute__((used)) static int set_buffer_end(Packets_Array *array, uint32_t number)
{
    if ((number - array->buffer_start) > CRYPTO_PACKET_BUFFER_SIZE)
        return -1;

    if ((number - array->buffer_end) > CRYPTO_PACKET_BUFFER_SIZE)
        return -1;

    array->buffer_end = number;
    return 0;
}