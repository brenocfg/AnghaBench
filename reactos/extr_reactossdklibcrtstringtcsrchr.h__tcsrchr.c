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
typedef  scalar_t__ _XINT ;
typedef  scalar_t__ const _TCHAR ;

/* Variables and functions */

_TCHAR * _tcsrchr(const _TCHAR * s, _XINT c)
{
 _TCHAR cc = c;
 const _TCHAR * sp = (_TCHAR *)0;

 while(*s)
 {
  if(*s == cc) sp = s;
  s ++;
 }

 if(cc == 0) sp = s;

 return (_TCHAR *)sp;
}