#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  aCksum ;
struct TYPE_4__ {int /*<<< orphan*/  aCksum; } ;
typedef  TYPE_1__ TreeHeader ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  treeHeaderChecksum (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int treeHeaderChecksumOk(TreeHeader *pHdr){
  u32 aCksum[2];
  treeHeaderChecksum(pHdr, aCksum);
  return (0==memcmp(aCksum, pHdr->aCksum, sizeof(aCksum)));
}