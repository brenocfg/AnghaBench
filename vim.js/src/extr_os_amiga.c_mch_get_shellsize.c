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
struct Window {scalar_t__ Title; } ;
struct InfoData {scalar_t__ id_InUse; scalar_t__ id_VolumeNode; } ;
struct IOStdReq {scalar_t__ io_Unit; } ;
struct ConUnit {int cu_YMax; int cu_XMax; } ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int ULONG ;
typedef  scalar_t__ BPTR ;

/* Variables and functions */
 scalar_t__ ACTION_DISK_INFO ; 
 struct InfoData* AllocDosObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Columns ; 
 int /*<<< orphan*/  DOS_INFODATA ; 
 int FAIL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FreeDosObject (int /*<<< orphan*/ ,struct InfoData*) ; 
 int /*<<< orphan*/  Info (int /*<<< orphan*/ ,struct InfoData*) ; 
 int /*<<< orphan*/  MP (int /*<<< orphan*/ ) ; 
 int OK ; 
 int /*<<< orphan*/  OUT_STR (char*) ; 
 int Rows ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ dos_packet (int /*<<< orphan*/ ,long,int) ; 
 int /*<<< orphan*/  mch_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * oldwindowtitle ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  raw_out ; 
 scalar_t__ size_set ; 
 scalar_t__ term_console ; 
 struct Window* wb_window ; 

int
mch_get_shellsize()
{
    struct ConUnit  *conUnit;
#ifndef __amigaos4__
    char	    id_a[sizeof(struct InfoData) + 3];
#endif
    struct InfoData *id=0;

    if (!term_console)	/* not an amiga window */
	goto out;

    /* insure longword alignment */
#ifdef __amigaos4__
    if (!(id = AllocDosObject(DOS_INFODATA, 0)))
	goto out;
#else
    id = (struct InfoData *)(((long)id_a + 3L) & ~3L);
#endif

    /*
     * Should make console aware of real window size, not the one we set.
     * Unfortunately, under DOS 2.0x this redraws the window and it
     * is rarely needed, so we skip it now, unless we changed the size.
     */
    if (size_set)
	OUT_STR("\233t\233u");	/* CSI t CSI u */
    out_flush();

#ifdef __AROS__
    if (!Info(raw_out, id)
		 || (wb_window = (struct Window *) id->id_VolumeNode) == NULL)
#else
    if (dos_packet(MP(raw_out), (long)ACTION_DISK_INFO, ((ULONG) id) >> 2) == 0
	    || (wb_window = (struct Window *)id->id_VolumeNode) == NULL)
#endif
    {
	/* it's not an amiga window, maybe aux device */
	/* terminal type should be set */
	term_console = FALSE;
	goto out;
    }
    if (oldwindowtitle == NULL)
	oldwindowtitle = (char_u *)wb_window->Title;
    if (id->id_InUse == (BPTR)NULL)
    {
	mch_errmsg(_("mch_get_shellsize: not a console??\n"));
	return FAIL;
    }
    conUnit = (struct ConUnit *) ((struct IOStdReq *) id->id_InUse)->io_Unit;

    /* get window size */
    Rows = conUnit->cu_YMax + 1;
    Columns = conUnit->cu_XMax + 1;
    if (Rows < 0 || Rows > 200)	    /* cannot be an amiga window */
    {
	Columns = 80;
	Rows = 24;
	term_console = FALSE;
	return FAIL;
    }

    return OK;
out:
#ifdef __amigaos4__
    FreeDosObject(DOS_INFODATA, id); /* Safe to pass NULL */
#endif

    return FAIL;
}