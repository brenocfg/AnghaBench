#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  INSTALLSTATE_ABSENT ; 
 int /*<<< orphan*/  INSTALLSTATE_ADVERTISED ; 
 int /*<<< orphan*/  INSTALLSTATE_LOCAL ; 
 int /*<<< orphan*/  INSTALLSTATE_SOURCE ; 
 int /*<<< orphan*/  INSTALLSTATE_UNKNOWN ; 
 int /*<<< orphan*/  msi_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int process_state_property (TYPE_1__*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szOne ; 
 int /*<<< orphan*/  szPreselected ; 
 char const* szReinstall ; 
 char const* szRemove ; 

__attribute__((used)) static BOOL process_overrides( MSIPACKAGE *package, int level )
{
    static const WCHAR szAddLocal[] =
        {'A','D','D','L','O','C','A','L',0};
    static const WCHAR szAddSource[] =
        {'A','D','D','S','O','U','R','C','E',0};
    static const WCHAR szAdvertise[] =
        {'A','D','V','E','R','T','I','S','E',0};
    BOOL ret = FALSE;

    /* all these activation/deactivation things happen in order and things
     * later on the list override things earlier on the list.
     *
     *  0  INSTALLLEVEL processing
     *  1  ADDLOCAL
     *  2  REMOVE
     *  3  ADDSOURCE
     *  4  ADDDEFAULT
     *  5  REINSTALL
     *  6  ADVERTISE
     *  7  COMPADDLOCAL
     *  8  COMPADDSOURCE
     *  9  FILEADDLOCAL
     * 10  FILEADDSOURCE
     * 11  FILEADDDEFAULT
     */
    ret |= process_state_property( package, level, szAddLocal, INSTALLSTATE_LOCAL );
    ret |= process_state_property( package, level, szRemove, INSTALLSTATE_ABSENT );
    ret |= process_state_property( package, level, szAddSource, INSTALLSTATE_SOURCE );
    ret |= process_state_property( package, level, szReinstall, INSTALLSTATE_UNKNOWN );
    ret |= process_state_property( package, level, szAdvertise, INSTALLSTATE_ADVERTISED );

    if (ret)
        msi_set_property( package->db, szPreselected, szOne, -1 );

    return ret;
}