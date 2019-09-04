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

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int tcp_data_callback_called ; 

__attribute__((used)) static int tcp_data_callback(void *object, int id, const uint8_t *data, uint16_t length)
{
    if (object != (void *)120397)
        return -1;

    if (id != 123)
        return -1;

    if (length != 6)
        return -1;

    if (memcmp(data, "Gentoo", length) != 0)
        return -1;

    tcp_data_callback_called = 1;
    return 0;
}