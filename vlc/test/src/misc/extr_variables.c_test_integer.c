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
struct TYPE_2__ {scalar_t__ i_int; } ;

/* Variables and functions */
 unsigned int VAR_COUNT ; 
 int /*<<< orphan*/  VLC_VAR_INTEGER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * psz_var_name ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_DecInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ var_GetInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_IncInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* var_value ; 

__attribute__((used)) static void test_integer( libvlc_int_t *p_libvlc )
{
    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_Create( p_libvlc, psz_var_name[i], VLC_VAR_INTEGER );

    for( unsigned i = 0; i < VAR_COUNT; i++ )
    {
        var_value[i].i_int = rand();
        var_SetInteger( p_libvlc, psz_var_name[i], var_value[i].i_int );
    }

    for( unsigned i = 0; i < VAR_COUNT; i++ )
    {
        assert( var_GetInteger( p_libvlc, psz_var_name[i] ) == var_value[i].i_int );
        var_IncInteger( p_libvlc, psz_var_name[i] );
        assert( var_GetInteger( p_libvlc, psz_var_name[i] ) == var_value[i].i_int + 1 );
        var_DecInteger( p_libvlc, psz_var_name[i] );
        assert( var_GetInteger( p_libvlc, psz_var_name[i] ) == var_value[i].i_int );
    }

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_Destroy( p_libvlc, psz_var_name[i] );
}