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
struct stat {size_t st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (void*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void *
loadFile(const char *fileName, size_t *fileSize_)
{
   FILE *f;
   struct stat sb;
   size_t fileSize;
   void *p;

   /* Open the file */
   f = fopen(fileName, "rb");
   if (f == NULL)
   {
      printf("Couldn't open file %s for reading!\n", fileName);
      return NULL;
   }

   /* Get file size */
   if (fstat(_fileno(f), &sb) < 0)
   {
      fclose(f);
      printf("Couldn't get size of file %s!\n", fileName);
      return NULL;
   }
   fileSize = sb.st_size;

   /* Load file */
   p = malloc(fileSize);
   if (p == NULL)
   {
      fclose(f);
      printf("Couldn't allocate %Id bytes for file %s!\n", fileSize, fileName);
      return NULL;
   }

   if (fread(p, fileSize, 1, f) != 1)
   {
      fclose(f);
      free(p);
      printf("Couldn't read file %s into memory!\n", fileName);
      return NULL;
   }

   /* Close file */
   fclose(f);

   *fileSize_ = fileSize;
   return p;
}