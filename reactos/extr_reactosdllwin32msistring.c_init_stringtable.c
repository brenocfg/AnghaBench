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
struct msistring {int dummy; } ;
struct TYPE_5__ {int maxcount; int freeslot; scalar_t__ sortcount; int /*<<< orphan*/  codepage; struct TYPE_5__* strings; void* sorted; } ;
typedef  TYPE_1__ string_table ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 void* msi_alloc (int) ; 
 TYPE_1__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  validate_codepage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static string_table *init_stringtable( int entries, UINT codepage )
{
    string_table *st;

    if (!validate_codepage( codepage ))
        return NULL;

    st = msi_alloc( sizeof (string_table) );
    if( !st )
        return NULL;    
    if( entries < 1 )
        entries = 1;

    st->strings = msi_alloc_zero( sizeof(struct msistring) * entries );
    if( !st->strings )
    {
        msi_free( st );
        return NULL;    
    }

    st->sorted = msi_alloc( sizeof (UINT) * entries );
    if( !st->sorted )
    {
        msi_free( st->strings );
        msi_free( st );
        return NULL;
    }

    st->maxcount = entries;
    st->freeslot = 1;
    st->codepage = codepage;
    st->sortcount = 0;

    return st;
}