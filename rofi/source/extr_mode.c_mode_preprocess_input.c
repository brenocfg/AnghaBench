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
struct TYPE_4__ {char* (* _preprocess_input ) (TYPE_1__*,char const*) ;} ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 char* g_strdup (char const*) ; 
 char* stub1 (TYPE_1__*,char const*) ; 

char * mode_preprocess_input ( Mode *mode, const char *input )
{
    if ( mode->_preprocess_input ) {
        return mode->_preprocess_input ( mode, input );
    }
    return g_strdup ( input );
}