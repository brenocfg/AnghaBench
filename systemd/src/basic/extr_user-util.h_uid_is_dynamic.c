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
 scalar_t__ DYNAMIC_UID_MAX ; 
 scalar_t__ DYNAMIC_UID_MIN ; 

__attribute__((used)) static inline bool uid_is_dynamic(uid_t uid) {
        return DYNAMIC_UID_MIN <= uid && uid <= DYNAMIC_UID_MAX;
}