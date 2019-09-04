#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  wDayOfWeek; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */

__attribute__((used)) static void MONTHCAL_CopyDate(const SYSTEMTIME *from, SYSTEMTIME *to)
{
  to->wYear  = from->wYear;
  to->wMonth = from->wMonth;
  to->wDay   = from->wDay;
  to->wDayOfWeek = from->wDayOfWeek;
}