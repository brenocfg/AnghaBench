#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_10__ {int num_elements; int max_elements; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ int32_vec ;

/* Variables and functions */
 int /*<<< orphan*/  AssertInt64Eq (int,int) ; 
 int /*<<< orphan*/  AssertPtrEq (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  int32_vec_append (TYPE_1__*,int) ; 
 int* int32_vec_at (TYPE_1__*,int) ; 
 int /*<<< orphan*/  int32_vec_clear (TYPE_1__*) ; 
 TYPE_1__* int32_vec_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int32_vec_delete_range (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  int32_vec_free (TYPE_1__*) ; 
 int /*<<< orphan*/  int32_vec_free_data (TYPE_1__*) ; 
 int /*<<< orphan*/  int32_vec_last (TYPE_1__*) ; 

__attribute__((used)) static void
i32_vec_test(void)
{
	int32_vec *vec = int32_vec_create(CurrentMemoryContext, 0);
	int i;
	uint32 old_capacity;
	for (i = 0; i < 100; i++)
		int32_vec_append(vec, i);

	AssertInt64Eq(vec->num_elements, 100);

	if (vec->max_elements < 100)
		elog(ERROR, "vec capacity %d, should be at least 100", vec->max_elements);

	for (i = 0; i < 100; i++)
		AssertInt64Eq(*int32_vec_at(vec, i), i);

	AssertPtrEq(int32_vec_last(vec), int32_vec_at(vec, vec->num_elements - 1));

	old_capacity = vec->max_elements;
	int32_vec_delete_range(vec, 30, 19);
	AssertInt64Eq(vec->num_elements, 81);
	AssertInt64Eq(vec->max_elements, old_capacity);

	for (i = 0; i < 30; i++)
		AssertInt64Eq(*int32_vec_at(vec, i), i);

	for (; i < 51; i++)
		AssertInt64Eq(*int32_vec_at(vec, i), i + 19);

	AssertPtrEq(int32_vec_last(vec), int32_vec_at(vec, vec->num_elements - 1));

	int32_vec_clear(vec);
	AssertInt64Eq(vec->num_elements, 0);
	AssertInt64Eq(vec->max_elements, old_capacity);

	int32_vec_free_data(vec);
	AssertInt64Eq(vec->num_elements, 0);
	AssertInt64Eq(vec->max_elements, 0);
	AssertPtrEq(vec->data, NULL);

	/* free_data is idempotent */
	int32_vec_free_data(vec);
	AssertInt64Eq(vec->num_elements, 0);
	AssertInt64Eq(vec->max_elements, 0);
	AssertPtrEq(vec->data, NULL);

	int32_vec_free(vec);
}