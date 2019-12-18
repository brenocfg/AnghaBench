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
struct TYPE_4__ {char* (* _get_message ) (TYPE_1__ const*) ;} ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 char* stub1 (TYPE_1__ const*) ; 

char *mode_get_message ( const Mode *mode )
{
    if ( mode->_get_message ) {
        return mode->_get_message ( mode );
    }
    return NULL;
}