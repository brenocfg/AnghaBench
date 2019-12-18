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
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 unsigned int VAR_COUNT ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** psz_var_name ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,char*) ; 
 char* var_GetNonEmptyString (int /*<<< orphan*/ *,char*) ; 
 char* var_GetString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void test_strings( libvlc_int_t *p_libvlc )
{
    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_Create( p_libvlc, psz_var_name[i], VLC_VAR_STRING );

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_SetString( p_libvlc, psz_var_name[i], psz_var_name[i] );

    for( unsigned i = 0; i < VAR_COUNT; i++ )
    {
        char *psz_tmp = var_GetString( p_libvlc, psz_var_name[i] );

        assert( psz_tmp != NULL );
        assert( !strcmp( psz_tmp, psz_var_name[i] ) );
        free( psz_tmp );
    }

    for( unsigned i = 0; i < VAR_COUNT; i++ )
        var_Destroy( p_libvlc, psz_var_name[i] );

    /* Some more test for strings */
    var_Create( p_libvlc, "bla", VLC_VAR_STRING );
    assert( var_GetNonEmptyString( p_libvlc, "bla" ) == NULL );
    var_SetString( p_libvlc, "bla", "" );
    assert( var_GetNonEmptyString( p_libvlc, "bla" ) == NULL );
    var_SetString( p_libvlc, "bla", "test" );

    char *psz_tmp = var_GetNonEmptyString( p_libvlc, "bla" );
    assert( psz_tmp != NULL );
    assert( !strcmp( psz_tmp, "test" ) );
    free( psz_tmp );
    var_Destroy( p_libvlc, "bla" );
}