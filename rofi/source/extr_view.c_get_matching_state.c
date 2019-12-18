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
struct TYPE_2__ {scalar_t__ sort; scalar_t__ case_sensitive; } ;

/* Variables and functions */
 TYPE_1__ config ; 

__attribute__((used)) static char * get_matching_state ( void )
{
    if ( config.case_sensitive ) {
        if ( config.sort ) {
            return "±";
        }
        else {
            return "-";
        }
    }
    else{
        if ( config.sort ) {
            return "+";
        }
    }
    return " ";
}