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
struct TYPE_4__ {int _flag; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_FILES () ; 
 int MSVCRT_stream_idx ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  UNLOCK_FILES () ; 
 int /*<<< orphan*/  fflush (TYPE_1__*) ; 
 TYPE_1__* msvcrt_get_file (int) ; 

__attribute__((used)) static int msvcrt_flush_all_buffers(int mask)
{
  int i, num_flushed = 0;
  FILE *file;

  LOCK_FILES();
  for (i = 0; i < MSVCRT_stream_idx; i++) {
    file = msvcrt_get_file(i);

    if (file->_flag)
    {
      if(file->_flag & mask) {
	fflush(file);
        num_flushed++;
      }
    }
  }
  UNLOCK_FILES();

  TRACE(":flushed (%d) handles\n",num_flushed);
  return num_flushed;
}