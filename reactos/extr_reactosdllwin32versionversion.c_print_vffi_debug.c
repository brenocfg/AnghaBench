#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_3__ {int dwFileType; scalar_t__ dwFileSubtype; int dwFileVersionMS; int dwProductVersionMS; int dwStrucVersion; int dwFileVersionLS; int dwProductVersionLS; int dwFileFlags; int dwFileOS; int dwFileDateMS; int dwFileDateLS; int /*<<< orphan*/  dwFileFlagsMask; } ;
typedef  TYPE_1__ VS_FIXEDFILEINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HIBYTE (int) ; 
 int HIWORD (int) ; 
 int /*<<< orphan*/  LOBYTE (int) ; 
 int LOWORD (int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
#define  VFT2_DRV_COMM 160 
#define  VFT2_DRV_DISPLAY 159 
#define  VFT2_DRV_INPUTMETHOD 158 
#define  VFT2_DRV_INSTALLABLE 157 
#define  VFT2_DRV_KEYBOARD 156 
#define  VFT2_DRV_LANGUAGE 155 
#define  VFT2_DRV_MOUSE 154 
#define  VFT2_DRV_NETWORK 153 
#define  VFT2_DRV_PRINTER 152 
#define  VFT2_DRV_SOUND 151 
#define  VFT2_DRV_SYSTEM 150 
#define  VFT2_DRV_VERSIONED_PRINTER 149 
#define  VFT2_FONT_RASTER 148 
#define  VFT2_FONT_TRUETYPE 147 
#define  VFT2_FONT_VECTOR 146 
#define  VFT2_UNKNOWN 145 
#define  VFT_APP 144 
#define  VFT_DLL 143 
#define  VFT_DRV 142 
#define  VFT_FONT 141 
#define  VFT_STATIC_LIB 140 
#define  VFT_UNKNOWN 139 
#define  VFT_VXD 138 
#define  VOS_DOS 137 
#define  VOS_NT 136 
#define  VOS_OS216 135 
#define  VOS_OS232 134 
#define  VOS_UNKNOWN 133 
#define  VOS__BASE 132 
#define  VOS__PM16 131 
#define  VOS__PM32 130 
#define  VOS__WINDOWS16 129 
#define  VOS__WINDOWS32 128 
 int VS_FF_DEBUG ; 
 int VS_FF_INFOINFERRED ; 
 int VS_FF_PATCHED ; 
 int VS_FF_PRERELEASE ; 
 int VS_FF_PRIVATEBUILD ; 
 int VS_FF_SPECIALBUILD ; 

__attribute__((used)) static void print_vffi_debug(const VS_FIXEDFILEINFO *vffi)
{
    BOOL    versioned_printer = FALSE;

    if((vffi->dwFileType == VFT_DLL) || (vffi->dwFileType == VFT_DRV))
    {
        if(vffi->dwFileSubtype == VFT2_DRV_VERSIONED_PRINTER)
            /* this is documented for newer w2k Drivers and up */
            versioned_printer = TRUE;
        else if( (vffi->dwFileSubtype == VFT2_DRV_PRINTER) &&
                 (vffi->dwFileVersionMS != vffi->dwProductVersionMS) &&
                 (vffi->dwFileVersionMS > 0) &&
                 (vffi->dwFileVersionMS <= 3) )
            /* found this on NT 3.51, NT4.0 and old w2k Drivers */
            versioned_printer = TRUE;
    }

    TRACE("structversion=%u.%u, ",
            HIWORD(vffi->dwStrucVersion),LOWORD(vffi->dwStrucVersion));
    if(versioned_printer)
    {
        WORD mode = LOWORD(vffi->dwFileVersionMS);
        WORD ver_rev = HIWORD(vffi->dwFileVersionLS);
        TRACE("fileversion=%u.%u.%u.%u (%s.major.minor.release), ",
            (vffi->dwFileVersionMS),
            HIBYTE(ver_rev), LOBYTE(ver_rev), LOWORD(vffi->dwFileVersionLS),
            (mode == 3) ? "Usermode" : ((mode <= 2) ? "Kernelmode" : "?") );
    }
    else
    {
        TRACE("fileversion=%u.%u.%u.%u, ",
            HIWORD(vffi->dwFileVersionMS),LOWORD(vffi->dwFileVersionMS),
            HIWORD(vffi->dwFileVersionLS),LOWORD(vffi->dwFileVersionLS));
    }
    TRACE("productversion=%u.%u.%u.%u\n",
          HIWORD(vffi->dwProductVersionMS),LOWORD(vffi->dwProductVersionMS),
          HIWORD(vffi->dwProductVersionLS),LOWORD(vffi->dwProductVersionLS));

    TRACE("flagmask=0x%x, flags=0x%x %s%s%s%s%s%s\n",
          vffi->dwFileFlagsMask, vffi->dwFileFlags,
          (vffi->dwFileFlags & VS_FF_DEBUG) ? "DEBUG," : "",
          (vffi->dwFileFlags & VS_FF_PRERELEASE) ? "PRERELEASE," : "",
          (vffi->dwFileFlags & VS_FF_PATCHED) ? "PATCHED," : "",
          (vffi->dwFileFlags & VS_FF_PRIVATEBUILD) ? "PRIVATEBUILD," : "",
          (vffi->dwFileFlags & VS_FF_INFOINFERRED) ? "INFOINFERRED," : "",
          (vffi->dwFileFlags & VS_FF_SPECIALBUILD) ? "SPECIALBUILD," : "");

    TRACE("(");

    TRACE("OS=0x%x.0x%x ", HIWORD(vffi->dwFileOS), LOWORD(vffi->dwFileOS));

    switch (vffi->dwFileOS&0xFFFF0000)
    {
    case VOS_DOS:TRACE("DOS,");break;
    case VOS_OS216:TRACE("OS/2-16,");break;
    case VOS_OS232:TRACE("OS/2-32,");break;
    case VOS_NT:TRACE("NT,");break;
    case VOS_UNKNOWN:
    default:
        TRACE("UNKNOWN(0x%x),",vffi->dwFileOS&0xFFFF0000);break;
    }

    switch (LOWORD(vffi->dwFileOS))
    {
    case VOS__BASE:TRACE("BASE");break;
    case VOS__WINDOWS16:TRACE("WIN16");break;
    case VOS__WINDOWS32:TRACE("WIN32");break;
    case VOS__PM16:TRACE("PM16");break;
    case VOS__PM32:TRACE("PM32");break;
    default:
        TRACE("UNKNOWN(0x%x)",LOWORD(vffi->dwFileOS));break;
    }

    TRACE(")\n");

    switch (vffi->dwFileType)
    {
    case VFT_APP:TRACE("filetype=APP");break;
    case VFT_DLL:
        TRACE("filetype=DLL");
        if(vffi->dwFileSubtype != 0)
        {
            if(versioned_printer) /* NT3.x/NT4.0 or old w2k Driver  */
                TRACE(",PRINTER");
            TRACE(" (subtype=0x%x)", vffi->dwFileSubtype);
        }
        break;
    case VFT_DRV:
        TRACE("filetype=DRV,");
        switch(vffi->dwFileSubtype)
        {
        case VFT2_DRV_PRINTER:TRACE("PRINTER");break;
        case VFT2_DRV_KEYBOARD:TRACE("KEYBOARD");break;
        case VFT2_DRV_LANGUAGE:TRACE("LANGUAGE");break;
        case VFT2_DRV_DISPLAY:TRACE("DISPLAY");break;
        case VFT2_DRV_MOUSE:TRACE("MOUSE");break;
        case VFT2_DRV_NETWORK:TRACE("NETWORK");break;
        case VFT2_DRV_SYSTEM:TRACE("SYSTEM");break;
        case VFT2_DRV_INSTALLABLE:TRACE("INSTALLABLE");break;
        case VFT2_DRV_SOUND:TRACE("SOUND");break;
        case VFT2_DRV_COMM:TRACE("COMM");break;
        case VFT2_DRV_INPUTMETHOD:TRACE("INPUTMETHOD");break;
        case VFT2_DRV_VERSIONED_PRINTER:TRACE("VERSIONED_PRINTER");break;
        case VFT2_UNKNOWN:
        default:
            TRACE("UNKNOWN(0x%x)",vffi->dwFileSubtype);break;
        }
        break;
    case VFT_FONT:
        TRACE("filetype=FONT,");
        switch (vffi->dwFileSubtype)
        {
        case VFT2_FONT_RASTER:TRACE("RASTER");break;
        case VFT2_FONT_VECTOR:TRACE("VECTOR");break;
        case VFT2_FONT_TRUETYPE:TRACE("TRUETYPE");break;
        default:TRACE("UNKNOWN(0x%x)",vffi->dwFileSubtype);break;
        }
        break;
    case VFT_VXD:TRACE("filetype=VXD");break;
    case VFT_STATIC_LIB:TRACE("filetype=STATIC_LIB");break;
    case VFT_UNKNOWN:
    default:
        TRACE("filetype=Unknown(0x%x)",vffi->dwFileType);break;
    }

    TRACE("\n");
    TRACE("filedate=0x%x.0x%x\n",vffi->dwFileDateMS,vffi->dwFileDateLS);
}