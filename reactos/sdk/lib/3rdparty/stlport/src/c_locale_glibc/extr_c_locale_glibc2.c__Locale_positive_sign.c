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
struct _Locale_monetary {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  POSITIVE_SIGN ; 
 char const* nl_langinfo_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *_Locale_positive_sign(struct _Locale_monetary *__loc)
{
  return nl_langinfo_l(POSITIVE_SIGN, (locale_t)__loc);
}