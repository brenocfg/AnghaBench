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
 scalar_t__ isempty (char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static inline bool SEAT_IS_SELF(const char *name) {
        return isempty(name) || streq(name, "self");
}