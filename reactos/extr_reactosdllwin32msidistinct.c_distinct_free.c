#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* nextcol; struct TYPE_4__* nextrow; } ;
typedef  TYPE_1__ DISTINCTSET ;

/* Variables and functions */
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 

__attribute__((used)) static void distinct_free( DISTINCTSET *x )
{
    while( x )
    {
        DISTINCTSET *next = x->nextrow;
        distinct_free( x->nextcol );
        msi_free( x );
        x = next;
    }
}