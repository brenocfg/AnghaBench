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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 scalar_t__ intV (int /*<<< orphan*/ *) ; 
 scalar_t__ lj_strscan_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setnumV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnum (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static cTValue *str2num(cTValue *o, TValue *n)
{
  if (tvisnum(o))
    return o;
  else if (tvisint(o))
    return (setnumV(n, (lua_Number)intV(o)), n);
  else if (tvisstr(o) && lj_strscan_num(strV(o), n))
    return n;
  else
    return NULL;
}