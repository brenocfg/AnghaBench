#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int debug; int size; int /*<<< orphan*/  reallocs; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */
 int calculate_new_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,int,int) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

void strbuf_resize(strbuf_t *s, int len)
{
    int newsize;

    newsize = calculate_new_size(s, len);

    if (s->debug > 1) {
        fprintf(stderr, "strbuf(%lx) resize: %d => %d\n",
                (long)s, s->size, newsize);
    }

    s->size = newsize;
    s->buf = realloc(s->buf, s->size);
    if (!s->buf)
        die("Out of memory");
    s->reallocs++;
}