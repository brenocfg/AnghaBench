#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  max_elements; int /*<<< orphan*/  num_elements; } ;
typedef  TYPE_1__ uint64_vec ;

/* Variables and functions */
 int /*<<< orphan*/  AssertInt64Eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AssertPtrEq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  uint64_vec_append (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * uint64_vec_at (TYPE_1__*,int) ; 
 int /*<<< orphan*/  uint64_vec_free_data (TYPE_1__*) ; 
 int /*<<< orphan*/  uint64_vec_init (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uint64_vec_test(void)
{
	uint64_vec vec;
	int i;
	uint64_vec_init(&vec, CurrentMemoryContext, 100);
	for (i = 0; i < 30; i++)
		uint64_vec_append(&vec, i + 3);

	AssertInt64Eq(vec.num_elements, 30);
	AssertInt64Eq(vec.max_elements, 100);
	for (i = 0; i < 30; i++)
		AssertInt64Eq(*uint64_vec_at(&vec, i), i + 3);

	uint64_vec_free_data(&vec);
	AssertInt64Eq(vec.num_elements, 0);
	AssertInt64Eq(vec.max_elements, 0);
	AssertPtrEq(vec.data, NULL);
}