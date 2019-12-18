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
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  scalar_t__ offset_t ;
typedef  int mode_t ;

/* Variables and functions */
 int EFBIG ; 
 int EINVAL ; 
 scalar_t__ MAXOFFSET_T ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ lseek64 (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigxfsz ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int write (int,char*,int) ; 

int
main(int argc, char **argv)
{
	int		fd = 0;
	offset_t	offset = (MAXOFFSET_T - 1);
	offset_t	llseek_ret = 0;
	int		write_ret = 0;
	int		err = 0;
	char		mybuf[5] = "aaaa\0";
	char		*testfile;
	mode_t		mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	struct sigaction sa;

	if (argc != 2) {
		usage(argv[0]);
	}

	if (sigemptyset(&sa.sa_mask) == -1)
		return (errno);
	sa.sa_flags = 0;
	sa.sa_handler = sigxfsz;
	if (sigaction(SIGXFSZ, &sa, NULL) == -1)
		return (errno);

	testfile = strdup(argv[1]);

	fd = open(testfile, O_CREAT | O_RDWR, mode);
	if (fd < 0) {
		err = errno;
		perror("Failed to create testfile");
		free(testfile);
		return (err);
	}

	llseek_ret = lseek64(fd, offset, SEEK_SET);
	if (llseek_ret < 0) {
		err = errno;
		perror("Failed to seek to end of testfile");
		goto out;
	}

	write_ret = write(fd, mybuf, 1);
	if (write_ret < 0) {
		err = errno;
		perror("Failed to write to end of file");
		goto out;
	}

	offset = 0;
	llseek_ret = lseek64(fd, offset, SEEK_CUR);
	if (llseek_ret < 0) {
		err = errno;
		perror("Failed to seek to end of file");
		goto out;
	}

	write_ret = write(fd, mybuf, 1);
	if (write_ret < 0) {
		if (errno == EFBIG || errno == EINVAL) {
			(void) printf("write errno=EFBIG|EINVAL: success\n");
			err = 0;
		} else {
			err = errno;
			perror("Did not receive EFBIG");
		}
	} else {
		(void) printf("write completed successfully, test failed\n");
		err = 1;
	}

out:
	(void) unlink(testfile);
	free(testfile);
	close(fd);
	return (err);
}