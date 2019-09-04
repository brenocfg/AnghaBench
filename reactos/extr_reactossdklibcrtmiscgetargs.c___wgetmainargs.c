#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char wchar_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapValidate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int TRUE ; 
 int __argc ; 
 char** __wargv ; 
 char** __winitenv ; 
 char* _wcmdln ; 
 char* _wcsdup (char*) ; 
 char* _wpgmptr ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (int) ; 
 size_t wcslen (char*) ; 
 int /*<<< orphan*/  wcsndup (char*,int) ; 
 int /*<<< orphan*/  wexpand (int /*<<< orphan*/ ,int) ; 

void __wgetmainargs(int* argc, wchar_t*** wargv, wchar_t*** wenv,
                    int expand_wildcards, int* new_mode)
{
   int i, doexpand, slashesAdded, escapedQuote, inQuotes, bufferIndex, anyLetter;
   size_t len;
   wchar_t* buffer;

   /* missing threading init */

   i = 0;
   doexpand = expand_wildcards;
   escapedQuote = FALSE;
   anyLetter = TRUE;
   slashesAdded = 0;
   inQuotes = 0;
   bufferIndex = 0;

   if (__wargv && __winitenv)
   {
      *wargv = __wargv;
      *wenv = __winitenv;
      *argc = __argc;
      return;
   }

   __argc = 0;

   len = wcslen(_wcmdln);
   buffer = malloc(sizeof(wchar_t) * len);

   // Reference: https://msdn.microsoft.com/en-us/library/a1y7w461.aspx
   while (TRUE)
   {
      // Arguments are delimited by white space, which is either a space or a tab.
      if (i >= len || ((_wcmdln[i] == ' ' || _wcmdln[i] == '\t') && !inQuotes))
      {
         // Handle the case when empty spaces are in the end of the cmdline
         if (anyLetter)
         {
            wexpand(wcsndup(buffer, bufferIndex), doexpand);
         }
         // Copy the last element from buffer and quit the loop
         if (i >= len)
         {
            break;
         }

         while (_wcmdln[i] == ' ' || _wcmdln[i] == '\t')
            ++i;
         anyLetter = FALSE;
         bufferIndex = 0;
         slashesAdded = 0;
         escapedQuote = FALSE;
         continue;
      }

      anyLetter = TRUE;

      if (_wcmdln[i] == '\\')
      {
         buffer[bufferIndex++] = _wcmdln[i];
         ++slashesAdded;
         ++i;
         escapedQuote = FALSE;
         continue;
      }

      if (_wcmdln[i] == '\"')
      {
         if (slashesAdded > 0)
         {
            if (slashesAdded % 2 == 0)
            {
               // If an even number of backslashes is followed by a double quotation mark, then one backslash (\)
               // is placed in the argv array for every pair of backslashes (\\), and the double quotation mark (")
               // is interpreted as a string delimiter.
               bufferIndex -= slashesAdded / 2;
            }
            else
            {
               // If an odd number of backslashes is followed by a double quotation mark, then one backslash (\)
               // is placed in the argv array for every pair of backslashes (\\) and the double quotation mark is
               // interpreted as an escape sequence by the remaining backslash, causing a literal double quotation mark (")
               // to be placed in argv.
               bufferIndex -= slashesAdded / 2 + 1;
               buffer[bufferIndex++] = '\"';
               slashesAdded = 0;
               escapedQuote = TRUE;
               ++i;
               continue;
            }
            slashesAdded = 0;
         }
         else if (!inQuotes && i > 0 && _wcmdln[i - 1] == '\"' && !escapedQuote)
         {
            buffer[bufferIndex++] = '\"';
            ++i;
            escapedQuote = TRUE;
            continue;
         }
         slashesAdded = 0;
         escapedQuote = FALSE;
         inQuotes = !inQuotes;
         doexpand = inQuotes ? FALSE : expand_wildcards;
         ++i;
         continue;
      }

      buffer[bufferIndex++] = _wcmdln[i];
      slashesAdded = 0;
      escapedQuote = FALSE;
      ++i;
   }

   /* Free the temporary buffer. */
   free(buffer);

   *argc = __argc;
   if (__wargv == NULL)
   {
      __wargv = (wchar_t**)malloc(sizeof(wchar_t*));
      __wargv[0] = 0;
   }
   *wargv = __wargv;
   *wenv = __winitenv;

   _wpgmptr = malloc(MAX_PATH * sizeof(wchar_t));
   if (_wpgmptr)
   {
      if (!GetModuleFileNameW(NULL, _wpgmptr, MAX_PATH))
        _wpgmptr[0] = '\0';
      else
        _wpgmptr[MAX_PATH - 1] = '\0';
   }
   else
   {
      _wpgmptr = _wcsdup(__wargv[0]);
   }

   HeapValidate(GetProcessHeap(), 0, NULL);

   // if (new_mode) _set_new_mode(*new_mode);
}