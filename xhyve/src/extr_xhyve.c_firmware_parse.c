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

/* Variables and functions */
 int /*<<< orphan*/  fbsd_init (char*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ fbsd_load ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fw_func ; 
 scalar_t__ kexec ; 
 int /*<<< orphan*/  kexec_init (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 

__attribute__((used)) static int
firmware_parse(const char *opt) {
	char *fw, *opt1, *opt2, *opt3, *cp;

	fw = strdup(opt);

	if (strncmp(fw, "kexec", strlen("kexec")) == 0) {
		fw_func = kexec;
	} else if (strncmp(fw, "fbsd", strlen("fbsd")) == 0) {
		fw_func = fbsd_load;
	} else {
		goto fail;
	}

		if ((cp = strchr(fw, ',')) != NULL) {
			*cp = '\0';
			opt1 = cp + 1;
		} else {
			goto fail;
		}

		if ((cp = strchr(opt1, ',')) != NULL) {
			*cp = '\0';
			opt2 = cp + 1;
		} else {
			goto fail;
		}

		if ((cp = strchr(opt2, ',')) != NULL) {
			*cp = '\0';
			opt3 = cp + 1;
		} else {
			goto fail;
		}

		opt2 = strlen(opt2) ? opt2 : NULL;
		opt3 = strlen(opt3) ? opt3 : NULL;

	if (fw_func == kexec) {
		kexec_init(opt1, opt2, opt3);
	} else if (fw_func == fbsd_load) {
		/* FIXME: let user set boot-loader serial device */
		fbsd_init(opt1, opt2, opt3, NULL);
	} else {
		goto fail;
	}

	return 0;

fail:
	fprintf(stderr, "Invalid firmware argument\n"
		"    -f kexec,'kernel','initrd','\"cmdline\"'\n"
		"    -f fbsd,'userboot','boot volume','\"kernel env\"'\n");

	return -1;
}