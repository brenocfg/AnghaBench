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
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_5__ {TYPE_1__ lc; } ;
typedef  TYPE_2__ _Locale_monetary_t ;

/* Variables and functions */
 int CHAR_MAX ; 
 int /*<<< orphan*/  GetLocaleInfoA (scalar_t__,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ INVARIANT_LCID ; 
 int /*<<< orphan*/  LOCALE_INEGSIGNPOSN ; 
 int atoi (char*) ; 

int _Locale_n_sign_posn(_Locale_monetary_t * lmon) {
  char loc_data[2];
  if (lmon->lc.id != INVARIANT_LCID) {
    GetLocaleInfoA(lmon->lc.id, LOCALE_INEGSIGNPOSN, loc_data, 2);
    return atoi(loc_data);
  }
  else {
    return CHAR_MAX;
  }
}