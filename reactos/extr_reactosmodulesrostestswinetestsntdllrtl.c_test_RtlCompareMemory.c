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
typedef  int /*<<< orphan*/  SIZE_T ;

/* Variables and functions */
 int /*<<< orphan*/  COMP (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEN ; 
 char* dest ; 
 int /*<<< orphan*/  pRtlCompareMemory ; 
 char* src ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlCompareMemory(void)
{
  SIZE_T size;

  if (!pRtlCompareMemory)
  {
    win_skip("RtlCompareMemory is not available\n");
    return;
  }

  strcpy(dest, src);

  COMP(src,src,0,0);
  COMP(src,src,LEN,LEN);
  dest[0] = 'x';
  COMP(src,dest,LEN,0);
}