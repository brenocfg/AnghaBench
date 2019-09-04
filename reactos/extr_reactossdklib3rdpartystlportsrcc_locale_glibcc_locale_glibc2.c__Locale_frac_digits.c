#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _Locale_monetary {int dummy; } ;
typedef  TYPE_1__* locale_t ;
struct TYPE_3__ {char** __names; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAC_DIGITS ; 
 size_t LC_MONETARY ; 
 char* nl_langinfo_l (int /*<<< orphan*/ ,TYPE_1__*) ; 

char _Locale_frac_digits(struct _Locale_monetary *__loc)
{
  /* We are forced to manually handled the "C" locale for consistency with
   * the default implementation in STLport. */
  const char* lname = ((locale_t)__loc)->__names[LC_MONETARY];
  if (lname[0] == 'C' && lname[1] == 0)
    return 0;
  return *(nl_langinfo_l(FRAC_DIGITS, (locale_t)__loc));
}