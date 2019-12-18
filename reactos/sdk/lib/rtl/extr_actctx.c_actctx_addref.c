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
struct TYPE_3__ {int /*<<< orphan*/  RefCount; } ;
typedef  TYPE_1__ ACTIVATION_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedExchangeAdd (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void actctx_addref( ACTIVATION_CONTEXT *actctx )
{
    InterlockedExchangeAdd( &actctx->RefCount, 1 );
}