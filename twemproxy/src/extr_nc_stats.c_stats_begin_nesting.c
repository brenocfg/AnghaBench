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
typedef  int /*<<< orphan*/  uint8_t ;
struct string {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct stats_buffer {int len; int size; int /*<<< orphan*/ * data; } ;
struct stats {struct stats_buffer buf; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_ERROR ; 
 int /*<<< orphan*/  NC_OK ; 
 int nc_snprintf (int /*<<< orphan*/ *,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rstatus_t
stats_begin_nesting(struct stats *st, struct string *key)
{
    struct stats_buffer *buf;
    uint8_t *pos;
    size_t room;
    int n;

    buf = &st->buf;
    pos = buf->data + buf->len;
    room = buf->size - buf->len - 1;

    n = nc_snprintf(pos, room, "\"%.*s\": {", key->len, key->data);
    if (n < 0 || n >= (int)room) {
        return NC_ERROR;
    }

    buf->len += (size_t)n;

    return NC_OK;
}