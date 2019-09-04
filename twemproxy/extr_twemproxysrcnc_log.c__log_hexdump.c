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
struct logger {scalar_t__ fd; int /*<<< orphan*/  nerror; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int LOG_MAX_LEN ; 
 int errno ; 
 scalar_t__ isprint (char) ; 
 struct logger logger ; 
 scalar_t__ nc_scnprintf (char*,int,char*,...) ; 
 scalar_t__ nc_write (scalar_t__,char*,int) ; 

void
_log_hexdump(const char *file, int line, char *data, int datalen,
             const char *fmt, ...)
{
    struct logger *l = &logger;
    char buf[8 * LOG_MAX_LEN];
    int i, off, len, size, errno_save;
    ssize_t n;

    if (l->fd < 0) {
        return;
    }

    /* log hexdump */
    errno_save = errno;
    off = 0;                  /* data offset */
    len = 0;                  /* length of output buffer */
    size = 8 * LOG_MAX_LEN;   /* size of output buffer */

    while (datalen != 0 && (len < size - 1)) {
        char *save, *str;
        unsigned char c;
        int savelen;

        len += nc_scnprintf(buf + len, size - len, "%08x  ", off);

        save = data;
        savelen = datalen;

        for (i = 0; datalen != 0 && i < 16; data++, datalen--, i++) {
            c = (unsigned char)(*data);
            str = (i == 7) ? "  " : " ";
            len += nc_scnprintf(buf + len, size - len, "%02x%s", c, str);
        }
        for ( ; i < 16; i++) {
            str = (i == 7) ? "  " : " ";
            len += nc_scnprintf(buf + len, size - len, "  %s", str);
        }

        data = save;
        datalen = savelen;

        len += nc_scnprintf(buf + len, size - len, "  |");

        for (i = 0; datalen != 0 && i < 16; data++, datalen--, i++) {
            c = (unsigned char)(isprint(*data) ? *data : '.');
            len += nc_scnprintf(buf + len, size - len, "%c", c);
        }
        len += nc_scnprintf(buf + len, size - len, "|\n");

        off += 16;
    }

    n = nc_write(l->fd, buf, len);
    if (n < 0) {
        l->nerror++;
    }

    if (len >= size - 1) {
        n = nc_write(l->fd, "\n", 1);
        if (n < 0) {
            l->nerror++;
        }
    }

    errno = errno_save;
}