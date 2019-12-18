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
struct TYPE_3__ {int /*<<< orphan*/ * Data4; void* Data3; void* Data2; int /*<<< orphan*/  Data1; } ;
typedef  TYPE_1__ vlc_guid_t ;
typedef  int /*<<< orphan*/  var_buffer_t ;

/* Variables and functions */
 void* var_buffer_get16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_buffer_get32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_buffer_get8 (int /*<<< orphan*/ *) ; 

void var_buffer_getguid( var_buffer_t *p_buf, vlc_guid_t *p_guid )
{
    p_guid->Data1 = var_buffer_get32( p_buf );
    p_guid->Data2 = var_buffer_get16( p_buf );
    p_guid->Data3 = var_buffer_get16( p_buf );

    for( int i = 0; i < 8; i++ )
        p_guid->Data4[i] = var_buffer_get8( p_buf );
}