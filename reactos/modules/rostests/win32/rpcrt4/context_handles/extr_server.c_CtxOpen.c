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
typedef  long* PCTXTYPE ;
typedef  int /*<<< orphan*/  CTXTYPE ;

/* Variables and functions */
 scalar_t__ midl_user_allocate (int) ; 
 int /*<<< orphan*/  printf (char*,long) ; 

void CtxOpen( PCTXTYPE *pphContext,
	 long Value)
{
	printf("CtxOpen(): Value=%d\n",Value);
	*pphContext = (PCTXTYPE)midl_user_allocate( sizeof(CTXTYPE) );
	**pphContext = Value;
}