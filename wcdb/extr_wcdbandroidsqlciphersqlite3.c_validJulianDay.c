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
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */
 scalar_t__ INT_464269060799999 ; 

__attribute__((used)) static int validJulianDay(sqlite3_int64 iJD){
  return iJD>=0 && iJD<=INT_464269060799999;
}