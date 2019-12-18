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
typedef  int /*<<< orphan*/  Walker ;
typedef  int /*<<< orphan*/  Select ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int WRC_Continue ; 

int sqlite3SelectWalkNoop(Walker *NotUsed, Select *NotUsed2){
  UNUSED_PARAMETER2(NotUsed, NotUsed2);
  return WRC_Continue;
}