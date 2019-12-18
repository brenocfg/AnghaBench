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
struct index_entry_s {scalar_t__ time; scalar_t__ active; } ;

/* Variables and functions */

__attribute__((used)) static int index_Compare( const void *a_, const void *b_ )
{
    struct index_entry_s *a = (struct index_entry_s *) a_;
    struct index_entry_s *b = (struct index_entry_s *) b_;
    if( a->time == b->time )
    {
        if( a->active > b->active )
            return -1;
        else
            return b->active - a->active;
    }
    else return a->time < b->time ? -1 : 1;
}