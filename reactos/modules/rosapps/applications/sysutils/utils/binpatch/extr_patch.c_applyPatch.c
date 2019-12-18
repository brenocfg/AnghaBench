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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_6__ {char* name; int fileCount; TYPE_2__* files; } ;
struct TYPE_5__ {char* name; size_t fileSize; int patchCount; TYPE_1__* patches; } ;
struct TYPE_4__ {int offset; unsigned char expected; unsigned char patched; } ;

/* Variables and functions */
 int MAX_PATH ; 
 scalar_t__ _access (char*,int /*<<< orphan*/ ) ; 
 int _getch () ; 
 int /*<<< orphan*/  _snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* loadFile (char const*,size_t*) ; 
 scalar_t__ loadPatch () ; 
 int m_argc ; 
 int /*<<< orphan*/ * m_argv ; 
 TYPE_3__ m_patch ; 
 int /*<<< orphan*/  printUsage () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ saveFile (char const*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stdin ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
applyPatch()
{
   int c, i, j, makeBackup;
   size_t fileSize;
   unsigned char *file;
   char *p;
   const char *fileName;
   char buffer[MAX_PATH];


   if (m_argc > 1 && strcmp(m_argv[1], "-d") != 0)
   {
      printUsage();
      return -1;
   }

   /* Load patch */
   if (loadPatch() < 0)
   {
      printf("This executable doesn't contain a patch, use -c to create one.\n");
      return -1;
   }

   if (m_argc > 1)
   {
      /* Dump patch */
      printf("Patch name: %s\n", m_patch.name);
      printf("File count: %d\n", m_patch.fileCount);
      for (i = 0; i < m_patch.fileCount; i++)
      {
         printf("----------------------\n"
                "File name:   %s\n"
                "File size:   %Id bytes\n",
                m_patch.files[i].name, m_patch.files[i].fileSize);
         printf("Patch count: %d\n", m_patch.files[i].patchCount);
         for (j = 0; j < m_patch.files[i].patchCount; j++)
         {
            printf("  Offset 0x%Ix   0x%02x -> 0x%02x\n",
                   m_patch.files[i].patches[j].offset,
                   m_patch.files[i].patches[j].expected,
                   m_patch.files[i].patches[j].patched);
         }
      }
   }
   else
   {
      /* Apply patch */
      printf("Applying patch...\n");
      for (i = 0; i < m_patch.fileCount; i++)
      {
         /* Load original file */
         fileName = m_patch.files[i].name;
applyPatch_retry_file:
         file = loadFile(fileName, &fileSize);
         if (file == NULL)
         {
            printf("File %s not found! ", fileName);
applyPatch_file_open_error:
            printf("(S)kip, (R)etry, (A)bort, (M)anually enter filename");
            do
            {
               c = _getch();
            }
            while (c != 's' && c != 'r' && c != 'a' && c != 'm');
            printf("\n");
            if (c == 's')
            {
               continue;
            }
            else if (c == 'r')
            {
               goto applyPatch_retry_file;
            }
            else if (c == 'a')
            {
               return 0;
            }
            else if (c == 'm')
            {
               if (fgets(buffer, sizeof (buffer), stdin) == NULL)
               {
                  printf("fgets() failed!\n");
                  return -1;
               }
               p = strchr(buffer, '\r');
               if (p != NULL)
                  *p = '\0';
               p = strchr(buffer, '\n');
               if (p != NULL)
                  *p = '\0';

               fileName = buffer;
               goto applyPatch_retry_file;
            }
         }

         /* Check file size */
         if (fileSize != m_patch.files[i].fileSize)
         {
            free(file);
            printf("File %s has unexpected filesize of %Id bytes (%Id bytes expected)\n",
                   fileName, fileSize, m_patch.files[i].fileSize);
            if (fileName != m_patch.files[i].name) /* manually entered filename */
            {
               goto applyPatch_file_open_error;
            }
            return -1;
         }

         /* Ask for backup */
         printf("Do you want to make a backup of %s? (Y)es, (N)o, (A)bort", fileName);
         do
         {
            c = _getch();
         }
         while (c != 'y' && c != 'n' && c != 'a');
         printf("\n");
         if (c == 'y')
         {
            char buffer[MAX_PATH];
            _snprintf(buffer, MAX_PATH, "%s.bak", fileName);
            buffer[MAX_PATH-1] = '\0';
            makeBackup = 1;
            if (_access(buffer, 0) >= 0) /* file exists */
            {
               printf("File %s already exists, overwrite? (Y)es, (N)o, (A)bort", buffer);
               do
               {
                  c = _getch();
               }
               while (c != 'y' && c != 'n' && c != 'a');
               printf("\n");
               if (c == 'n')
                  makeBackup = 0;
               else if (c == 'a')
               {
                  free(file);
                  return 0;
               }
            }
            if (makeBackup && saveFile(buffer, file, fileSize) < 0)
            {
               free(file);
               return -1;
            }
         }
         else if (c == 'a')
         {
            free(file);
            return 0;
         }

         /* Patch file */
         for (j = 0; j < m_patch.files[i].patchCount; j++)
         {
            int offset = m_patch.files[i].patches[j].offset;
            if (file[offset] != m_patch.files[i].patches[j].expected)
            {
               printf("Unexpected value in file %s at offset 0x%x: expected = 0x%02x, found = 0x%02x\n",
                      fileName, offset, m_patch.files[i].patches[j].expected, file[offset]);
               free(file);
               return -1;
            }
            file[offset] = m_patch.files[i].patches[j].patched;
         }

         /* Save file */
         if (saveFile(fileName, file, fileSize) < 0)
         {
            free(file);
            return -1;
         }
         free(file);
      }

      printf("Patch applied sucessfully!\n");
   }

   return 0;
}