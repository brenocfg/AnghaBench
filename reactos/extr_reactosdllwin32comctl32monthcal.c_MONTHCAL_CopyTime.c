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
struct TYPE_4__ {int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */

__attribute__((used)) static void MONTHCAL_CopyTime(const SYSTEMTIME *from, SYSTEMTIME *to)
{
  to->wHour   = from->wHour;
  to->wMinute = from->wMinute;
  to->wSecond = from->wSecond;
}