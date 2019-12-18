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
 int ENOMEM ; 
 int /*<<< orphan*/  UID_FMT ; 
 scalar_t__ asprintf (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 

int specifier_user_id(char specifier, const void *data, const void *userdata, char **ret) {

        if (asprintf(ret, UID_FMT, getuid()) < 0)
                return -ENOMEM;

        return 0;
}