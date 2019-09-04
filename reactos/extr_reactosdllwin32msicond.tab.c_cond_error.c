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
typedef  int /*<<< orphan*/  COND_input ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,char const*) ; 

__attribute__((used)) static int cond_error( COND_input *info, const char *str )
{
    TRACE("%s\n", str );
    return 0;
}