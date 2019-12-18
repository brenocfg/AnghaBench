#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ offset; } ;
struct TYPE_5__ {TYPE_1__ pGuidTab; } ;
typedef  TYPE_2__ MSFT_SegDir ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  tlb_lseek (int,scalar_t__) ; 
 int /*<<< orphan*/  tlb_read (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void msft_read_guid(int fd, MSFT_SegDir *segdir, int offset, GUID *guid)
{
    tlb_lseek(fd, segdir->pGuidTab.offset+offset);
    tlb_read(fd, guid, sizeof(GUID));
}