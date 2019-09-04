#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ _flag; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int MSVCRT_max_streams ; 
 int MSVCRT_stream_idx ; 
 TYPE_1__* msvcrt_get_file (int) ; 

__attribute__((used)) static FILE* msvcrt_alloc_fp(void)
{
  int i;
  FILE *file;

  for (i = 3; i < MSVCRT_max_streams; i++)
  {
    file = msvcrt_get_file(i);
    if (!file)
      return NULL;

    if (file->_flag == 0)
    {
      if (i == MSVCRT_stream_idx) MSVCRT_stream_idx++;
      return file;
    }
  }

  return NULL;
}