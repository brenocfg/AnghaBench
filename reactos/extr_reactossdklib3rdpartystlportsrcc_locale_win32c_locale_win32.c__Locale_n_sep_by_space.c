#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ lc; } ;
typedef  TYPE_2__ _Locale_monetary_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocaleInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  LOCALE_INEGSEPBYSPACE ; 

int _Locale_n_sep_by_space(_Locale_monetary_t * lmon) {
  char loc_data[2];
  GetLocaleInfoA(lmon->lc.id, LOCALE_INEGSEPBYSPACE, loc_data, 2);
  if (loc_data[0] == '0') return 0;
  else if (loc_data[0] == '1') return 1;
  else return -1;
}