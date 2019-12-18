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
 int /*<<< orphan*/  MCMP (char*) ; 
 int /*<<< orphan*/  ZERO (int) ; 
 int /*<<< orphan*/  pRtlZeroMemory ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlZeroMemory(void)
{
  if (!pRtlZeroMemory)
  {
    win_skip("RtlZeroMemory is not available\n");
    return;
  }

  /* Length should be in bytes and not rounded. */
  ZERO(0); MCMP("This is a test!");
  ZERO(1); MCMP("\0his is a test!");
  ZERO(2); MCMP("\0\0is is a test!");
  ZERO(3); MCMP("\0\0\0s is a test!");
  ZERO(4); MCMP("\0\0\0\0 is a test!");
  ZERO(5); MCMP("\0\0\0\0\0is a test!");
  ZERO(6); MCMP("\0\0\0\0\0\0s a test!");
  ZERO(7); MCMP("\0\0\0\0\0\0\0 a test!");
  ZERO(8); MCMP("\0\0\0\0\0\0\0\0a test!");
  ZERO(9); MCMP("\0\0\0\0\0\0\0\0\0 test!");
}