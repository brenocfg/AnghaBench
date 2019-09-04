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
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  MONTHCAL_CompareSystemTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MONTHCAL_CopyDate (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_null ; 

__attribute__((used)) static LONG MONTHCAL_CompareDate(const SYSTEMTIME *first, const SYSTEMTIME *second)
{
  SYSTEMTIME st_first, st_second;

  st_first = st_second = st_null;
  MONTHCAL_CopyDate(first, &st_first);
  MONTHCAL_CopyDate(second, &st_second);

  return MONTHCAL_CompareSystemTime(&st_first, &st_second);
}