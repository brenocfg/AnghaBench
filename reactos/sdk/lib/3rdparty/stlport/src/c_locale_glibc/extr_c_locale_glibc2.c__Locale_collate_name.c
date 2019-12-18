#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _Locale_collate {int dummy; } ;
typedef  TYPE_1__* locale_t ;
struct TYPE_2__ {char const** __names; } ;

/* Variables and functions */
 size_t LC_COLLATE ; 

char const*_Locale_collate_name( const struct _Locale_collate *__loc, char *buf )
{
  return ((locale_t)__loc)->__names[LC_COLLATE];
}