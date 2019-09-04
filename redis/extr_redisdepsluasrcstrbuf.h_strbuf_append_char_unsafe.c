#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* buf; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */

__attribute__((used)) static inline void strbuf_append_char_unsafe(strbuf_t *s, const char c)
{
    s->buf[s->length++] = c;
}