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
typedef  int /*<<< orphan*/  VOID ;
typedef  int* PCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

VOID HexDump( PCHAR Data, DWORD Len ) {
    int i;

    for( i = 0; i < Len; i++ ) {
        if( !(i & 0xf) ) {
            if( i ) fprintf(stderr,"\n");
            fprintf(stderr,"%08x:", i);
        }
        fprintf( stderr, " %02x", Data[i] & 0xff );
    }
    fprintf(stderr,"\n");
}