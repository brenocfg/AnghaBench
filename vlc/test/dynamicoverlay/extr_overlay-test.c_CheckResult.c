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
 scalar_t__ IsFailure (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  printf (char*) ; 

void CheckResult( FILE *p_res ) {
    char psz_resp[9];

    fscanf( p_res, "%8s", &psz_resp );
    if( IsFailure( psz_resp ) ) {
        printf( " failed\n" );
        exit( -1 );
    }
}