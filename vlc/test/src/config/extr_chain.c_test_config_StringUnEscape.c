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
struct TYPE_2__ {scalar_t__ psz_string; int /*<<< orphan*/  psz_escaped; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  config_StringUnescape (char*) ; 
 TYPE_1__* escape_samples ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_config_StringUnEscape()
{
    for( int i = 0; escape_samples[i].psz_string; i++ )
    {
        char *psz_tmp = strdup( escape_samples[i].psz_escaped );
        config_StringUnescape( psz_tmp );
        assert( !strcmp( psz_tmp, escape_samples[i].psz_string ) );
        free( psz_tmp );
    }
}