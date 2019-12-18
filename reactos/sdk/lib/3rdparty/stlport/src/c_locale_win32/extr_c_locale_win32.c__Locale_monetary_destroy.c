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
struct TYPE_4__ {struct TYPE_4__* grouping; } ;
typedef  TYPE_1__ _Locale_monetary_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void _Locale_monetary_destroy(_Locale_monetary_t* lmon) {
  if (!lmon) return;

  if (lmon->grouping) free(lmon->grouping);
  free(lmon);
}