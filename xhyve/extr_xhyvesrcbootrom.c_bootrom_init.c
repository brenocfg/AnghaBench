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
struct stat {int st_size; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int MAX_BOOTROM_SIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int XHYVE_PAGE_MASK ; 
 int XHYVE_PAGE_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ xh_setup_bootrom_memory (size_t,void**) ; 

int
bootrom_init(const char *romfile)
{
	struct stat sbuf;
	ssize_t rlen;
	char *ptr;
	int fd, i, rv;

	rv = -1;
	fd = open(romfile, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "Error opening bootrom \"%s\": %s\n",
		    romfile, strerror(errno));
		goto done;
	}

        if (fstat(fd, &sbuf) < 0) {
		fprintf(stderr, "Could not fstat bootrom file \"%s\": %s\n",
		    romfile, strerror(errno));
		goto done;
        }

	/*
	 * Limit bootrom size to 16MB so it doesn't encroach into reserved
	 * MMIO space (e.g. APIC, HPET, MSI).
	 */
	if (sbuf.st_size > MAX_BOOTROM_SIZE || sbuf.st_size < XHYVE_PAGE_SIZE) {
		fprintf(stderr, "Invalid bootrom size %lld\n", sbuf.st_size);
		goto done;
	}

	if (sbuf.st_size & XHYVE_PAGE_MASK) {
		fprintf(stderr, "Bootrom size %lld is not a multiple of the "
		    "page size\n", sbuf.st_size);
		goto done;
	}

	/* Map the bootrom into the guest address space */
	if (xh_setup_bootrom_memory((size_t)sbuf.st_size, (void **)&ptr) != 0)
    {
        fprintf(stderr, "hv_setup_bootrom_memory failed\n");
		goto done;
    }

	/* Read 'romfile' into the guest address space */
	for (i = 0; i < sbuf.st_size / XHYVE_PAGE_SIZE; i++) {
		rlen = read(fd, ptr + i * XHYVE_PAGE_SIZE, XHYVE_PAGE_SIZE);
		if (rlen != XHYVE_PAGE_SIZE) {
			fprintf(stderr, "Incomplete read of page %d of bootrom "
			    "file %s: %ld bytes\n", i, romfile, rlen);
			goto done;
		}
	}
	rv = 0;
done:
	if (fd >= 0)
		close(fd);
	return (rv);
}