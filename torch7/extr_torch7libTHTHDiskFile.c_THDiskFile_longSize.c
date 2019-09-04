#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int longSize; int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  THFile ;
typedef  TYPE_1__ THDiskFile ;

/* Variables and functions */
 int /*<<< orphan*/  THArgCheck (int,int,char*) ; 

void THDiskFile_longSize(THFile *self, int size)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(size == 0 || size == 4 || size == 8, 1, "Invalid long size specified");
  dfself->longSize = size;
}