#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct write_data {int /*<<< orphan*/  f; TYPE_1__* io; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_2__ strm_stream ;
struct TYPE_4__ {int mode; } ;

/* Variables and functions */
 int STRM_IO_READING ; 
 int STRM_OK ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct write_data*) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
write_close(strm_stream* strm, strm_value data)
{
  struct write_data *d = (struct write_data*)strm->data;

  /* tell peer we close the socket for writing (if it is) */
  shutdown(fileno(d->f), 1);
  /* if we have a reading strm, let it close the fd */
  if ((d->io->mode & STRM_IO_READING) == 0) {
    fclose(d->f);
  }
  free(d);
  return STRM_OK;
}