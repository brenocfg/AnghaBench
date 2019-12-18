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
struct TYPE_3__ {int /*<<< orphan*/  fromlist; } ;
typedef  TYPE_1__ FromExpr ;

/* Variables and functions */
 int /*<<< orphan*/  IsA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeTblRef ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
has_joins(FromExpr *jointree)
{
	return list_length(jointree->fromlist) != 1 || !IsA(linitial(jointree->fromlist), RangeTblRef);
}