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
 size_t file_pointer ; 
 size_t file_size ; 
 int get_previous_identifier (size_t,char*) ; 

__attribute__((used)) static int
skip_to_next_name(char *name)
{
  while ((file_pointer < file_size))
    {
      if (file_buffer[file_pointer] == '(')
        {
          return get_previous_identifier(file_pointer - 1, name);
        }
      file_pointer++;
    }
  return 0;
}