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
struct TYPE_3__ {int HasStream; scalar_t__ MTimeDefined; scalar_t__ CrcDefined; scalar_t__ IsAnti; scalar_t__ IsDir; } ;
typedef  TYPE_1__ CSzFileItem ;

/* Variables and functions */

void SzFile_Init(CSzFileItem *p)
{
  p->HasStream = 1;
  p->IsDir = 0;
  p->IsAnti = 0;
  p->CrcDefined = 0;
  p->MTimeDefined = 0;
}