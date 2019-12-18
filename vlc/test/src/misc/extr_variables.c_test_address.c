#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ p_address; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_5__ {char* p_address; } ;

/* Variables and functions */
 int VAR_COUNT ; 
 int /*<<< orphan*/  VLC_VAR_ADDRESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * psz_var_name ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* var_value ; 

__attribute__((used)) static void test_address( libvlc_int_t *p_libvlc )
{
    char dummy[VAR_COUNT];

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_Create( p_libvlc, psz_var_name[i], VLC_VAR_ADDRESS );

    for( unsigned i = 0; i < VAR_COUNT; i++ )
    {
        var_value[i].p_address = &dummy[i];
        var_SetAddress( p_libvlc, psz_var_name[i], var_value[i].p_address );
    }

    for( unsigned i = 0; i < VAR_COUNT; i++ )
    {
        vlc_value_t val;
        var_Get( p_libvlc, psz_var_name[i], &val );
        assert( val.p_address == var_value[i].p_address );
    }

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_Destroy( p_libvlc, psz_var_name[i] );
}