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
struct vertex_metadata {scalar_t__ key; } ;

/* Variables and functions */

__attribute__((used)) static int compare_vertex_keys(const void *a, const void *b)
{
    const struct vertex_metadata *left = a;
    const struct vertex_metadata *right = b;
    if (left->key == right->key)
        return 0;
    return left->key < right->key ? -1 : 1;
}