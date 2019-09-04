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
struct TYPE_3__ {int exflag; int /*<<< orphan*/  crit; } ;
typedef  TYPE_1__ ioinfo ;

/* Variables and functions */
 int EF_CRIT_INIT ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCK_FILES () ; 
 int /*<<< orphan*/  UNLOCK_FILES () ; 

__attribute__((used)) static inline void init_ioinfo_cs(ioinfo *info)
{
    if(!(info->exflag & EF_CRIT_INIT)) {
        LOCK_FILES();
        if(!(info->exflag & EF_CRIT_INIT)) {
            InitializeCriticalSection(&info->crit);
            info->exflag |= EF_CRIT_INIT;
        }
        UNLOCK_FILES();
    }
}