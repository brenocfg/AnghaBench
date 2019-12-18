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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CheckedCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int,int,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void DataSharedMem( FILE *p_cmd, FILE *p_res, int i_overlay, int i_width,
                    int i_height, char *psz_format, int i_shmid ) {

    printf( "Sending data via shared memory..." );
    CheckedCommand( p_cmd, p_res, "DataSharedMem %d %d %d %s %d\n", i_overlay,
                    i_width, i_height, psz_format, i_shmid );
    printf( " done\n" );
}