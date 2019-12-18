#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* (* get_name ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ ar_archive ;

/* Variables and functions */
 char const* stub1 (TYPE_1__*) ; 

const char *ar_entry_get_name(ar_archive *ar)
{
    return ar->get_name(ar);
}