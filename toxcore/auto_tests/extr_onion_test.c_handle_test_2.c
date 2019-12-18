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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int handled_test_2 ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int handle_test_2(void *object, IP_Port source, const uint8_t *packet, uint16_t length)
{
    if (length != sizeof("\x84 install Gentoo"))
        return 1;

    if (memcmp(packet, (uint8_t *)"\x84 install gentoo", sizeof("\x84 install gentoo")) != 0)
        return 1;

    handled_test_2 = 1;
    return 0;
}