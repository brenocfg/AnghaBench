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
struct TYPE_3__ {struct TYPE_3__* name; scalar_t__ handle; } ;
typedef  int /*<<< orphan*/  THFile ;
typedef  TYPE_1__ THDiskFile ;

/* Variables and functions */
 int /*<<< orphan*/  THFree (TYPE_1__*) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 

__attribute__((used)) static void THDiskFile_free(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  if(dfself->handle)
    fclose(dfself->handle);
  THFree(dfself->name);
  THFree(dfself);
}