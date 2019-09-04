#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct BackupSysParam {scalar_t__ spiGet; scalar_t__ spiSet; } ;
typedef  int /*<<< orphan*/  ncm ;
typedef  int /*<<< orphan*/  iconTitleFont ;
struct TYPE_8__ {int cbSize; } ;
typedef  TYPE_1__ NONCLIENTMETRICSW ;
typedef  TYPE_1__ LOGFONTW ;
typedef  TYPE_1__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int SPIF_SENDCHANGE ; 
 int SPIF_UPDATEINIFILE ; 
 scalar_t__ SPI_GETICONTITLELOGFONT ; 
 scalar_t__ SPI_GETNONCLIENTMETRICS ; 
 scalar_t__ SPI_SETICONTITLELOGFONT ; 
 scalar_t__ SPI_SETNONCLIENTMETRICS ; 
 int /*<<< orphan*/  SystemParametersInfoW (scalar_t__,int,TYPE_1__*,int) ; 
 TYPE_1__* UlongToPtr (TYPE_1__) ; 
 struct BackupSysParam* backupSysParams ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_sys_colors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UXTHEME_SaveSystemMetrics(void)
{
    const struct BackupSysParam* bsp = backupSysParams;
    NONCLIENTMETRICSW ncm;
    LOGFONTW iconTitleFont;

    save_sys_colors (HKEY_CURRENT_USER);

    while (bsp->spiGet >= 0)
    {
        DWORD value;
        
        SystemParametersInfoW (bsp->spiGet, 0, &value, 0);
        SystemParametersInfoW (bsp->spiSet, 0, UlongToPtr(value), SPIF_UPDATEINIFILE);
        bsp++;
    }
    
    memset (&ncm, 0, sizeof (ncm));
    ncm.cbSize = sizeof (ncm);
    SystemParametersInfoW (SPI_GETNONCLIENTMETRICS, sizeof (ncm), &ncm, 0);
    SystemParametersInfoW (SPI_SETNONCLIENTMETRICS, sizeof (ncm), &ncm,
        SPIF_UPDATEINIFILE);

    memset (&iconTitleFont, 0, sizeof (iconTitleFont));
    SystemParametersInfoW (SPI_GETICONTITLELOGFONT, sizeof (iconTitleFont),
        &iconTitleFont, 0);
    SystemParametersInfoW (SPI_SETICONTITLELOGFONT, sizeof (iconTitleFont),
        &iconTitleFont, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}