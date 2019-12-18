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
typedef  int /*<<< orphan*/  gint ;
typedef  char* gconstpointer ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static gint
compare_paths (gconstpointer a, gconstpointer b)
{
    const char *patha = a, *pathb = b;

    return strcmp (patha, pathb);
}