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
typedef  int* PCTXTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  midl_user_free (int*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void CtxClose(PCTXTYPE *pphContext )
{
	printf("CtxClose(): %d\n", **pphContext);
	midl_user_free(*pphContext);
	*pphContext = NULL;
}