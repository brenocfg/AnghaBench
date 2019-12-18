#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; int fileCount; TYPE_1__* files; } ;
struct TYPE_5__ {int fileCount; scalar_t__ files; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/ * patches; } ;
typedef  TYPE_1__ PatchedFile ;
typedef  int /*<<< orphan*/  PatchedByte ;
typedef  TYPE_2__ Patch ;

/* Variables and functions */
 int SIZEOF_PATCH_BUFFER_MAGIC ; 
 TYPE_3__ m_patch ; 
 char* m_patchBuffer ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
loadPatch()
{
   char *p;
   Patch *patch;
   int i;

   p = m_patchBuffer + SIZEOF_PATCH_BUFFER_MAGIC;
   patch = (Patch *)p;

   if (patch->name == NULL)
   {
      return -1;
   }

   m_patch.name = p + (intptr_t)patch->name;
   m_patch.fileCount = patch->fileCount;
   m_patch.files = (PatchedFile *)(p + (intptr_t)patch->files);

   for (i = 0; i < m_patch.fileCount; i++)
   {
      m_patch.files[i].name = p + (intptr_t)m_patch.files[i].name;
      m_patch.files[i].patches = (PatchedByte *)(p + (intptr_t)m_patch.files[i].patches);
   }

   printf("Patch %s loaded...\n", m_patch.name);
   return 0;
}