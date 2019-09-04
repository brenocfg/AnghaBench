#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ val; int count; int /*<<< orphan*/ * nextcol; struct TYPE_5__* nextrow; scalar_t__ row; } ;
typedef  TYPE_1__ DISTINCTSET ;

/* Variables and functions */
 TYPE_1__* msi_alloc (int) ; 

__attribute__((used)) static DISTINCTSET ** distinct_insert( DISTINCTSET **x, UINT val, UINT row )
{
    /* horrible O(n) find */
    while( *x )
    {
        if( (*x)->val == val )
        {
            (*x)->count++;
            return x;
        }
        x = &(*x)->nextrow;
    }

    /* nothing found, so add one */
    *x = msi_alloc( sizeof (DISTINCTSET) );
    if( *x )
    {
        (*x)->val = val;
        (*x)->count = 1;
        (*x)->row = row;
        (*x)->nextrow = NULL;
        (*x)->nextcol = NULL;
    }
    return x;
}