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
struct _exception {int type; char* name; double arg1; double arg2; double retval; } ;

/* Variables and functions */
 int /*<<< orphan*/  stUserMathErr (struct _exception*) ; 
 int /*<<< orphan*/  stub1 (struct _exception*) ; 

void __mingw_raise_matherr (int typ, const char *name, double a1, double a2,
			    double rslt)
{
  struct _exception ex;
  if (!stUserMathErr)
    return;
  ex.type = typ;
  ex.name = (char*)name;
  ex.arg1 = a1;
  ex.arg2 = a2;
  ex.retval = rslt;
  (*stUserMathErr)(&ex);
}