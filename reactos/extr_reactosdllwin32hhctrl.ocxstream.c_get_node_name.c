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
struct TYPE_6__ {char* buf; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  isspace (char const) ; 
 int /*<<< orphan*/  strbuf_append (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  strbuf_zero (TYPE_1__*) ; 

void get_node_name(strbuf_t *node, strbuf_t *name)
{
    const char *ptr = node->buf+1;

    strbuf_zero(name);

    while(*ptr != '>' && !isspace(*ptr))
        ptr++;

    strbuf_append(name, node->buf+1, ptr-node->buf-1);
    strbuf_append(name, "", 1);
}