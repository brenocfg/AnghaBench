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
struct TYPE_5__ {TYPE_1__ lc; int /*<<< orphan*/  cp; } ;
typedef  TYPE_2__ _Locale_ctype_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CP_LEN ; 
 char const* __GetLocaleName (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  my_ltoa (int /*<<< orphan*/ ,char*) ; 

char const* _Locale_ctype_name(const _Locale_ctype_t* ltype, char* buf) {
  char cp_buf[MAX_CP_LEN + 1];
  my_ltoa(ltype->cp, cp_buf);
  return __GetLocaleName(ltype->lc.id, cp_buf, buf);
}