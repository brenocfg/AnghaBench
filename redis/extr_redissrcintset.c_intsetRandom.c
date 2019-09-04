#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ intset ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  _intsetGet (TYPE_1__*,int) ; 
 int intrev32ifbe (int /*<<< orphan*/ ) ; 
 int rand () ; 

int64_t intsetRandom(intset *is) {
    return _intsetGet(is,rand()%intrev32ifbe(is->length));
}