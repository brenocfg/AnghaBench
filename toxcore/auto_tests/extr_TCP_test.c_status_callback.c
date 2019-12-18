#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 void* status_callback_connection_id ; 
 int /*<<< orphan*/  status_callback_good ; 
 void* status_callback_status ; 

__attribute__((used)) static int status_callback(void *object, uint32_t number, uint8_t connection_id, uint8_t status)
{
    if (object != (void *)2)
        return 1;

    if (number != 7)
        return 1;

    status_callback_connection_id = connection_id;
    status_callback_status = status;
    status_callback_good++;
    return 0;
}