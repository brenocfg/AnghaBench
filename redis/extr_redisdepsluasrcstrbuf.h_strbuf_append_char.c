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
struct TYPE_4__ {char* buf; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_ensure_empty_length (TYPE_1__*,int) ; 

__attribute__((used)) static inline void strbuf_append_char(strbuf_t *s, const char c)
{
    strbuf_ensure_empty_length(s, 1);
    s->buf[s->length++] = c;
}