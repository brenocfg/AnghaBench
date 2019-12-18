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
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_libvlc_int; } ;
typedef  TYPE_1__ libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_booleans (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_callbacks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_choices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_creation_and_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_floats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_fracts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_limits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  test_strings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_variables( libvlc_instance_t *p_vlc )
{
    libvlc_int_t *p_libvlc = p_vlc->p_libvlc_int;
    srand( time( NULL ) );

    test_log( "Testing for integers\n" );
    test_integer( p_libvlc );

    test_log( "Testing for booleans\n" );
    test_booleans( p_libvlc );

    test_log( "Testing for floats\n" );
    test_floats( p_libvlc );

    test_log( "Testing for rationals\n" );
    test_fracts( p_libvlc );

    test_log( "Testing for strings\n" );
    test_strings( p_libvlc );

    test_log( "Testing for addresses\n" );
    test_address( p_libvlc );

    test_log( "Testing the callbacks\n" );
    test_callbacks( p_libvlc );

    test_log( "Testing the limits\n" );
    test_limits( p_libvlc );

    test_log( "Testing choices\n" );
    test_choices( p_libvlc );

    test_log( "Testing var_Change()\n" );
    test_change( p_libvlc );

    test_log( "Testing type at creation\n" );
    test_creation_and_type( p_libvlc );
}