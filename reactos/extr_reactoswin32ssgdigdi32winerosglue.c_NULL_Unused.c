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
typedef  int /*<<< orphan*/  INT_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i ; 

__attribute__((used)) static
INT_PTR
NULL_Unused()
{
    DPRINT1("NULL_Unused %d\n",i);
    // __debugbreak();
    return 0;
}