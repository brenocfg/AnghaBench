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
 char* replace_env_n (char const*,int /*<<< orphan*/ ,char**,unsigned int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline char *replace_env(const char *format, char **env, unsigned flags) {
        return replace_env_n(format, strlen(format), env, flags);
}