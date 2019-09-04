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
typedef  int /*<<< orphan*/  value ;
struct BackupSysParam {scalar_t__ spiGet; int /*<<< orphan*/  spiSet; int /*<<< orphan*/  keyName; } ;
typedef  int /*<<< orphan*/  ncm ;
typedef  int /*<<< orphan*/  iconTitleFont ;
typedef  int /*<<< orphan*/  colorStr ;
typedef  int /*<<< orphan*/  NONCLIENTMETRICSW ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int NUM_SYS_COLORS ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_SETICONTITLELOGFONT ; 
 int /*<<< orphan*/  SPI_SETNONCLIENTMETRICS ; 
 int /*<<< orphan*/  SetSysColors (int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SysColorsNames ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * UlongToPtr (int) ; 
 struct BackupSysParam* backupSysParams ; 
 int /*<<< orphan*/  keyIconTitleFont ; 
 int /*<<< orphan*/  keyNonClientMetrics ; 
 int sscanf (char*,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  strColorKey ; 
 int /*<<< orphan*/  szThemeManager ; 

__attribute__((used)) static void UXTHEME_RestoreSystemMetrics(void)
{
    HKEY hKey;
    const struct BackupSysParam* bsp = backupSysParams;

    if (RegOpenKeyExW (HKEY_CURRENT_USER, szThemeManager,
                       0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) 
    {
        HKEY colorKey;
    
        /* read backed-up colors */
        if (RegOpenKeyExW (hKey, strColorKey,
                           0, KEY_QUERY_VALUE, &colorKey) == ERROR_SUCCESS) 
        {
            int i;
            COLORREF sysCols[NUM_SYS_COLORS];
            int sysColsIndices[NUM_SYS_COLORS];
            int sysColCount = 0;
        
            for (i = 0; i < NUM_SYS_COLORS; i++)
            {
                DWORD type;
                char colorStr[13];
                DWORD count = sizeof(colorStr);
            
                if (RegQueryValueExA (colorKey, SysColorsNames[i], 0,
                    &type, (LPBYTE) colorStr, &count) == ERROR_SUCCESS)
                {
                    int r, g, b;
                    if (sscanf (colorStr, "%d %d %d", &r, &g, &b) == 3)
                    {
                        sysColsIndices[sysColCount] = i;
                        sysCols[sysColCount] = RGB(r, g, b);
                        sysColCount++;
                    }
                }
            }
            RegCloseKey (colorKey);
          
            SetSysColors (sysColCount, sysColsIndices, sysCols);
        }
    
        /* read backed-up other settings */
        while (bsp->spiGet >= 0)
        {
            DWORD value;
            DWORD count = sizeof(value);
            DWORD type;
            
            if (RegQueryValueExW (hKey, bsp->keyName, 0,
                &type, (LPBYTE)&value, &count) == ERROR_SUCCESS)
            {
                SystemParametersInfoW (bsp->spiSet, 0, UlongToPtr(value), SPIF_UPDATEINIFILE);
            }
        
            bsp++;
        }
    
        /* read backed-up non-client metrics */
        {
            NONCLIENTMETRICSW ncm;
            LOGFONTW iconTitleFont;
            DWORD count = sizeof(ncm);
            DWORD type;
            
	    if (RegQueryValueExW (hKey, keyNonClientMetrics, 0,
		&type, (LPBYTE)&ncm, &count) == ERROR_SUCCESS)
	    {
		SystemParametersInfoW (SPI_SETNONCLIENTMETRICS, 
                    count, &ncm, SPIF_UPDATEINIFILE);
	    }
	    
            count = sizeof(iconTitleFont);
            
	    if (RegQueryValueExW (hKey, keyIconTitleFont, 0,
		&type, (LPBYTE)&iconTitleFont, &count) == ERROR_SUCCESS)
	    {
		SystemParametersInfoW (SPI_SETICONTITLELOGFONT, 
                    count, &iconTitleFont, SPIF_UPDATEINIFILE);
	    }
	}
      
        RegCloseKey (hKey);
    }
}