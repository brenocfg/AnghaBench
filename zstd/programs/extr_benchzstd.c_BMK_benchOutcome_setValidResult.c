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
struct TYPE_3__ {int /*<<< orphan*/  internal_never_use_directly; scalar_t__ tag; } ;
typedef  int /*<<< orphan*/  BMK_benchResult_t ;
typedef  TYPE_1__ BMK_benchOutcome_t ;

/* Variables and functions */

__attribute__((used)) static BMK_benchOutcome_t BMK_benchOutcome_setValidResult(BMK_benchResult_t result)
{
    BMK_benchOutcome_t b;
    b.tag = 0;
    b.internal_never_use_directly = result;
    return b;
}