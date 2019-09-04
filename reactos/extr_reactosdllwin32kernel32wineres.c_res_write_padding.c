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
typedef  int DWORD ;
typedef  char BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static void res_write_padding( BYTE *res_base, DWORD size )
{
    static const BYTE pad[] = {
        'P','A','D','D','I','N','G','X','X','P','A','D','D','I','N','G' };
    DWORD i;

    for ( i = 0; i < size / sizeof pad; i++ )
        memcpy( &res_base[i*sizeof pad], pad, sizeof pad );
    memcpy( &res_base[i*sizeof pad], pad, size%sizeof pad );
}