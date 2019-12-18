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
typedef  int wchar_t ;
struct TYPE_4__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (int*,TYPE_1__*) ; 
 scalar_t__ FindNextFileW (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ TRUE ; 
 int* _wcsdup (int*) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ wadd (int*) ; 
 int /*<<< orphan*/  wcscpy (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcsncpy (int*,int*,uintptr_t) ; 
 int* wcspbrk (int*,char*) ; 

int wexpand(wchar_t* name, int expand_wildcards)
{
   wchar_t* s;
   WIN32_FIND_DATAW fd;
   HANDLE hFile;
   BOOLEAN first = TRUE;
   wchar_t buffer[MAX_PATH];
   uintptr_t pos;

   if (expand_wildcards && (s = wcspbrk(name, L"*?")))
   {
      hFile = FindFirstFileW(name, &fd);
      if (hFile != INVALID_HANDLE_VALUE)
      {
         while(s != name && *s != L'/' && *s != L'\\')
            s--;
         pos = s - name;
         if (*s == L'/' || *s == L'\\')
            pos++;
         wcsncpy(buffer, name, pos);
         do
         {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
               wcscpy(&buffer[pos], fd.cFileName);
               if (wadd(_wcsdup(buffer)) < 0)
               {
                  FindClose(hFile);
                  return -1;
               }
               first = FALSE;
            }
         }
         while(FindNextFileW(hFile, &fd));
         FindClose(hFile);
      }
   }
   if (first)
   {
      if (wadd(name) < 0)
         return -1;
   }
   else
      free(name);
   return 0;
}