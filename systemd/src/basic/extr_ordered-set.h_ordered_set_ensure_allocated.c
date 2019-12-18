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
struct hash_ops {int dummy; } ;
typedef  int /*<<< orphan*/  OrderedSet ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * ordered_set_new (struct hash_ops const*) ; 

__attribute__((used)) static inline int ordered_set_ensure_allocated(OrderedSet **s, const struct hash_ops *ops) {
        if (*s)
                return 0;

        *s = ordered_set_new(ops);
        if (!*s)
                return -ENOMEM;

        return 0;
}