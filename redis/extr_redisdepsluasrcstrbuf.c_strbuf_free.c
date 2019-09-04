#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dynamic; struct TYPE_5__* buf; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void strbuf_free(strbuf_t *s)
{
    debug_stats(s);

    if (s->buf) {
        free(s->buf);
        s->buf = NULL;
    }
    if (s->dynamic)
        free(s);
}