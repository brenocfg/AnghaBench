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
 char* bus_label_unescape_n (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen_ptr (char const*) ; 

__attribute__((used)) static inline char *bus_label_unescape(const char *f) {
        return bus_label_unescape_n(f, strlen_ptr(f));
}