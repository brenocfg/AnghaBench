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
typedef  int /*<<< orphan*/  Bitmap ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * bitmap_new () ; 

int bitmap_ensure_allocated(Bitmap **b) {
        Bitmap *a;

        assert(b);

        if (*b)
                return 0;

        a = bitmap_new();
        if (!a)
                return -ENOMEM;

        *b = a;

        return 0;
}