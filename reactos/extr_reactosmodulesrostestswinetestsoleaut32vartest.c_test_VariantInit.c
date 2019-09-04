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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  VARIANT ;

/* Variables and functions */
 scalar_t__ VT_EMPTY ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_VariantInit(void)
{
  VARIANT v;

  memset(&v, -1, sizeof(v));
  VariantInit(&v);
  ok(V_VT(&v) == VT_EMPTY, "VariantInit() returned vt %d\n", V_VT(&v));
}