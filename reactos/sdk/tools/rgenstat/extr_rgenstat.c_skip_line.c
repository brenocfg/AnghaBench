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
 int /*<<< orphan*/  is_eol_char (char) ; 

__attribute__((used)) static void
skip_line()
{
  while ((file_pointer < file_size) && (!is_eol_char(file_buffer[file_pointer])))
    {
      file_pointer++;
    }
  if ((file_pointer < file_size) && (file_buffer[file_pointer] == '\n'))
    {
      file_pointer++;
    }
}