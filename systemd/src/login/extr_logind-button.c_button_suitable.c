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

/* Variables and functions */
 int CONST_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CONST_MAX4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVIOCGBIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  EV_SYN ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  KEY_POWER2 ; 
 int /*<<< orphan*/  KEY_SLEEP ; 
 int /*<<< orphan*/  KEY_SUSPEND ; 
 int /*<<< orphan*/  SW_DOCK ; 
 int /*<<< orphan*/  SW_LID ; 
 int ULONG_BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bitset_get (unsigned long*,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int button_suitable(int fd) {
        unsigned long types[CONST_MAX(EV_KEY, EV_SW)/ULONG_BITS+1];

        assert(fd >= 0);

        if (ioctl(fd, EVIOCGBIT(EV_SYN, sizeof types), types) < 0)
                return -errno;

        if (bitset_get(types, EV_KEY)) {
                unsigned long keys[CONST_MAX4(KEY_POWER, KEY_POWER2, KEY_SLEEP, KEY_SUSPEND)/ULONG_BITS+1];

                if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof keys), keys) < 0)
                        return -errno;

                if (bitset_get(keys, KEY_POWER) ||
                    bitset_get(keys, KEY_POWER2) ||
                    bitset_get(keys, KEY_SLEEP) ||
                    bitset_get(keys, KEY_SUSPEND))
                        return true;
        }

        if (bitset_get(types, EV_SW)) {
                unsigned long switches[CONST_MAX(SW_LID, SW_DOCK)/ULONG_BITS+1];

                if (ioctl(fd, EVIOCGBIT(EV_SW, sizeof switches), switches) < 0)
                        return -errno;

                if (bitset_get(switches, SW_LID) ||
                    bitset_get(switches, SW_DOCK))
                        return true;
        }

        return false;
}