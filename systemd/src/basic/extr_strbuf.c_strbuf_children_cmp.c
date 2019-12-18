#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strbuf_child_entry {int c; } ;

/* Variables and functions */

__attribute__((used)) static int strbuf_children_cmp(const struct strbuf_child_entry *n1,
                               const struct strbuf_child_entry *n2) {
        return n1->c - n2->c;
}