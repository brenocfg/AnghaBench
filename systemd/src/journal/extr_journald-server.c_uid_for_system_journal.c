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
typedef  scalar_t__ uid_t ;

/* Variables and functions */
 scalar_t__ UID_NOBODY ; 
 scalar_t__ uid_is_dynamic (scalar_t__) ; 
 scalar_t__ uid_is_system (scalar_t__) ; 

__attribute__((used)) static bool uid_for_system_journal(uid_t uid) {

        /* Returns true if the specified UID shall get its data stored in the system journal*/

        return uid_is_system(uid) || uid_is_dynamic(uid) || uid == UID_NOBODY;
}