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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  uHit; int /*<<< orphan*/  rc; int /*<<< orphan*/  st; } ;
typedef  TYPE_1__ MCHITTESTINFO ;

/* Variables and functions */
 scalar_t__ MCHITTESTINFO_V1_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline UINT fill_hittest_info(const MCHITTESTINFO *src, MCHITTESTINFO *dest)
{
  dest->uHit = src->uHit;
  dest->st = src->st;

  if (dest->cbSize == sizeof(MCHITTESTINFO))
    memcpy(&dest->rc, &src->rc, sizeof(MCHITTESTINFO) - MCHITTESTINFO_V1_SIZE);

  return src->uHit;
}