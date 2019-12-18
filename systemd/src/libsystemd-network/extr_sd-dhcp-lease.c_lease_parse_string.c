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
typedef  char* uint8_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char* const*) ; 
 int /*<<< orphan*/  free_and_replace (char*,char*) ; 
 scalar_t__ memchr (char* const*,int /*<<< orphan*/ ,size_t) ; 
 char* memdup_suffix0 (char const*,size_t) ; 
 char* mfree (char*) ; 

__attribute__((used)) static int lease_parse_string(const uint8_t *option, size_t len, char **ret) {
        assert(option);
        assert(ret);

        if (len <= 0)
                *ret = mfree(*ret);
        else {
                char *string;

                /*
                 * One trailing NUL byte is OK, we don't mind. See:
                 * https://github.com/systemd/systemd/issues/1337
                 */
                if (memchr(option, 0, len - 1))
                        return -EINVAL;

                string = memdup_suffix0((const char *) option, len);
                if (!string)
                        return -ENOMEM;

                free_and_replace(*ret, string);
        }

        return 0;
}