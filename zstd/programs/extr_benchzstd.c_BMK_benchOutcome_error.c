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
typedef  int /*<<< orphan*/  b ;
struct TYPE_4__ {int tag; } ;
typedef  TYPE_1__ BMK_benchOutcome_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BMK_benchOutcome_t BMK_benchOutcome_error(void)
{
    BMK_benchOutcome_t b;
    memset(&b, 0, sizeof(b));
    b.tag = 1;
    return b;
}