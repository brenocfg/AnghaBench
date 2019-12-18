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
 int AST_FUNDEC ; 
 int EXP_FUN ; 
 int EXP_PROP_GET ; 
 int EXP_PROP_SET ; 

__attribute__((used)) static int isfun(enum js_AstType T)
{
	return T == AST_FUNDEC || T == EXP_FUN || T == EXP_PROP_GET || T == EXP_PROP_SET;
}