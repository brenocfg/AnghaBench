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

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapValidate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int TRUE ; 
 int __argc ; 
 char** __argv ; 
 char* _acmdln ; 
 char** _environ ; 
 char* _pgmptr ; 
 char* _strdup (char*) ; 
 int /*<<< orphan*/  aexpand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strndup (char*,int) ; 

void __getmainargs(int* argc, char*** argv, char*** env, int expand_wildcards, int* new_mode)
{
   int i, doexpand, slashesAdded, escapedQuote, inQuotes, bufferIndex, anyLetter;
   size_t len;
   char* buffer;

   /* missing threading init */

   i = 0;
   doexpand = expand_wildcards;
   escapedQuote = FALSE;
   anyLetter = FALSE;
   slashesAdded = 0;
   inQuotes = 0;
   bufferIndex = 0;

   if (__argv && _environ)
   {
      *argv = __argv;
      *env = _environ;
      *argc = __argc;
      return;
   }

   __argc = 0;

   len = strlen(_acmdln);
   buffer = malloc(sizeof(char) * len);

   // Reference: https://msdn.microsoft.com/en-us/library/a1y7w461.aspx
   while (TRUE)
   {
      // Arguments are delimited by white space, which is either a space or a tab.
      if (i >= len || ((_acmdln[i] == ' ' || _acmdln[i] == '\t') && !inQuotes))
      {
         // Handle the case when empty spaces are in the end of the cmdline
         if (anyLetter) 
         {
            aexpand(strndup(buffer, bufferIndex), doexpand);
         }
         // Copy the last element from buffer and quit the loop
         if (i >= len)
         {
            break;
         }

         while (_acmdln[i] == ' ' || _acmdln[i] == '\t')
            ++i;
         anyLetter = FALSE;
         bufferIndex = 0;
         slashesAdded = 0;
         escapedQuote = FALSE;
         continue;
      }

      anyLetter = TRUE;

      if (_acmdln[i] == '\\')
      {
         buffer[bufferIndex++] = _acmdln[i];
         ++slashesAdded;
         ++i;
         escapedQuote = FALSE;
         continue;
      }

      if (_acmdln[i] == '\"')
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
         else if (!inQuotes && i > 0 && _acmdln[i - 1] == '\"' && !escapedQuote)
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

      buffer[bufferIndex++] = _acmdln[i];
      slashesAdded = 0;
      escapedQuote = FALSE;
      ++i;
   }

   /* Free the temporary buffer. */
   free(buffer);

   *argc = __argc;
   if (__argv == NULL)
   {
      __argv = (char**)malloc(sizeof(char*));
      __argv[0] = 0;
   }
   *argv = __argv;
   *env  = _environ;

   _pgmptr = malloc(MAX_PATH * sizeof(char));
   if (_pgmptr)
   {
      if (!GetModuleFileNameA(NULL, _pgmptr, MAX_PATH))
        _pgmptr[0] = '\0';
      else
        _pgmptr[MAX_PATH - 1] = '\0';
   }
   else
   {
      _pgmptr = _strdup(__argv[0]);
   }

   HeapValidate(GetProcessHeap(), 0, NULL);

   // if (new_mode) _set_new_mode(*new_mode);
}