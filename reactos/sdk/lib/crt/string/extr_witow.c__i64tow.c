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
typedef  scalar_t__ wchar_t ;
typedef  unsigned int __int64 ;

/* Variables and functions */
 int /*<<< orphan*/  EDOM ; 
 int /*<<< orphan*/  _set_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 

wchar_t* _i64tow(__int64 value, wchar_t* string, int radix)
{
  wchar_t tmp[65];
  wchar_t* tp = tmp;
  int i;
  unsigned v;
  int sign;
  wchar_t* sp;

  if (radix > 36 || radix <= 1) {
    _set_errno(EDOM);
    return 0;
  }

  sign = (radix == 10 && value < 0);
  if (sign)
    v = -value;
  else
    v = (unsigned)value;
  while (v || tp == tmp) {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+L'0';
    else
      *tp++ = i + L'a' - 10;
  }

  if (string == 0)
    string = (wchar_t*)malloc(((tp-tmp)+sign+1)*sizeof(wchar_t));
  sp = string;

  if (sign)
    *sp++ = L'-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
  return string;
}