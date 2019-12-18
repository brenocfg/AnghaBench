#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fileCount; TYPE_1__* files; void* name; } ;
struct TYPE_6__ {struct TYPE_6__* patches; void* name; } ;
typedef  int /*<<< orphan*/  PatchedFile ;

/* Variables and functions */
 int compareFiles (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int m_argc ; 
 void** m_argv ; 
 TYPE_3__ m_patch ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int outputPatch (char const*) ; 
 int /*<<< orphan*/  printUsage () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
createPatch()
{
   int i, status;
   const char *outputFileName;

   /* Check argument count */
   if (m_argc < 6 || (m_argc % 2) != 0)
   {
      printUsage();
      return -1;
   }

   outputFileName = m_argv[3];
   m_patch.name = m_argv[2];

   /* Allocate PatchedFiles array */
   m_patch.fileCount = (m_argc - 4) / 2;
   m_patch.files = malloc(m_patch.fileCount * sizeof (PatchedFile));
   if (m_patch.files == NULL)
   {
      printf("Out of memory!\n");
      return -1;
   }
   memset(m_patch.files, 0, m_patch.fileCount * sizeof (PatchedFile));

   /* Compare original to patched files and fill m_patch.files array */
   for (i = 0; i < m_patch.fileCount; i++)
   {
      m_patch.files[i].name = m_argv[4 + (i * 2) + 1];
      status = compareFiles(m_patch.files + i, m_argv[4 + (i * 2) + 0]);
      if (status < 0)
      {
         for (i = 0; i < m_patch.fileCount; i++)
         {
            if (m_patch.files[i].patches != NULL)
               free(m_patch.files[i].patches);
         }
         free(m_patch.files);
         m_patch.files = NULL;
         m_patch.fileCount = 0;
         return status;
      }
   }

   /* Output patch */
   return outputPatch(outputFileName);
}