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
struct iocb {int dummy; } ;

/* Variables and functions */
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  do_sync_io (struct iocb*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ftruncate (int,int) ; 
 int getpagesize () ; 
 int /*<<< orphan*/  io_ctx ; 
 int /*<<< orphan*/  io_prep_pread (struct iocb*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_prep_pwrite (struct iocb*,int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ io_queue_init (int,int /*<<< orphan*/ *) ; 
 scalar_t__ io_queue_release (int /*<<< orphan*/ ) ; 
 char* mmap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	char *buf;
	int page_size = getpagesize();
	int buf_size = strtol(argv[2], NULL, 0);
	int rwfd;
	struct iocb iocb;

	if (io_queue_init(1024, &io_ctx))
		err(1, "io_queue_init failed");

	rwfd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (rwfd < 0)
		err(1, "open failed");

	if (ftruncate(rwfd, buf_size) < 0)
		err(1, "ftruncate failed");

	buf = mmap(0, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, rwfd, 0);
	if (buf == MAP_FAILED)
		err(1, "mmap failed");

	(void) io_prep_pwrite(&iocb, rwfd, buf, buf_size, 0);
	do_sync_io(&iocb);

	(void) io_prep_pread(&iocb, rwfd, buf, buf_size, 0);
	do_sync_io(&iocb);

	if (close(rwfd))
		err(1, "close failed");

	if (io_queue_release(io_ctx) != 0)
		err(1, "io_queue_release failed");

	return (0);
}