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

/* Variables and functions */
 scalar_t__* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,size_t) ; 

wchar_t* wcsndup(wchar_t* name, size_t len)
{
   wchar_t *s = malloc((len + 1) * sizeof(wchar_t));
   if (s != NULL)
   {
      memcpy(s, name, len*sizeof(wchar_t));
      s[len] = 0;
   }
   return s;
}