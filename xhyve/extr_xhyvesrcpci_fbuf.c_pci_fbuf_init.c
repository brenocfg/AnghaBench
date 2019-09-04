#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fbsize; } ;
struct pci_fbuf_softc {int vga_enabled; scalar_t__ vga_full; int /*<<< orphan*/  rfb_password; int /*<<< orphan*/  rfb_wait; int /*<<< orphan*/  rfb_port; int /*<<< orphan*/  rfb_host; scalar_t__ fb_base; int /*<<< orphan*/  gc_image; int /*<<< orphan*/  vgasc; TYPE_2__ memregs; int /*<<< orphan*/  fbaddr; struct pci_devinst* fsc_pi; } ;
struct pci_devinst {TYPE_1__* pi_bar; struct pci_fbuf_softc* pi_arg; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLS_DEFAULT ; 
 int /*<<< orphan*/  DEBUG_INFO ; 
 int /*<<< orphan*/  DMEMSZ ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FB_SIZE ; 
 int /*<<< orphan*/  PCIBAR_MEM32 ; 
 int /*<<< orphan*/  PCIC_DISPLAY ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int /*<<< orphan*/  PCIS_DISPLAY_VGA ; 
 int /*<<< orphan*/  PCI_FBUF_MSI_MSGS ; 
 int /*<<< orphan*/  ROWS_DEFAULT ; 
 int /*<<< orphan*/  assert (int) ; 
 struct pci_fbuf_softc* calloc (int,int) ; 
 int /*<<< orphan*/  console_fb_register (int /*<<< orphan*/ ,struct pci_fbuf_softc*) ; 
 int /*<<< orphan*/  console_get_image () ; 
 int /*<<< orphan*/  console_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct pci_fbuf_softc* fbuf_sc ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct pci_fbuf_softc*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_emul_add_msicap (struct pci_devinst*,int /*<<< orphan*/ ) ; 
 int pci_emul_alloc_bar (struct pci_devinst*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_fbuf_parse_opts (struct pci_fbuf_softc*,char*) ; 
 int /*<<< orphan*/  pci_fbuf_render ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rfb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vga_init (int) ; 
 scalar_t__ xh_setup_video_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int
pci_fbuf_init(struct pci_devinst *pi, char *opts)
{
	int error;
	struct pci_fbuf_softc *sc;

	if (fbuf_sc != NULL) {
		fprintf(stderr, "Only one frame buffer device is allowed.\n");
		return (-1);
	}

	sc = calloc(1, sizeof(struct pci_fbuf_softc));

	pi->pi_arg = sc;

	/* initialize config space */
	pci_set_cfgdata16(pi, PCIR_DEVICE, 0x40FB);
	pci_set_cfgdata16(pi, PCIR_VENDOR, 0xFB5D);
	pci_set_cfgdata8(pi, PCIR_CLASS, PCIC_DISPLAY);
	pci_set_cfgdata8(pi, PCIR_SUBCLASS, PCIS_DISPLAY_VGA);

	error = pci_emul_alloc_bar(pi, 0, PCIBAR_MEM32, DMEMSZ);
	assert(error == 0);

	error = pci_emul_alloc_bar(pi, 1, PCIBAR_MEM32, FB_SIZE);
	assert(error == 0);

	error = pci_emul_add_msicap(pi, PCI_FBUF_MSI_MSGS);
	assert(error == 0);

	sc->fbaddr = pi->pi_bar[1].addr;
	sc->memregs.fbsize = FB_SIZE;
	sc->memregs.width  = COLS_DEFAULT;
	sc->memregs.height = ROWS_DEFAULT;
	sc->memregs.depth  = 32;

	sc->vga_enabled = 1;
	sc->vga_full = 0;

	sc->fsc_pi = pi;

	error = pci_fbuf_parse_opts(sc, opts);
	if (error != 0)
		goto done;

	/* XXX until VGA rendering is enabled */
	if (sc->vga_full != 0) {
		fprintf(stderr, "pci_fbuf: VGA rendering not enabled");
		goto done;
	}

	DPRINTF(DEBUG_INFO, ("fbuf frame buffer base: %p [sz %lu]\r\n",
	        (void *)sc->fb_base, FB_SIZE));

	/*
	 * Map the framebuffer into the guest address space.
	 * XXX This may fail if the BAR is different than a prior
	 * run. In this case flag the error. This will be fixed
	 * when a change_memseg api is available.
	 */
	if (xh_setup_video_memory(sc->fbaddr, FB_SIZE, (void **)&sc->fb_base) != 0) {
		fprintf(stderr, "pci_fbuf: mapseg failed - try deleting VM and restarting\n");
		error = -1;
		goto done;
	}

	console_init(sc->memregs.width, sc->memregs.height, sc->fb_base);
	console_fb_register(pci_fbuf_render, sc);

	if (sc->vga_enabled)
		sc->vgasc = vga_init(!sc->vga_full);
	sc->gc_image = console_get_image();

	fbuf_sc = sc;

	memset((void *)sc->fb_base, 0, FB_SIZE);

	error = rfb_init(sc->rfb_host, sc->rfb_port, sc->rfb_wait, sc->rfb_password);
done:
	if (error)
		free(sc);

	return (error);
}