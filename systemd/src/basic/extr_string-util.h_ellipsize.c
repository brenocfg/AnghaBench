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
 char* ellipsize_mem (char const*,int /*<<< orphan*/ ,size_t,unsigned int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline char *ellipsize(const char *s, size_t length, unsigned percent) {
        return ellipsize_mem(s, strlen(s), length, percent);
}