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
struct TYPE_3__ {int /*<<< orphan*/  consttype; int /*<<< orphan*/  constvalue; } ;
typedef  int /*<<< orphan*/  DimensionValues ;
typedef  TYPE_1__ Const ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dimension_values_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DimensionValues *
dimension_values_create_from_single_element(Const *c, bool user_or)
{
	return dimension_values_create(list_make1(DatumGetPointer(c->constvalue)),
								   c->consttype,
								   user_or);
}