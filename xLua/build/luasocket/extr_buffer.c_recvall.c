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
typedef  int /*<<< orphan*/  p_buffer ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int IO_CLOSED ; 
 int IO_DONE ; 
 int buffer_get (int /*<<< orphan*/ ,char const**,size_t*) ; 
 int /*<<< orphan*/  buffer_skip (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int recvall(p_buffer buf, luaL_Buffer *b) {
    int err = IO_DONE;
    size_t total = 0;
    while (err == IO_DONE) {
        const char *data; size_t count;
        err = buffer_get(buf, &data, &count);
        total += count;
        luaL_addlstring(b, data, count);
        buffer_skip(buf, count);
    }
    if (err == IO_CLOSED) {
        if (total > 0) return IO_DONE;
        else return IO_CLOSED;
    } else return err;
}