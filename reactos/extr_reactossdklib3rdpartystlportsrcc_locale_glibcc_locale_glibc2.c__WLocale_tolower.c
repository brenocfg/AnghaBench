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
typedef  int /*<<< orphan*/  wint_t ;
struct _Locale_ctype {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  towlower_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

wint_t _WLocale_tolower( struct _Locale_ctype *__loc, wint_t c )
{
  return towlower_l( c, ((locale_t)__loc) );
}