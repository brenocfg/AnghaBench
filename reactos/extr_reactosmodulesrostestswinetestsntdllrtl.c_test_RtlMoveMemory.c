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
 int /*<<< orphan*/  COPY (int) ; 
 scalar_t__ dest ; 
 int /*<<< orphan*/  pRtlMoveMemory (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  src ; 
 int /*<<< orphan*/  strcpy (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlMoveMemory(void)
{
  if (!pRtlMoveMemory)
  {
    win_skip("RtlMoveMemory is not available\n");
    return;
  }

  /* Length should be in bytes and not rounded. Use strcmp to ensure we
   * didn't write past the end (it checks for the final NUL left by memset)
   */
  COPY(0); CMP("");
  COPY(1); CMP("T");
  COPY(2); CMP("Th");
  COPY(3); CMP("Thi");
  COPY(4); CMP("This");
  COPY(5); CMP("This ");
  COPY(6); CMP("This i");
  COPY(7); CMP("This is");
  COPY(8); CMP("This is ");
  COPY(9); CMP("This is a");

  /* Overlapping */
  strcpy(dest, src); pRtlMoveMemory(dest, dest + 1, strlen(src) - 1);
  CMP("his is a test!!");
  strcpy(dest, src); pRtlMoveMemory(dest + 1, dest, strlen(src));
  CMP("TThis is a test!");
}