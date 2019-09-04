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
struct TYPE_4__ {int size; int /*<<< orphan*/ * buf; scalar_t__ debug; scalar_t__ reallocs; scalar_t__ dynamic; int /*<<< orphan*/  increment; scalar_t__ length; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRBUF_DEFAULT_INCREMENT ; 
 int STRBUF_DEFAULT_SIZE ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  strbuf_ensure_null (TYPE_1__*) ; 

void strbuf_init(strbuf_t *s, int len)
{
    int size;

    if (len <= 0)
        size = STRBUF_DEFAULT_SIZE;
    else
        size = len + 1;         /* \0 terminator */

    s->buf = NULL;
    s->size = size;
    s->length = 0;
    s->increment = STRBUF_DEFAULT_INCREMENT;
    s->dynamic = 0;
    s->reallocs = 0;
    s->debug = 0;

    s->buf = malloc(size);
    if (!s->buf)
        die("Out of memory");

    strbuf_ensure_null(s);
}