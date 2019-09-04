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
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  status_m_changes ; 

void print_status_m_change(Tox *tox, uint32_t friend_number, const uint8_t *message, size_t length, void *user_data)
{
    if (*((uint32_t *)user_data) != 974536)
        return;

    if (length == sizeof("Installing Gentoo") && memcmp(message, "Installing Gentoo", sizeof("Installing Gentoo")) == 0)
        ++status_m_changes;
}