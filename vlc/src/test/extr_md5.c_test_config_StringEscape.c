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
struct md5_s {int dummy; } ;
struct TYPE_2__ {char* psz_md5; scalar_t__ psz_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddMD5 (struct md5_s*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndMD5 (struct md5_s*) ; 
 int /*<<< orphan*/  InitMD5 (struct md5_s*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* md5_samples ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* psz_md5_hash (struct md5_s*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static void test_config_StringEscape()
{
    for( int i = 0; md5_samples[i].psz_string; i++ )
    {
        struct md5_s md5;
        InitMD5( &md5 );
        AddMD5( &md5, md5_samples[i].psz_string, strlen( md5_samples[i].psz_string ) );
        EndMD5( &md5 );
        char * psz_hash = psz_md5_hash( &md5 );

        if( strcmp( psz_hash, md5_samples[i].psz_md5 ) )
        {
            printf( "Output: %s\nExpected: %s\n", psz_hash,
                    md5_samples[i].psz_md5 );
            abort();
        }
        free( psz_hash );
    }
}