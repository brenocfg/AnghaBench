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
 int /*<<< orphan*/  CMP (char*) ; 
 int /*<<< orphan*/  FILL (int) ; 
 int /*<<< orphan*/  pRtlFillMemory ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlFillMemory(void)
{
  if (!pRtlFillMemory)
  {
    win_skip("RtlFillMemory is not available\n");
    return;
  }

  /* Length should be in bytes and not rounded. Use strcmp to ensure we
   * didn't write past the end (the remainder of the string should match)
   */
  FILL(0); CMP("This is a test!");
  FILL(1); CMP("xhis is a test!");
  FILL(2); CMP("xxis is a test!");
  FILL(3); CMP("xxxs is a test!");
  FILL(4); CMP("xxxx is a test!");
  FILL(5); CMP("xxxxxis a test!");
  FILL(6); CMP("xxxxxxs a test!");
  FILL(7); CMP("xxxxxxx a test!");
  FILL(8); CMP("xxxxxxxxa test!");
  FILL(9); CMP("xxxxxxxxx test!");
}