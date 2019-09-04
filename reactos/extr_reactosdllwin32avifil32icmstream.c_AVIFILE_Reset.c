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
struct TYPE_3__ {int lCurrent; scalar_t__ dwUnusedBytes; int /*<<< orphan*/  dwLastQuality; scalar_t__ lLastKey; } ;
typedef  TYPE_1__ IAVIStreamImpl ;

/* Variables and functions */
 int /*<<< orphan*/  ICQUALITY_HIGH ; 

__attribute__((used)) static inline void AVIFILE_Reset(IAVIStreamImpl *This)
{
  This->lCurrent      = -1;
  This->lLastKey      = 0;
  This->dwLastQuality = ICQUALITY_HIGH;
  This->dwUnusedBytes = 0;
}