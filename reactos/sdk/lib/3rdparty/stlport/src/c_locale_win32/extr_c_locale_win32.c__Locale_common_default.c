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

/* Variables and functions */
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  MAX_CP_LEN ; 
 int __GetDefaultCP (int /*<<< orphan*/ ) ; 
 char const* __GetLocaleName (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  my_ltoa (int,char*) ; 

__attribute__((used)) static const char* _Locale_common_default(char* buf) {
  char cp[MAX_CP_LEN + 1];
  int CodePage = __GetDefaultCP(LOCALE_USER_DEFAULT);
  my_ltoa(CodePage, cp);
  return __GetLocaleName(LOCALE_USER_DEFAULT, cp, buf);
}