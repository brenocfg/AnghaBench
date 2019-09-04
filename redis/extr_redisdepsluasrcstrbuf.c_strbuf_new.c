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
struct TYPE_5__ {int dynamic; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*,int) ; 

strbuf_t *strbuf_new(int len)
{
    strbuf_t *s;

    s = malloc(sizeof(strbuf_t));
    if (!s)
        die("Out of memory");

    strbuf_init(s, len);

    /* Dynamic strbuf allocation / deallocation */
    s->dynamic = 1;

    return s;
}