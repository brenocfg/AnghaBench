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
struct TYPE_4__ {size_t (* get_comment ) (TYPE_1__*,void*,size_t) ;} ;
typedef  TYPE_1__ ar_archive ;

/* Variables and functions */
 size_t stub1 (TYPE_1__*,void*,size_t) ; 

size_t ar_get_global_comment(ar_archive *ar, void *buffer, size_t count)
{
    if (!ar->get_comment)
        return 0;
    return ar->get_comment(ar, buffer, count);
}