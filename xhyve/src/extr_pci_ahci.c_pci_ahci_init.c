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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_char ;
struct pci_devinst {int pi_slot; int pi_func; struct pci_ahci_softc* pi_arg; } ;
struct pci_ahci_softc {int ports; int cap; int pi; int vs; TYPE_1__* port; int /*<<< orphan*/  cap2; int /*<<< orphan*/  mtx; struct pci_devinst* asc_pi; } ;
struct blockif_ctxt {int dummy; } ;
typedef  int /*<<< orphan*/  bident ;
struct TYPE_2__ {int atapi; int ioqsz; struct blockif_ctxt* bctx; int /*<<< orphan*/  ident; struct pci_ahci_softc* pr_sc; } ;
typedef  int /*<<< orphan*/  CC_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_CAP2_APST ; 
 int AHCI_CAP_64BIT ; 
 int AHCI_CAP_ISS_SHIFT ; 
 unsigned int AHCI_CAP_NCS_SHIFT ; 
 int AHCI_CAP_PMD ; 
 int AHCI_CAP_PSC ; 
 int AHCI_CAP_SAL ; 
 int AHCI_CAP_SALP ; 
 int AHCI_CAP_SCLO ; 
 int AHCI_CAP_SMPS ; 
 int AHCI_CAP_SNCQ ; 
 int AHCI_CAP_SSC ; 
 int AHCI_CAP_SSNTF ; 
 int AHCI_CAP_SSS ; 
 int AHCI_CAP_SXS ; 
 scalar_t__ AHCI_OFFSET ; 
 int /*<<< orphan*/  AHCI_PORT_IDENT ; 
 int AHCI_STEP ; 
 int /*<<< orphan*/  CC_SHA256 (char*,int /*<<< orphan*/ ,int*) ; 
 int CC_SHA256_DIGEST_LENGTH ; 
 int MAX_PORTS ; 
 int /*<<< orphan*/  PCIBAR_MEM32 ; 
 int /*<<< orphan*/  PCIC_STORAGE ; 
 int /*<<< orphan*/  PCIP_STORAGE_SATA_AHCI_1_0 ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_PROGIF ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int /*<<< orphan*/  PCIS_STORAGE_SATA ; 
 int /*<<< orphan*/  ahci_reset (struct pci_ahci_softc*) ; 
 int /*<<< orphan*/  blockif_close (struct blockif_ctxt*) ; 
 struct blockif_ctxt* blockif_open (char*,char*) ; 
 struct pci_ahci_softc* calloc (int,int) ; 
 int /*<<< orphan*/  dbg ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct pci_ahci_softc*) ; 
 int /*<<< orphan*/  pci_ahci_ioreq_init (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_emul_add_msicap (struct pci_devinst*,int) ; 
 int /*<<< orphan*/  pci_emul_alloc_bar (struct pci_devinst*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lintr_request (struct pci_devinst*) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
pci_ahci_init(struct pci_devinst *pi, char *opts, int atapi)
{
	char bident[sizeof("XX:X:X")];
	struct blockif_ctxt *bctxt;
	struct pci_ahci_softc *sc;
	int ret, slots;
	u_char digest[CC_SHA256_DIGEST_LENGTH];

	ret = 0;

	if (opts == NULL) {
		fprintf(stderr, "pci_ahci: backing device required\n");
		return (1);
	}

#ifdef AHCI_DEBUG
	dbg = fopen("/tmp/log", "w+");
#endif

	sc = calloc(1, sizeof(struct pci_ahci_softc));
	pi->pi_arg = sc;
	sc->asc_pi = pi;
	sc->ports = MAX_PORTS;

	/*
	 * Only use port 0 for a backing device. All other ports will be
	 * marked as unused
	 */
	sc->port[0].atapi = atapi;

	/*
	 * Attempt to open the backing image. Use the PCI
	 * slot/func for the identifier string.
	 */
	snprintf(bident, sizeof(bident), "%d:%d", pi->pi_slot, pi->pi_func);
	bctxt = blockif_open(opts, bident);
	if (bctxt == NULL) {       	
		ret = 1;
		goto open_fail;
	}	
	sc->port[0].bctx = bctxt;
	sc->port[0].pr_sc = sc;

	/*
	 * Create an identifier for the backing file. Use parts of the
	 * md5 sum of the filename
	 */
    CC_SHA256(opts, (CC_LONG)strlen(opts), digest);
    snprintf(sc->port[0].ident, AHCI_PORT_IDENT, "BHYVE-%02X%02X-%02X%02X-%02X%02X",
	    digest[0], digest[1], digest[2], digest[3], digest[4], digest[5]);

	/*
	 * Allocate blockif request structures and add them
	 * to the free list
	 */
	pci_ahci_ioreq_init(&sc->port[0]);

	pthread_mutex_init(&sc->mtx, NULL);

	/* Intel ICH8 AHCI */
	slots = sc->port[0].ioqsz;
	if (slots > 32)
		slots = 32;
	--slots;
	sc->cap = AHCI_CAP_64BIT | AHCI_CAP_SNCQ | AHCI_CAP_SSNTF |
	    AHCI_CAP_SMPS | AHCI_CAP_SSS | AHCI_CAP_SALP |
	    AHCI_CAP_SAL | AHCI_CAP_SCLO | (0x3 << AHCI_CAP_ISS_SHIFT)|
	    AHCI_CAP_PMD | AHCI_CAP_SSC | AHCI_CAP_PSC |
	    (((unsigned) slots) << AHCI_CAP_NCS_SHIFT) | AHCI_CAP_SXS |
	    (((unsigned) sc->ports) - 1);

	/* Only port 0 implemented */
	sc->pi = 1;
	sc->vs = 0x10300;
	sc->cap2 = AHCI_CAP2_APST;
	ahci_reset(sc);

	pci_set_cfgdata16(pi, PCIR_DEVICE, 0x2821);
	pci_set_cfgdata16(pi, PCIR_VENDOR, 0x8086);
	pci_set_cfgdata8(pi, PCIR_CLASS, PCIC_STORAGE);
	pci_set_cfgdata8(pi, PCIR_SUBCLASS, PCIS_STORAGE_SATA);
	pci_set_cfgdata8(pi, PCIR_PROGIF, PCIP_STORAGE_SATA_AHCI_1_0);
	pci_emul_add_msicap(pi, 1);
	pci_emul_alloc_bar(pi, 5, PCIBAR_MEM32,
		((uint64_t) (AHCI_OFFSET + sc->ports * AHCI_STEP)));

	pci_lintr_request(pi);

open_fail:
	if (ret) {
		if (sc->port[0].bctx != NULL)
			blockif_close(sc->port[0].bctx);
		free(sc);
	}

	return (ret);
}