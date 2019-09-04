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
 int /*<<< orphan*/  HELP ; 
 char* convert_path (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * out ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_input_file (char*) ; 

int main(int argc, char **argv)
{
  char *input_file;
  char *output_file;

  if (argc != 3)
  {
    puts(HELP);
    return 1;
  }

  input_file = convert_path(argv[1]);
  if (input_file[0] == 0)
    {
      free(input_file);
      printf("Missing input-filename\n");
      return 1;
    }

  output_file = convert_path(argv[2]);
  if (output_file[0] == 0)
    {
      free(input_file);
      free(output_file);
      printf("Missing output-filename\n");
      return 1;
    }

  out = fopen(output_file, "wb");
  if (out == NULL)
    {
      free(input_file);
      free(output_file);
    	printf("Cannot open output file");
    	return 1;
     }

  read_input_file(input_file);

  free(input_file);
  free(output_file);
  fclose(out);

  return 0;
}