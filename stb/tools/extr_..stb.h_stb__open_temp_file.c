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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int mkstemp (char*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stb_p_fopen (char*,char const*) ; 
 int /*<<< orphan*/  stb_p_mktemp (char*) ; 
 int /*<<< orphan*/  stb_p_strcpy_s (char*,int,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static FILE *stb__open_temp_file(char *temp_name, char *src_name, const char *mode)
{
   size_t p;
#ifdef _MSC_VER
   int j;
#endif
   FILE *f;
   // try to generate a temporary file in the same directory
   p = strlen(src_name)-1;
   while (p > 0 && src_name[p] != '/' && src_name[p] != '\\'
                && src_name[p] != ':' && src_name[p] != '~')
      --p;
   ++p;

   memcpy(temp_name, src_name, p);

   #ifdef _MSC_VER
   // try multiple times to make a temp file... just in
   // case some other process makes the name first
   for (j=0; j < 32; ++j) {
      stb_p_strcpy_s(temp_name+p, 65536, "stmpXXXXXX");
      if (!stb_p_mktemp(temp_name))
         return 0;

      f = stb_p_fopen(temp_name, mode);
      if (f != NULL)
         break;
   }
   #else
   {
      stb_p_strcpy_s(temp_name+p, 65536, "stmpXXXXXX");
      #ifdef __MINGW32__
         int fd = open(stb_p_mktemp(temp_name), O_RDWR);
      #else
         int fd = mkstemp(temp_name);
      #endif
      if (fd == -1) return NULL;
      f = fdopen(fd, mode);
      if (f == NULL) {
         unlink(temp_name);
         close(fd);
         return NULL;
      }
   }
   #endif
   return f;
}