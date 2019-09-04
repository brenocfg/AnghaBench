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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  SECOND_FLAG ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  request_flags ; 

void parent_confirm_message(Messenger *m, int num, uint8_t *data, uint16_t length, void *userdata)
{
    puts("OK");
    request_flags |= SECOND_FLAG;
}