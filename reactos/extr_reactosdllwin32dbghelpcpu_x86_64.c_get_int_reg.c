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
typedef  int /*<<< orphan*/  ULONG64 ;
struct TYPE_3__ {int /*<<< orphan*/  Rax; } ;
typedef  TYPE_1__ CONTEXT ;

/* Variables and functions */

__attribute__((used)) static ULONG64 get_int_reg(CONTEXT *context, int reg)
{
    return *(&context->Rax + reg);
}