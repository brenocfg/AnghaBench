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
typedef  int /*<<< orphan*/  _Locale_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  _Locale_ALPHA ; 
 int /*<<< orphan*/  _Locale_CNTRL ; 
 int /*<<< orphan*/  _Locale_DIGIT ; 
 int /*<<< orphan*/  _Locale_LOWER ; 
 int /*<<< orphan*/  _Locale_PRINT ; 
 int /*<<< orphan*/  _Locale_PUNCT ; 
 int /*<<< orphan*/  _Locale_SPACE ; 
 int /*<<< orphan*/  _Locale_UPPER ; 
 int /*<<< orphan*/  _Locale_XDIGIT ; 
 int /*<<< orphan*/ * ctable ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ iscntrl (char) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ islower (char) ; 
 scalar_t__ isprint (char) ; 
 scalar_t__ ispunct (char) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ isupper (char) ; 
 scalar_t__ isxdigit (char) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void _Locale_init(void) {
  /* Ctype table for the ASCII character set. */
  char c;
  /* We might never reach 128 when char is signed. */
  for (c = 0; /* c != 128 */; ++c) {
    if (isalpha(c)) ctable[(unsigned char)c] |= _Locale_ALPHA;
    if (iscntrl(c)) ctable[(unsigned char)c] |= _Locale_CNTRL;
    if (isdigit(c)) ctable[(unsigned char)c] |= _Locale_DIGIT;
    if (isprint(c)) ctable[(unsigned char)c] |= _Locale_PRINT;
    if (ispunct(c)) ctable[(unsigned char)c] |= _Locale_PUNCT;
    if (isspace(c)) ctable[(unsigned char)c] |= _Locale_SPACE;
    if (isxdigit(c)) ctable[(unsigned char)c] |= _Locale_XDIGIT;
    if (isupper(c)) ctable[(unsigned char)c] |= _Locale_UPPER;
    if (islower(c)) ctable[(unsigned char)c] |= _Locale_LOWER;
    if (c == 127) break;
  }

  /* ASCII is a 7-bit code, so everything else is non-ASCII. */
  memset(&(ctable[128]), 0, 128 * sizeof(_Locale_mask_t));
}