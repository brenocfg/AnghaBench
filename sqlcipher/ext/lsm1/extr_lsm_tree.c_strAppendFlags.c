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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  LsmString ;

/* Variables and functions */
 int /*<<< orphan*/  lsmFlagsToString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lsmStringAppend (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void strAppendFlags(LsmString *pStr, u8 flags){
  char zFlags[8];

  lsmFlagsToString(flags, zFlags);
  zFlags[4] = ':';

  lsmStringAppend(pStr, zFlags, 5);
}