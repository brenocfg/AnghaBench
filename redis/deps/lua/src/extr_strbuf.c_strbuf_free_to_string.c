#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* buf; int length; scalar_t__ dynamic; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_ensure_null (TYPE_1__*) ; 

char *strbuf_free_to_string(strbuf_t *s, int *len)
{
    char *buf;

    debug_stats(s);

    strbuf_ensure_null(s);

    buf = s->buf;
    if (len)
        *len = s->length;

    if (s->dynamic)
        free(s);

    return buf;
}