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
struct linebuf {size_t len; scalar_t__ bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static bool linebuf_add(struct linebuf *buf, const char *s, size_t len) {
        if (buf->len + len >= sizeof(buf->bytes))
                return false;
        memcpy(buf->bytes + buf->len, s, len);
        buf->len += len;
        return true;
}