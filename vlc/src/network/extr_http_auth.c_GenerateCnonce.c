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
struct md5_s {int dummy; } ;
typedef  int /*<<< orphan*/  ps_random ;

/* Variables and functions */
 int /*<<< orphan*/  AddMD5 (struct md5_s*,char*,int) ; 
 int /*<<< orphan*/  EndMD5 (struct md5_s*) ; 
 int /*<<< orphan*/  InitMD5 (struct md5_s*) ; 
 char* psz_md5_hash (struct md5_s*) ; 
 int /*<<< orphan*/  vlc_rand_bytes (char*,int) ; 

__attribute__((used)) static char *GenerateCnonce()
{
    char ps_random[32];
    struct md5_s md5;

    vlc_rand_bytes( ps_random, sizeof( ps_random ) );

    InitMD5( &md5 );
    AddMD5( &md5, ps_random, sizeof( ps_random ) );
    EndMD5( &md5 );

    return psz_md5_hash( &md5 );
}