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
 char* file_buffer ; 
 scalar_t__ is_end_of_name (char) ; 
 scalar_t__ is_eol_char (char) ; 
 scalar_t__ is_whitespace (char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int
get_previous_identifier(unsigned int end, char *name)
{
  unsigned int my_file_pointer = end;
  int len;

  name[0] = 0;

  while ((my_file_pointer > 0) && (is_whitespace(file_buffer[my_file_pointer])
    || is_eol_char(file_buffer[my_file_pointer])))
    {
      my_file_pointer--;
    }

  /* Skip any comments between function name and it's parameters */
  if ((my_file_pointer > 0) && (file_buffer[my_file_pointer] == '/'))
    {
      if ((my_file_pointer > 0) && (file_buffer[my_file_pointer - 1] == '*'))
        {
          my_file_pointer--;
          while ((my_file_pointer > 0) && !((file_buffer[my_file_pointer] == '*')
            && (file_buffer[my_file_pointer - 1] == '/')))
            {
              my_file_pointer--;
            }
          my_file_pointer -= 2;
        }
    }

  /* Skip any remaining whitespace */
  while ((my_file_pointer > 0) && (is_whitespace(file_buffer[my_file_pointer])))
    {
      my_file_pointer--;
    }

  end = my_file_pointer;
  while ((my_file_pointer > 0))
    {
      if (is_end_of_name(file_buffer[my_file_pointer]))
        {
          len = end - my_file_pointer;
          strncpy(name, &file_buffer[my_file_pointer + 1], len);
          name[len] = 0;
          return 1;
        }
      my_file_pointer--;
    }

  return 0;
}