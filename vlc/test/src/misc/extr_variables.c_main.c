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
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * libvlc_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_defaults_args ; 
 int /*<<< orphan*/  test_defaults_nargs ; 
 int /*<<< orphan*/  test_init () ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  test_variables (int /*<<< orphan*/ *) ; 

int main( void )
{
    libvlc_instance_t *p_vlc;

    test_init();

    test_log( "Testing the core variables\n" );
    p_vlc = libvlc_new( test_defaults_nargs, test_defaults_args );
    assert( p_vlc != NULL );

    test_variables( p_vlc );

    libvlc_release( p_vlc );

    return 0;
}