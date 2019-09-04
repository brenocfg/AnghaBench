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
struct Vector {int current; scalar_t__ pData; } ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int find_data(const struct Vector * v, const BYTE * pData, int size)
{
    int index;
    for (index = 0; index < v->current; index++)
        if (!memcmp(v->pData + index, pData, size))
            return index;
    /* not found */
    return -1;
}