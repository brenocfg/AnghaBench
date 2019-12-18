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
 int IO_DONE ; 
 size_t MIN (size_t,size_t) ; 
 int buffer_get (int /*<<< orphan*/ ,char const**,size_t*) ; 
 int /*<<< orphan*/  buffer_skip (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int recvraw(p_buffer buf, size_t wanted, luaL_Buffer *b) {
    int err = IO_DONE;
    size_t total = 0;
    while (err == IO_DONE) {
        size_t count; const char *data;
        err = buffer_get(buf, &data, &count);
        count = MIN(count, wanted - total);
        luaL_addlstring(b, data, count);
        buffer_skip(buf, count);
        total += count;
        if (total >= wanted) break;
    }
    return err;
}