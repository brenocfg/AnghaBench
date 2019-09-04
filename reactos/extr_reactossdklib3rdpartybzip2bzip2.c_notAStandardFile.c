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
struct MY_STAT {int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ IntNative ;
typedef  int /*<<< orphan*/  Char ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ MY_LSTAT (int /*<<< orphan*/ *,struct MY_STAT*) ; 
 scalar_t__ MY_S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  True ; 

__attribute__((used)) static 
Bool notAStandardFile ( Char* name )
{
   IntNative      i;
   struct MY_STAT statBuf;

   i = MY_LSTAT ( name, &statBuf );
   if (i != 0) return True;
   if (MY_S_ISREG(statBuf.st_mode)) return False;
   return True;
}