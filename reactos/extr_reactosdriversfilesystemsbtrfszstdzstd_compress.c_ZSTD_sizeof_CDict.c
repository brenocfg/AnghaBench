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
struct TYPE_3__ {size_t workspaceSize; int /*<<< orphan*/  dictContentSize; scalar_t__ dictBuffer; } ;
typedef  TYPE_1__ ZSTD_CDict ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ) ; 

size_t ZSTD_sizeof_CDict(const ZSTD_CDict* cdict)
{
    if (cdict==NULL) return 0;   /* support sizeof on NULL */
    DEBUGLOG(5, "sizeof(*cdict) : %u", (U32)sizeof(*cdict));
    return cdict->workspaceSize + (cdict->dictBuffer ? cdict->dictContentSize : 0) + sizeof(*cdict);
}