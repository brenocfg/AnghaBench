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
typedef  int /*<<< orphan*/  logbuf ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MEMTEST_MAX_REGIONS ; 
 int /*<<< orphan*/  closeDirectLogFiledes (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ memtest_preserving_test (void*,size_t,int) ; 
 int openDirectLogFiledes () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long,unsigned long) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 size_t strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int write (int,char*,int) ; 

int memtest_test_linux_anonymous_maps(void) {
    FILE *fp;
    char line[1024];
    char logbuf[1024];
    size_t start_addr, end_addr, size;
    size_t start_vect[MEMTEST_MAX_REGIONS];
    size_t size_vect[MEMTEST_MAX_REGIONS];
    int regions = 0, j;

    int fd = openDirectLogFiledes();
    if (!fd) return 0;

    fp = fopen("/proc/self/maps","r");
    if (!fp) return 0;
    while(fgets(line,sizeof(line),fp) != NULL) {
        char *start, *end, *p = line;

        start = p;
        p = strchr(p,'-');
        if (!p) continue;
        *p++ = '\0';
        end = p;
        p = strchr(p,' ');
        if (!p) continue;
        *p++ = '\0';
        if (strstr(p,"stack") ||
            strstr(p,"vdso") ||
            strstr(p,"vsyscall")) continue;
        if (!strstr(p,"00:00")) continue;
        if (!strstr(p,"rw")) continue;

        start_addr = strtoul(start,NULL,16);
        end_addr = strtoul(end,NULL,16);
        size = end_addr-start_addr;

        start_vect[regions] = start_addr;
        size_vect[regions] = size;
        snprintf(logbuf,sizeof(logbuf),
            "*** Preparing to test memory region %lx (%lu bytes)\n",
                (unsigned long) start_vect[regions],
                (unsigned long) size_vect[regions]);
        if (write(fd,logbuf,strlen(logbuf)) == -1) { /* Nothing to do. */ }
        regions++;
    }

    int errors = 0;
    for (j = 0; j < regions; j++) {
        if (write(fd,".",1) == -1) { /* Nothing to do. */ }
        errors += memtest_preserving_test((void*)start_vect[j],size_vect[j],1);
        if (write(fd, errors ? "E" : "O",1) == -1) { /* Nothing to do. */ }
    }
    if (write(fd,"\n",1) == -1) { /* Nothing to do. */ }

    /* NOTE: It is very important to close the file descriptor only now
     * because closing it before may result into unmapping of some memory
     * region that we are testing. */
    fclose(fp);
    closeDirectLogFiledes(fd);
    return errors;
}