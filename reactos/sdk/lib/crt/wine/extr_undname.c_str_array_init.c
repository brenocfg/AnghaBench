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
struct array {int /*<<< orphan*/ * elts; scalar_t__ alloc; scalar_t__ max; scalar_t__ num; scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static void str_array_init(struct array* a)
{
    a->start = a->num = a->max = a->alloc = 0;
    a->elts = NULL;
}