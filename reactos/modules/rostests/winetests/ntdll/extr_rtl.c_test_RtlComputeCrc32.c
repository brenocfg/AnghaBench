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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  LEN ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pRtlComputeCrc32 (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ src ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlComputeCrc32(void)
{
  DWORD crc = 0;

  if (!pRtlComputeCrc32)
  {
    win_skip("RtlComputeCrc32 is not available\n");
    return;
  }

  crc = pRtlComputeCrc32(crc, (const BYTE *)src, LEN);
  ok(crc == 0x40861dc2,"Expected 0x40861dc2, got %8x\n", crc);
}