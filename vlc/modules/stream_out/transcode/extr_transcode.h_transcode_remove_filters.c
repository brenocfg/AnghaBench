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
typedef  int /*<<< orphan*/  filter_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  filter_chain_Delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void transcode_remove_filters( filter_chain_t **pp )
{
    if( *pp )
    {
        filter_chain_Delete( *pp );
        *pp = NULL;
    }
}