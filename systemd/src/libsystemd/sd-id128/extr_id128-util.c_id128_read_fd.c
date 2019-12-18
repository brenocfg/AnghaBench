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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ Id128Format ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEDIUM ; 
 scalar_t__ ID128_PLAIN ; 
 scalar_t__ ID128_UUID ; 
 scalar_t__ _ID128_FORMAT_MAX ; 
 int /*<<< orphan*/  _fallthrough_ ; 
 int /*<<< orphan*/  assert (int) ; 
 int loop_read (int,char*,int,int) ; 
 int sd_id128_from_string (char*,int /*<<< orphan*/ *) ; 

int id128_read_fd(int fd, Id128Format f, sd_id128_t *ret) {
        char buffer[36 + 2];
        ssize_t l;

        assert(fd >= 0);
        assert(f < _ID128_FORMAT_MAX);

        /* Reads an 128bit ID from a file, which may either be in plain format (32 hex digits), or in UUID format, both
         * optionally followed by a newline and nothing else. ID files should really be newline terminated, but if they
         * aren't that's OK too, following the rule of "Be conservative in what you send, be liberal in what you
         * accept". */

        l = loop_read(fd, buffer, sizeof(buffer), false); /* we expect a short read of either 32/33 or 36/37 chars */
        if (l < 0)
                return (int) l;
        if (l == 0) /* empty? */
                return -ENOMEDIUM;

        switch (l) {

        case 33: /* plain UUID with trailing newline */
                if (buffer[32] != '\n')
                        return -EINVAL;

                _fallthrough_;
        case 32: /* plain UUID without trailing newline */
                if (f == ID128_UUID)
                        return -EINVAL;

                buffer[32] = 0;
                break;

        case 37: /* RFC UUID with trailing newline */
                if (buffer[36] != '\n')
                        return -EINVAL;

                _fallthrough_;
        case 36: /* RFC UUID without trailing newline */
                if (f == ID128_PLAIN)
                        return -EINVAL;

                buffer[36] = 0;
                break;

        default:
                return -EINVAL;
        }

        return sd_id128_from_string(buffer, ret);
}