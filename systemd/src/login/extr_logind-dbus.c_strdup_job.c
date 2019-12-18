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
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 int ENOMEM ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int strdup_job(sd_bus_message *reply, char **job) {
        const char *j;
        char *copy;
        int r;

        r = sd_bus_message_read(reply, "o", &j);
        if (r < 0)
                return r;

        copy = strdup(j);
        if (!copy)
                return -ENOMEM;

        *job = copy;
        return 1;
}