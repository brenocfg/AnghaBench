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
struct TYPE_3__ {int /*<<< orphan*/  next_object_id; } ;
typedef  TYPE_1__ GpMetafile ;
typedef  int DWORD ;

/* Variables and functions */
 int EmfPlusObjectTableSize ; 

__attribute__((used)) static DWORD METAFILE_AddObjectId(GpMetafile *metafile)
{
    return (metafile->next_object_id++) % EmfPlusObjectTableSize;
}