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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTM_DELLINK ; 
 int /*<<< orphan*/  RTM_GETLINK ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  RTM_SETLINK ; 

__attribute__((used)) static inline bool rtnl_message_type_is_link(uint16_t type) {
        return IN_SET(type, RTM_NEWLINK, RTM_SETLINK, RTM_GETLINK, RTM_DELLINK);
}