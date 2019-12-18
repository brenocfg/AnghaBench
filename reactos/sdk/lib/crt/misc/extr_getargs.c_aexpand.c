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
struct TYPE_4__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAA ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileA (char*,TYPE_1__*) ; 
 scalar_t__ FindNextFileA (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ TRUE ; 
 char* _strdup (char*) ; 
 scalar_t__ aadd (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,uintptr_t) ; 
 char* strpbrk (char*,char*) ; 

int aexpand(char* name, int expand_wildcards)
{
   char* s;
   WIN32_FIND_DATAA fd;
   HANDLE hFile;
   BOOLEAN first = TRUE;
   char buffer[MAX_PATH];
   uintptr_t pos;

   if (expand_wildcards && (s = strpbrk(name, "*?")))
   {
      hFile = FindFirstFileA(name, &fd);
      if (hFile != INVALID_HANDLE_VALUE)
      {
         while(s != name && *s != '/' && *s != '\\')
            s--;
         pos = s - name;
         if (*s == '/' || *s == '\\')
            pos++;
         strncpy(buffer, name, pos);
         do
         {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
               strcpy(&buffer[pos], fd.cFileName);
               if (aadd(_strdup(buffer)) < 0)
               {
                  FindClose(hFile);
                  return -1;
               }
               first = FALSE;
            }
         }
         while(FindNextFileA(hFile, &fd));
         FindClose(hFile);
      }
   }
   if (first)
   {
      if (aadd(name) < 0)
         return -1;
   }
   else
      free(name);
   return 0;
}