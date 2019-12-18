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
struct TYPE_3__ {char* psz_string; int b_bool; int /*<<< orphan*/  f_float; void* i_int; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
#define  VLC_VAR_BOOL 131 
#define  VLC_VAR_FLOAT 130 
#define  VLC_VAR_INTEGER 129 
#define  VLC_VAR_STRING 128 
 int config_GetType (char*) ; 
 int /*<<< orphan*/  config_IsSafe (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 void* strtoll (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  us_atof (char*) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  var_Set (int /*<<< orphan*/ *,char*,TYPE_1__) ; 

void var_OptionParse( vlc_object_t *p_obj, const char *psz_option,
                      bool trusted )
{
    char *psz_name, *psz_value;
    int  i_type;
    bool b_isno = false;
    vlc_value_t val;

    val.psz_string = NULL;

    /* It's too much of a hassle to remove the ':' when we parse
     * the cmd line :) */
    if( psz_option[0] == ':' )
        psz_option++;

    if( !psz_option[0] )
        return;

    psz_name = strdup( psz_option );
    if( psz_name == NULL )
        return;

    psz_value = strchr( psz_name, '=' );
    if( psz_value != NULL )
        *psz_value++ = '\0';

    i_type = config_GetType( psz_name );
    if( !i_type && !psz_value )
    {
        /* check for "no-foo" or "nofoo" */
        if( !strncmp( psz_name, "no-", 3 ) )
        {
            memmove( psz_name, psz_name + 3, strlen(psz_name) + 1 - 3 );
        }
        else if( !strncmp( psz_name, "no", 2 ) )
        {
            memmove( psz_name, psz_name + 2, strlen(psz_name) + 1 - 2 );
        }
        else goto cleanup;           /* Option doesn't exist */

        b_isno = true;
        i_type = config_GetType( psz_name );
    }
    if( !i_type ) goto cleanup; /* Option doesn't exist */

    if( ( i_type != VLC_VAR_BOOL ) &&
        ( !psz_value || !*psz_value ) ) goto cleanup; /* Invalid value */

    /* check if option is unsafe */
    if( !trusted && !config_IsSafe( psz_name ) )
    {
        msg_Err( p_obj, "unsafe option \"%s\" has been ignored for "
                        "security reasons", psz_name );
        free( psz_name );
        return;
    }

    /* Create the variable in the input object.
     * Children of the input object will be able to retrieve this value
     * thanks to the inheritance property of the object variables. */
    var_Create( p_obj, psz_name, i_type );

    switch( i_type )
    {
    case VLC_VAR_BOOL:
        if( psz_value )
        {
            char *endptr;
            long long int value = strtoll( psz_value, &endptr, 0 );
            if( endptr == psz_value ) /* Not an integer */
                val.b_bool = strcasecmp( psz_value, "true" ) == 0
                          || strcasecmp( psz_value, "yes" ) == 0;
            else
                val.b_bool = value != 0;
        }
        else
            val.b_bool = !b_isno;
        break;

    case VLC_VAR_INTEGER:
        val.i_int = strtoll( psz_value, NULL, 0 );
        break;

    case VLC_VAR_FLOAT:
        val.f_float = us_atof( psz_value );
        break;

    case VLC_VAR_STRING:
        val.psz_string = psz_value;
        break;

    default:
        goto cleanup;
    }

    var_Set( p_obj, psz_name, val );

cleanup:
    free( psz_name );
}