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
typedef  int /*<<< orphan*/  key2 ;
typedef  int /*<<< orphan*/  key1 ;

/* Variables and functions */
 int /*<<< orphan*/  LCMAP_SORTKEY ; 
 int /*<<< orphan*/  LCMapStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,int) ; 
 int strcmp (char*,char*) ; 

__attribute__((used)) static int compare_string3(const void *e1, const void *e2)
{
    const char *s1 = *(const char *const *)e1;
    const char *s2 = *(const char *const *)e2;
    char key1[256], key2[256];

    LCMapStringA(0, LCMAP_SORTKEY, s1, -1, key1, sizeof(key1));
    LCMapStringA(0, LCMAP_SORTKEY, s2, -1, key2, sizeof(key2));
    return strcmp(key1, key2);
}