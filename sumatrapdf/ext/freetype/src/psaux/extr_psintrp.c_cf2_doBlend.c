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
struct TYPE_3__ {scalar_t__ lenBV; int /*<<< orphan*/ * BV; } ;
typedef  TYPE_1__* CFF_Blend ;
typedef  scalar_t__ CF2_UInt ;
typedef  int /*<<< orphan*/  CF2_Stack ;
typedef  int /*<<< orphan*/  CF2_Fixed ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_INT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_MulFix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cf2_stack_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf2_stack_getReal (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cf2_stack_pop (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cf2_stack_setReal (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  cf2_doBlend( const CFF_Blend  blend,
               CF2_Stack        opStack,
               CF2_UInt         numBlends )
  {
    CF2_UInt  delta;
    CF2_UInt  base;
    CF2_UInt  i, j;
    CF2_UInt  numOperands = (CF2_UInt)( numBlends * blend->lenBV );


    base  = cf2_stack_count( opStack ) - numOperands;
    delta = base + numBlends;

    for ( i = 0; i < numBlends; i++ )
    {
      const CF2_Fixed*  weight = &blend->BV[1];

      /* start with first term */
      CF2_Fixed  sum = cf2_stack_getReal( opStack, i + base );


      for ( j = 1; j < blend->lenBV; j++ )
        sum = ADD_INT32( sum,
                         FT_MulFix( *weight++,
                                    cf2_stack_getReal( opStack,
                                                       delta++ ) ) );

      /* store blended result  */
      cf2_stack_setReal( opStack, i + base, sum );
    }

    /* leave only `numBlends' results on stack */
    cf2_stack_pop( opStack, numOperands - numBlends );
  }