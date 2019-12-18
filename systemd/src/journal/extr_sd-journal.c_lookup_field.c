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
typedef  char const sd_journal ;

/* Variables and functions */
 size_t REPLACE_VAR_MAX ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int sd_journal_get_data (char const*,char const*,void const**,size_t*) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 char* strndup (char const*,size_t) ; 

__attribute__((used)) static char *lookup_field(const char *field, void *userdata) {
        sd_journal *j = userdata;
        const void *data;
        size_t size, d;
        int r;

        assert(field);
        assert(j);

        r = sd_journal_get_data(j, field, &data, &size);
        if (r < 0 ||
            size > REPLACE_VAR_MAX)
                return strdup(field);

        d = strlen(field) + 1;

        return strndup((const char*) data + d, size - d);
}