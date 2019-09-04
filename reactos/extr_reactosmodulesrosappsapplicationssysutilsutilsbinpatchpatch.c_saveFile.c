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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fwrite (void*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static int
saveFile(const char *fileName, void *file, size_t fileSize)
{
   FILE *f;

   /* Open the file */
   f = fopen(fileName, "wb");
   if (f == NULL)
   {
      printf("Couldn't open file %s for writing!\n", fileName);
      return -1;
   }

   /* Write file */
   if (fwrite(file, fileSize, 1, f) != 1)
   {
      fclose(f);
      printf("Couldn't write file %s!\n", fileName);
      return -1;
   }

   /* Close file */
   fclose(f);
   return 0;
}