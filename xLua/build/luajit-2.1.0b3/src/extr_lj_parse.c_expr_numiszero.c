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
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  ExpDesc ;

/* Variables and functions */
 int /*<<< orphan*/ * expr_numtv (int /*<<< orphan*/ *) ; 
 scalar_t__ intV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 
 int tviszero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int expr_numiszero(ExpDesc *e)
{
  TValue *o = expr_numtv(e);
  return tvisint(o) ? (intV(o) == 0) : tviszero(o);
}