#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
struct TYPE_6__ {TYPE_1__ data; } ;
typedef  TYPE_2__ Entry ;

/* Variables and functions */
 int compareType (TYPE_1__ const*,TYPE_1__ const*) ; 
 int lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compareName(const void* arg1, const void* arg2)
{
	const WIN32_FIND_DATAW* fd1 = &(*(const Entry* const*)arg1)->data;
	const WIN32_FIND_DATAW* fd2 = &(*(const Entry* const*)arg2)->data;

	int cmp = compareType(fd1, fd2);
	if (cmp)
		return cmp;

	return lstrcmpiW(fd1->cFileName, fd2->cFileName);
}