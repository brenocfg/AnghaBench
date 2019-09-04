#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dictSize; int /*<<< orphan*/  dictContent; } ;
typedef  TYPE_1__ ZSTD_DDict ;

/* Variables and functions */
 int ZSTD_getDictID_fromDict (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned ZSTD_getDictID_fromDDict(const ZSTD_DDict *ddict)
{
	if (ddict == NULL)
		return 0;
	return ZSTD_getDictID_fromDict(ddict->dictContent, ddict->dictSize);
}