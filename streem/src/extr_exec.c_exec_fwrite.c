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
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_string ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  STRM_IO_WRITE ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_io_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_cstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
exec_fwrite(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  int fd;
  strm_string path;
  char buf[7];

  strm_get_args(strm, argc, args, "S", &path);
  fd = open(strm_str_cstr(path, buf), O_WRONLY|O_CREAT, 0644);
  if (fd < 0) return STRM_NG;
  *ret = strm_io_new(fd, STRM_IO_WRITE);
  return STRM_OK;
}