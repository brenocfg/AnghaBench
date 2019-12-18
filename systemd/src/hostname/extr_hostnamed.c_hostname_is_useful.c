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
 int /*<<< orphan*/  is_localhost (char const*) ; 
 int /*<<< orphan*/  isempty (char const*) ; 

__attribute__((used)) static bool hostname_is_useful(const char *hn) {
        return !isempty(hn) && !is_localhost(hn);
}