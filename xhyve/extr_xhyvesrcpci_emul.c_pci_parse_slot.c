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
struct slotinfo {TYPE_1__* si_funcs; } ;
struct businfo {struct slotinfo* slotinfo; } ;
struct TYPE_2__ {char* fi_name; char* fi_param; } ;

/* Variables and functions */
 int MAXBUSES ; 
 int MAXFUNCS ; 
 int MAXSLOTS ; 
 struct businfo* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct businfo** pci_businfo ; 
 int /*<<< orphan*/ * pci_emul_finddev (char*) ; 
 int /*<<< orphan*/  pci_parse_slot_usage (char*) ; 
 int sscanf (char*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 

int
pci_parse_slot(char *opt)
{
	struct businfo *bi;
	struct slotinfo *si;
	char *emul, *config, *str, *cp;
	int error, bnum, snum, fnum;

	error = -1;
	str = strdup(opt);

	emul = config = NULL;
	if ((cp = strchr(str, ',')) != NULL) {
		*cp = '\0';
		emul = cp + 1;
		if ((cp = strchr(emul, ',')) != NULL) {
			*cp = '\0';
			config = cp + 1;
		}
	} else {
		pci_parse_slot_usage(opt);
		goto done;
	}

	/* <bus>:<slot>:<func> */
	if (sscanf(str, "%d:%d:%d", &bnum, &snum, &fnum) != 3) {
		bnum = 0;
		/* <slot>:<func> */
		if (sscanf(str, "%d:%d", &snum, &fnum) != 2) {
			fnum = 0;
			/* <slot> */
			if (sscanf(str, "%d", &snum) != 1) {
				snum = -1;
			}
		}
	}

	if (bnum < 0 || bnum >= MAXBUSES || snum < 0 || snum >= MAXSLOTS ||
	    fnum < 0 || fnum >= MAXFUNCS) {
		pci_parse_slot_usage(opt);
		goto done;
	}

	if (pci_businfo[bnum] == NULL)
		pci_businfo[bnum] = calloc(1, sizeof(struct businfo));

	bi = pci_businfo[bnum];
	si = &bi->slotinfo[snum];

	if (si->si_funcs[fnum].fi_name != NULL) {
		fprintf(stderr, "pci slot %d:%d already occupied!\n",
			snum, fnum);
		goto done;
	}

	if (pci_emul_finddev(emul) == NULL) {
		fprintf(stderr, "pci slot %d:%d: unknown device \"%s\"\n",
			snum, fnum, emul);
		goto done;
	}

	error = 0;
	si->si_funcs[fnum].fi_name = emul;
	si->si_funcs[fnum].fi_param = config;

done:
	if (error)
		free(str);

	return (error);
}