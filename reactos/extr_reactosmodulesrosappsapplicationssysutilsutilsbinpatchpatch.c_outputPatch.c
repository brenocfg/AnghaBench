#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fileCount; TYPE_1__* files; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int fileCount; char const* name; TYPE_2__* files; } ;
struct TYPE_6__ {int patchCount; char const* name; int /*<<< orphan*/ * patches; int /*<<< orphan*/  fileSize; } ;
struct TYPE_5__ {int patchCount; int /*<<< orphan*/  patches; int /*<<< orphan*/  name; int /*<<< orphan*/  fileSize; } ;
typedef  TYPE_2__ PatchedFile ;
typedef  int /*<<< orphan*/  PatchedByte ;
typedef  TYPE_3__ Patch ;

/* Variables and functions */
 size_t PATCH_BUFFER_SIZE ; 
 size_t SIZEOF_PATCH_BUFFER_MAGIC ; 
 int /*<<< orphan*/  free (char*) ; 
 char* loadFile (char*,size_t*) ; 
 char** m_argv ; 
 TYPE_4__ m_patch ; 
 int /*<<< orphan*/  m_patchBuffer ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ saveFile (char const*,char*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
outputPatch(const char *outputFileName)
{
   char *patchExe, *patchBuffer = NULL;
   size_t i, size, patchExeSize, patchSize, stringSize, stringOffset, patchOffset;
   Patch *patch;
   PatchedFile *files;

   printf("Putting patch into %s...\n", outputFileName);

   /* Calculate size of the patch */
   patchSize = sizeof (Patch) + sizeof (PatchedFile) * m_patch.fileCount;
   stringSize = strlen(m_patch.name) + 1;
   for (i = 0; i < m_patch.fileCount; i++)
   {
      stringSize += strlen(m_patch.files[i].name) + 1;
      patchSize += sizeof (PatchedByte) * m_patch.files[i].patchCount;
   }
   if ((stringSize + patchSize) > PATCH_BUFFER_SIZE)
   {
      printf("Patch is too big - %u bytes maximum, %Iu bytes needed\n",
             PATCH_BUFFER_SIZE, stringSize + patchSize);
      return -1;
   }

   /* Load patch.exe file into memory... */
   patchExe = loadFile(m_argv[0], &patchExeSize);
   if (patchExe == NULL)
   {
      return -1;
   }

   /* Try to find the magic mark for the patch buffer */
   for (i = 0; i < (patchExeSize - SIZEOF_PATCH_BUFFER_MAGIC); i++)
   {
      if (memcmp(patchExe + i, m_patchBuffer, SIZEOF_PATCH_BUFFER_MAGIC) == 0)
      {
         patchBuffer = patchExe + i + SIZEOF_PATCH_BUFFER_MAGIC;

         break;
      }
   }
   if (!(i < (patchExeSize - SIZEOF_PATCH_BUFFER_MAGIC)))
   {
      free(patchExe);
      printf("Couldn't find patch buffer magic in file %s - this shouldn't happen!!!\n", m_argv[0]);
      return -1;
   }

   /* Pack patch together and replace string pointers by offsets */
   patch = (Patch *)patchBuffer;
   files = (PatchedFile *)(patchBuffer + sizeof (Patch));
   patchOffset = sizeof (Patch) + sizeof (PatchedFile) * m_patch.fileCount;
   stringOffset = patchSize;

   patch->fileCount = m_patch.fileCount;
   patch->files = (PatchedFile *)sizeof (Patch);

   patch->name = (const char *)stringOffset;
   strcpy(patchBuffer + stringOffset, m_patch.name);
   stringOffset += strlen(m_patch.name) + 1;

   for (i = 0; i < m_patch.fileCount; i++)
   {
      files[i].fileSize = m_patch.files[i].fileSize;
      files[i].patchCount = m_patch.files[i].patchCount;

      files[i].name = (const char *)stringOffset;
      strcpy(patchBuffer + stringOffset, m_patch.files[i].name);
      stringOffset += strlen(m_patch.files[i].name) + 1;

      size = files[i].patchCount * sizeof (PatchedByte);
      files[i].patches = (PatchedByte *)patchOffset;
      memcpy(patchBuffer + patchOffset, m_patch.files[i].patches, size);
      patchOffset += size;
   }
   size = patchSize + stringSize;
   memset(patchBuffer + size, 0, PATCH_BUFFER_SIZE - size);

   /* Save file */
   if (saveFile(outputFileName, patchExe, patchExeSize) < 0)
   {
      free(patchExe);
      return -1;
   }
   free(patchExe);

   printf("Patch saved!\n");
   return 0;
}