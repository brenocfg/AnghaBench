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
struct Item {int seen; } ;
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 int ELEMENTSOF (struct Item*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  item_seen ; 
 int /*<<< orphan*/ * set_free_with_destructor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * set_new (int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ *,struct Item*) ; 

__attribute__((used)) static void test_set_free_with_destructor(void) {
        Set *m;
        struct Item items[4] = {};
        unsigned i;

        assert_se(m = set_new(NULL));
        for (i = 0; i < ELEMENTSOF(items) - 1; i++)
                assert_se(set_put(m, items + i) == 1);

        m = set_free_with_destructor(m, item_seen);
        assert_se(items[0].seen == 1);
        assert_se(items[1].seen == 1);
        assert_se(items[2].seen == 1);
        assert_se(items[3].seen == 0);
}