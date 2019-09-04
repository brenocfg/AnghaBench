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
 int /*<<< orphan*/  GetTimeFormatA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char*,int) ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 

char* _strtime(char* time)
{
   static const char format[] = "HH':'mm':'ss";

   GetTimeFormatA(LOCALE_NEUTRAL, 0, NULL, format, time, 9); 

   return time;
}