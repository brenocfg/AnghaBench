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
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * file_buffer ; 
 int /*<<< orphan*/ * file_handle ; 
 scalar_t__ file_pointer ; 
 scalar_t__ file_size ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
read_file(char *filename)
{
  file_handle = fopen(filename, "rb");
  if (file_handle == NULL)
    {
      printf("Can't open %s\n", filename);
      exit(1);
    }

  // Get the size of the file
  fseek(file_handle, 0, SEEK_END);
  file_size = ftell(file_handle);

  // Load it all into memory
  file_buffer = malloc(file_size);
  if (file_buffer == NULL)
    {
      fclose(file_handle);
      printf("Out of memory\n");
      exit(1);
    }
  fseek(file_handle, 0, SEEK_SET);
  if (file_size > 0)
    {
      if (fread (file_buffer, 1, file_size, file_handle) < 1)
        {
          fclose(file_handle);
          printf("Read error in file %s\n", filename);
          exit(1);
        }
    }

  file_pointer = 0;
}