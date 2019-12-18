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
struct TYPE_4__ {scalar_t__ length; scalar_t__ buf; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  strbuf_ensure_empty_length (TYPE_1__*,int) ; 

__attribute__((used)) static inline void strbuf_append_mem(strbuf_t *s, const char *c, int len)
{
    strbuf_ensure_empty_length(s, len);
    memcpy(s->buf + s->length, c, len);
    s->length += len;
}