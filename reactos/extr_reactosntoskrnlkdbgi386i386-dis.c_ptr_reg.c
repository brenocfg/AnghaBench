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
 int AFLAG ; 
 int REX_MODE64 ; 
 int /*<<< orphan*/  USED_REX (int) ; 
 int /*<<< orphan*/  close_char ; 
 int eAX_reg ; 
 char** names16 ; 
 char** names32 ; 
 char** names64 ; 
 int /*<<< orphan*/  oappend (char const*) ; 
 scalar_t__* obufp ; 
 int /*<<< orphan*/  open_char ; 
 int rex ; 

__attribute__((used)) static void
ptr_reg (int code, int sizeflag)
{
  const char *s;

  *obufp++ = open_char;
  USED_REX (REX_MODE64);
  if (rex & REX_MODE64)
    {
      if (!(sizeflag & AFLAG))
	s = names32[code - eAX_reg];
      else
	s = names64[code - eAX_reg];
    }
  else if (sizeflag & AFLAG)
    s = names32[code - eAX_reg];
  else
    s = names16[code - eAX_reg];
  oappend (s);
  *obufp++ = close_char;
  *obufp = 0;
}