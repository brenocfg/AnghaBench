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
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 scalar_t__ NUM_FIRST ; 
 scalar_t__ NUM_LAST ; 
 int /*<<< orphan*/  ck_abort_msg (char*) ; 
 int first_ip ; 
 int last_ip ; 

void dht_ip_callback(void *object, int32_t number, IP_Port ip_port)
{
    if (NUM_FIRST == number) {
        first_ip = 1;
        return;
    }

    if (NUM_LAST == number) {
        last_ip = 1;
        return;
    }

    ck_abort_msg("Error.");
}