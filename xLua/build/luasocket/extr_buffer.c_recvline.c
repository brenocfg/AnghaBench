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
 int buffer_get (int /*<<< orphan*/ ,char const**,size_t*) ; 
 int /*<<< orphan*/  buffer_skip (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char const) ; 

__attribute__((used)) static int recvline(p_buffer buf, luaL_Buffer *b) {
    int err = IO_DONE;
    while (err == IO_DONE) {
        size_t count, pos; const char *data;
        err = buffer_get(buf, &data, &count);
        pos = 0;
        while (pos < count && data[pos] != '\n') {
            /* we ignore all \r's */
            if (data[pos] != '\r') luaL_addchar(b, data[pos]);
            pos++;
        }
        if (pos < count) { /* found '\n' */
            buffer_skip(buf, pos+1); /* skip '\n' too */
            break; /* we are done */
        } else /* reached the end of the buffer */
            buffer_skip(buf, pos);
    }
    return err;
}