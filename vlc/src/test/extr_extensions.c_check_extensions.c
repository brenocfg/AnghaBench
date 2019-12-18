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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strcmp (char const* const,char const* const) ; 

__attribute__((used)) static void check_extensions( const char* const* extensions, size_t nb_exts )
{
    for( size_t i = 0; i < nb_exts - 1; i++ )
        assert( strcmp( extensions[i], extensions[i + 1] ) < 0 );
}