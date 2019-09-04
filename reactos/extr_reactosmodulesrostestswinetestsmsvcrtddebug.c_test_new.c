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

/* Variables and functions */
 int /*<<< orphan*/  _CRT_BLOCK ; 
 int /*<<< orphan*/  _NORMAL_BLOCK ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pMSVCRTD_operator_delete (void*) ; 
 void* pMSVCRTD_operator_new_dbg (int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void test_new(void)
{
  void *mem;

  mem = pMSVCRTD_operator_new_dbg(42, _NORMAL_BLOCK, __FILE__, __LINE__);
  ok(mem != NULL, "memory not allocated\n");
  pMSVCRTD_operator_delete(mem);

  mem = pMSVCRTD_operator_new_dbg(42, _CRT_BLOCK, __FILE__, __LINE__);
  ok(mem != NULL, "memory not allocated\n");
  pMSVCRTD_operator_delete(mem);
}