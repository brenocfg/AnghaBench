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
typedef  int /*<<< orphan*/  realdir ;

/* Variables and functions */
 int /*<<< orphan*/  CCHMAXPATH ; 
 char* FromLocaleDup (char*) ; 
 char* config_GetBaseDir () ; 
 int /*<<< orphan*/  config_GetRelDir (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *config_GetRealDir( const char *dir )
{
    char realdir[ CCHMAXPATH + 4 ];

    snprintf( realdir, sizeof( realdir ), "%s%s",
              config_GetBaseDir(), config_GetRelDir( dir ));

    return FromLocaleDup( realdir );
}