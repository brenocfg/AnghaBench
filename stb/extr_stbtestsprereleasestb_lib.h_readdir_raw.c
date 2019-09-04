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
typedef  int /*<<< orphan*/  with_slash ;
struct dirent {char* d_name; int d_type; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  const DIR ;

/* Variables and functions */
 int DT_DIR ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  isdotdirname (char*) ; 
 int /*<<< orphan*/  const* opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stb_arr_push (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_fixpath (char*) ; 
 scalar_t__ stb_snprintf (char*,int,char*,char*,char*) ; 
 size_t stb_strscpy (char*,char*,int) ; 
 scalar_t__ stb_wildmatchi (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static char **readdir_raw(char *dir, int return_subdirs, char *mask)
{
   char **results = NULL;
   char buffer[4096], with_slash[4096];
   size_t n;

   #ifdef _MSC_VER
      stb__wchar *ws;
      struct _wfinddata_t data;
   #ifdef _WIN64
      const intptr_t none = -1;
      intptr_t z;
   #else
      const long none = -1;
      long z;
   #endif
   #else // !_MSC_VER
      const DIR *none = NULL;
      DIR *z;
   #endif

   n = stb_strscpy(buffer,dir,sizeof(buffer));
   if (!n || n >= sizeof(buffer))
      return NULL;
   stb_fixpath(buffer);
   n--;

   if (n > 0 && (buffer[n-1] != '/')) {
      buffer[n++] = '/';
   }
   buffer[n] = 0;
   if (!stb_strscpy(with_slash,buffer,sizeof(with_slash)))
      return NULL;

   #ifdef _MSC_VER
      if (!stb_strscpy(buffer+n,"*.*",sizeof(buffer)-n))
         return NULL;
      ws = stb__from_utf8(buffer);
      z = _wfindfirst((const wchar_t *)ws, &data);
   #else
      z = opendir(dir);
   #endif

   if (z != none) {
      int nonempty = 1;
      #ifndef _MSC_VER
      struct dirent *data = readdir(z);
      nonempty = (data != NULL);
      #endif

      if (nonempty) {

         do {
            int is_subdir;
            #ifdef _MSC_VER
            char *name = stb__to_utf8((stb__wchar *)data.name);
            if (name == NULL) {
               fprintf(stderr, "%s to convert '%S' to %s!\n", "Unable", data.name, "utf8");
               continue;
            }
            is_subdir = !!(data.attrib & _A_SUBDIR);
            #else
            char *name = data->d_name;
            if (!stb_strscpy(buffer+n,name,sizeof(buffer)-n))
               break;
            // Could follow DT_LNK, but would need to check for recursive links.
            is_subdir = !!(data->d_type & DT_DIR);
            #endif

            if (is_subdir == return_subdirs) {
               if (!is_subdir || !isdotdirname(name)) {
                  if (!mask || stb_wildmatchi(mask, name)) {
                     char buffer[4096],*p=buffer;
                     if ( stb_snprintf(buffer, sizeof(buffer), "%s%s", with_slash, name) < 0 )
                        break;
                     if (buffer[0] == '.' && buffer[1] == '/')
                        p = buffer+2;
                     stb_arr_push(results, strdup(p));
                  }
               }
            }
         }
         #ifdef _MSC_VER
         while (0 == _wfindnext(z, &data));
         #else
         while ((data = readdir(z)) != NULL);
         #endif
      }
      #ifdef _MSC_VER
         _findclose(z);
      #else
         closedir(z);
      #endif
   }
   return results;
}