#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ errors; void* name; void* temp_name; } ;
typedef  TYPE_1__ stb__file_data ;
typedef  int /*<<< orphan*/  name_full ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * stb__files ; 
 int /*<<< orphan*/ * stb__fopen (char*,char const*) ; 
 int /*<<< orphan*/ * stb__open_temp_file (char*,char*,char const*) ; 
 scalar_t__ stb_fullpath (char*,int,char*) ; 
 void* stb_p_strdup (char*) ; 
 int /*<<< orphan*/  stb_ptrmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * stb_ptrmap_create () ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 

FILE *  stb_fopen(char *filename, const char *mode)
{
   FILE *f;
   char name_full[4096];
   char temp_full[sizeof(name_full) + 12];

   // @TODO: if the file doesn't exist, we can also use the fastpath here
   if (mode[0] != 'w' && !strchr(mode, '+'))
      return stb__fopen(filename, mode);

   // save away the full path to the file so if the program
   // changes the cwd everything still works right! unix has
   // better ways to do this, but we have to work in windows
   name_full[0] = '\0'; // stb_fullpath reads name_full[0]
   if (stb_fullpath(name_full, sizeof(name_full), filename)==0)
      return 0;

   f = stb__open_temp_file(temp_full, name_full, mode);
   if (f != NULL) {
      stb__file_data *d = (stb__file_data *) malloc(sizeof(*d));
      if (!d) { assert(0);  /* NOTREACHED */fclose(f); return NULL; }
      if (stb__files == NULL) stb__files = stb_ptrmap_create();
      d->temp_name = stb_p_strdup(temp_full);
      d->name      = stb_p_strdup(name_full);
      d->errors    = 0;
      stb_ptrmap_add(stb__files, f, d);
      return f;
   }

   return NULL;
}