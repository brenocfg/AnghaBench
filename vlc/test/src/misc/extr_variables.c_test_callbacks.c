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
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_2__ {int i_int; } ;

/* Variables and functions */
 unsigned int VAR_COUNT ; 
 int /*<<< orphan*/  VLC_VAR_INTEGER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  callback ; 
 int /*<<< orphan*/ * psz_var_name ; 
 int rand () ; 
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_TriggerCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* var_value ; 

__attribute__((used)) static void test_callbacks( libvlc_int_t *p_libvlc )
{
    /* add the callbacks */
    for( unsigned i = 0; i < VAR_COUNT; i++ )
    {
        var_Create( p_libvlc, psz_var_name[i], VLC_VAR_INTEGER );
        var_AddCallback( p_libvlc, psz_var_name[i], callback, psz_var_name );
    }

    /* Set the variables and trigger the callbacks */
    for( unsigned i = 0; i < VAR_COUNT; i++ )
    {
        int i_temp = rand();
        var_SetInteger( p_libvlc, psz_var_name[i], i_temp );
        assert( i_temp == var_value[i].i_int );
        var_SetInteger( p_libvlc, psz_var_name[i], 0 );
        assert( var_value[i].i_int == 0 );
        var_value[i].i_int = 1;
    }

    /* Only trigger the callback: the value will be 0 again */
    for( unsigned i = 0; i < VAR_COUNT; i++ )
    {
        var_TriggerCallback( p_libvlc, psz_var_name[i] );
        assert( var_value[i].i_int == 0 );
    }

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_Destroy( p_libvlc, psz_var_name[i] );
}