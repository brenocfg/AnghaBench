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
typedef  enum js_AstType { ____Placeholder_js_AstType } js_AstType ;

/* Variables and functions */
 int STM_DO ; 
 int STM_FOR ; 
 int STM_FOR_IN ; 
 int STM_FOR_IN_VAR ; 
 int STM_FOR_VAR ; 
 int STM_WHILE ; 

__attribute__((used)) static int isloop(enum js_AstType T)
{
	return T == STM_DO || T == STM_WHILE ||
		T == STM_FOR || T == STM_FOR_VAR ||
		T == STM_FOR_IN || T == STM_FOR_IN_VAR;
}