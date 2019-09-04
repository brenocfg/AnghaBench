#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int gint64 ;
struct TYPE_3__ {int tv_sec; int tv_usec; } ;
typedef  TYPE_1__ GTimeVal ;

/* Variables and functions */
 int /*<<< orphan*/  g_get_current_time (TYPE_1__*) ; 

gint64
get_current_time()
{
    GTimeVal tv;
    gint64 t;

    g_get_current_time (&tv);
    t = tv.tv_sec * (gint64)1000000 + tv.tv_usec;
    return t;
}