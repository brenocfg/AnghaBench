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
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int lstrlenA (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static CHAR *heap_strdup(const CHAR *str)
{
    int len = lstrlenA(str) + 1;
    CHAR *ret = heap_alloc(len * sizeof(CHAR));
    lstrcpyA(ret, str);
    return ret;
}