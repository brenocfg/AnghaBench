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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  num_recv ; 

void print_group_message(Tox *tox, int groupnumber, int peernumber, const uint8_t *message, uint16_t length,
                         void *userdata)
{
    if (*((uint32_t *)userdata) != 234212)
        return;

    if (length == (sizeof("Install Gentoo") - 1) && memcmp(message, "Install Gentoo", sizeof("Install Gentoo") - 1) == 0) {
        ++num_recv;
    }
}