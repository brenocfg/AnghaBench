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
struct TYPE_3__ {size_t length; scalar_t__* buf; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */

__attribute__((used)) static inline void strbuf_ensure_null(strbuf_t *s)
{
    s->buf[s->length] = 0;
}