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
struct TYPE_2__ {int b_bool; } ;

/* Variables and functions */
 int RAND_MAX ; 
 unsigned int VAR_COUNT ; 
 int /*<<< orphan*/  VLC_VAR_BOOL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * psz_var_name ; 
 int rand () ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ var_GetBool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_ToggleBool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* var_value ; 

__attribute__((used)) static void test_booleans( libvlc_int_t *p_libvlc )
{
    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_Create( p_libvlc, psz_var_name[i], VLC_VAR_BOOL );

    for( unsigned i = 0; i < VAR_COUNT; i++ )
    {
        var_value[i].b_bool = (rand() > RAND_MAX/2);
        var_SetBool( p_libvlc, psz_var_name[i], var_value[i].b_bool );
    }

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        assert( var_GetBool( p_libvlc, psz_var_name[i] ) == var_value[i].b_bool );

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_ToggleBool( p_libvlc, psz_var_name[i] );

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        assert( var_GetBool( p_libvlc, psz_var_name[i] ) != var_value[i].b_bool );

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_Destroy( p_libvlc, psz_var_name[i] );
}