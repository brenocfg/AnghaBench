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
typedef  int _Locale_mask_t ;

/* Variables and functions */
 int _Locale_ALPHA ; 
 int _Locale_CNTRL ; 
 int _Locale_DIGIT ; 
 int _Locale_LOWER ; 
 int _Locale_PRINT ; 
 int _Locale_PUNCT ; 
 int _Locale_SPACE ; 
 int _Locale_UPPER ; 
 int _Locale_XDIGIT ; 
 scalar_t__ iswalpha_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iswcntrl_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iswdigit_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iswlower_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iswprint_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iswpunct_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iswspace_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iswupper_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iswxdigit_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

_Locale_mask_t _WLocale_ctype( struct _Locale_ctype *__loc, wint_t wc, _Locale_mask_t __mask )
{
  _Locale_mask_t ret = 0;
  if ((__mask & _Locale_ALPHA) != 0 && iswalpha_l(wc, (locale_t)__loc))
    ret |= _Locale_ALPHA;
  
  if ((__mask & _Locale_CNTRL) != 0 && iswcntrl_l(wc, (locale_t)__loc))
    ret |= _Locale_CNTRL;

  if ((__mask & _Locale_DIGIT) != 0 && iswdigit_l(wc, (locale_t)__loc))
    ret |= _Locale_DIGIT;

  if ((__mask & _Locale_PRINT) != 0 && iswprint_l(wc, (locale_t)__loc)) 
    ret |= _Locale_PRINT;

  if ((__mask & _Locale_PUNCT) != 0 && iswpunct_l(wc, (locale_t)__loc))
    ret |= _Locale_PUNCT;

  if ((__mask & _Locale_SPACE) != 0 && iswspace_l(wc, (locale_t)__loc))
    ret |= _Locale_SPACE;

  if ((__mask & _Locale_XDIGIT) != 0 && iswxdigit_l(wc, (locale_t)__loc))
    ret |= _Locale_XDIGIT;

  if ((__mask & _Locale_UPPER) != 0 && iswupper_l(wc, (locale_t)__loc))
    ret |= _Locale_UPPER;

  if ((__mask & _Locale_LOWER) != 0 && iswlower_l(wc, (locale_t)__loc))
    ret |= _Locale_LOWER;

  return ret;
}