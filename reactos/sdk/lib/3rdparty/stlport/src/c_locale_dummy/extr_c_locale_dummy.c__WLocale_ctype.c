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
 scalar_t__ iswalpha (int /*<<< orphan*/ ) ; 
 scalar_t__ iswcntrl (int /*<<< orphan*/ ) ; 
 scalar_t__ iswdigit (int /*<<< orphan*/ ) ; 
 scalar_t__ iswlower (int /*<<< orphan*/ ) ; 
 scalar_t__ iswprint (int /*<<< orphan*/ ) ; 
 scalar_t__ iswpunct (int /*<<< orphan*/ ) ; 
 scalar_t__ iswspace (int /*<<< orphan*/ ) ; 
 scalar_t__ iswupper (int /*<<< orphan*/ ) ; 
 scalar_t__ iswxdigit (int /*<<< orphan*/ ) ; 

_Locale_mask_t _WLocale_ctype(struct _Locale_ctype *lctype, wint_t wc, _Locale_mask_t mask) {
  _Locale_mask_t ret = 0;
  if ((mask & _Locale_ALPHA) != 0 && iswalpha(wc))
    ret |= _Locale_ALPHA;
  
  if ((mask & _Locale_CNTRL) != 0 && iswcntrl(wc))
    ret |= _Locale_CNTRL;

  if ((mask & _Locale_DIGIT) != 0 && iswdigit(wc))
    ret |= _Locale_DIGIT;

  if ((mask & _Locale_PRINT) != 0 && iswprint(wc)) 
    ret |= _Locale_PRINT;

  if ((mask & _Locale_PUNCT) != 0 && iswpunct(wc))
    ret |= _Locale_PUNCT;

  if ((mask & _Locale_SPACE) != 0 && iswspace(wc))
    ret |= _Locale_SPACE;

  if ((mask & _Locale_XDIGIT) != 0 && iswxdigit(wc))
    ret |= _Locale_XDIGIT;

  if ((mask & _Locale_UPPER) != 0 && iswupper(wc))
    ret |= _Locale_UPPER;

  if ((mask & _Locale_LOWER) != 0 && iswlower(wc))
    ret |= _Locale_LOWER;

  return ret;
}