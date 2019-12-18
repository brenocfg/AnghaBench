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
struct TYPE_2__ {scalar_t__ i_channel; scalar_t__ psz_name; } ;
typedef  TYPE_1__ scan_service_t ;

/* Variables and functions */
 int strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ScanServiceCmp( const void *a, const void *b )
{
    const scan_service_t *sa = *((const scan_service_t**)a);
    const scan_service_t *sb = *((const scan_service_t**)b);

    if( sa->i_channel == sb->i_channel )
    {
        if( sa->psz_name && sb->psz_name )
            return strcmp( sa->psz_name, sb->psz_name );
        return 0;
    }

    if( sa->i_channel < sb->i_channel )
        return -1;
    else if( sa->i_channel > sb->i_channel )
        return 1;
    return 0;
}