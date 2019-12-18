#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  long ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ _UserData ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_debug (char*) ; 
 int /*<<< orphan*/  cdio_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 long fread (void*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
_stdio_read(void *user_data, void *buf, size_t count)
{
  _UserData *const ud = user_data;
  long read_count;

  read_count = fread(buf, 1, count, ud->fd);

  if (read_count != count)
    { /* fixme -- ferror/feof */
      if (feof (ud->fd))
        {
          cdio_debug ("fread (): EOF encountered");
          clearerr (ud->fd);
        }
      else if (ferror (ud->fd))
        {
          cdio_error ("fread (): %s", strerror (errno));
          clearerr (ud->fd);
        }
      else
        cdio_debug ("fread (): short read and no EOF?!?");
    }

  return read_count;
}