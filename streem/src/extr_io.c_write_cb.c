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
struct iovec {int iov_len; void* iov_base; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_string ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_2__ strm_stream ;
struct TYPE_4__ {int mode; } ;

/* Variables and functions */
 int STRM_IO_FLUSH ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int strm_str_len (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_str_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ writev (int /*<<< orphan*/ ,struct iovec*,int) ; 

__attribute__((used)) static int
write_cb(strm_stream* strm, strm_value data)
{
  struct write_data *d = (struct write_data*)strm->data;
  strm_string p = strm_to_str(data);

#ifndef _WIN32
  struct iovec buf[2];

  buf[0].iov_base = (void*)strm_str_ptr(p);
  buf[0].iov_len = strm_str_len(p);
  buf[1].iov_base = (void*)"\n";
  buf[1].iov_len = 1;
  if (writev(fileno(d->f), buf, 2) < 0) {
    return STRM_NG;
  }
#else
  fwrite(strm_str_ptr(p), strm_str_len(p), 1, d->f);
  fputs("\n", d->f);
  if (d->io->mode & STRM_IO_FLUSH) {
    fflush(d->f);
  }
#endif
  return STRM_OK;
}