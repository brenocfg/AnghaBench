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
typedef  int /*<<< orphan*/  GRegex ;

/* Variables and functions */
 int G_REGEX_CASELESS ; 
 int G_REGEX_OPTIMIZE ; 
 int /*<<< orphan*/ * g_regex_new (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline GRegex * R ( const char *s, int case_sensitive  )
{
    return g_regex_new ( s, G_REGEX_OPTIMIZE | ( ( case_sensitive ) ? 0 : G_REGEX_CASELESS ), 0, NULL );
}