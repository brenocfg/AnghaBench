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
struct query {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_query (struct query*) ; 

void release_query( struct query *query )
{
    if (!InterlockedDecrement( &query->refs )) free_query( query );
}