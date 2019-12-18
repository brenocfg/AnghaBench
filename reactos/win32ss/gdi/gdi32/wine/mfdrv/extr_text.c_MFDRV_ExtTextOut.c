#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int /*<<< orphan*/  ciACP; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdc; } ;
struct TYPE_11__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_10__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT16 ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PHYSDEV ;
typedef  scalar_t__* LPSTR ;
typedef  scalar_t__* LPINT16 ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  INT16 ;
typedef  scalar_t__ INT ;
typedef  int DWORD ;
typedef  TYPE_4__ CHARSETINFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CELTIC_CHARSET 136 
 int /*<<< orphan*/  CP_ACP ; 
#define  DEFAULT_CHARSET 135 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GetACP () ; 
 int /*<<< orphan*/  GetOEMCP () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetTextCharset (int /*<<< orphan*/ ) ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
#define  ISO10_CHARSET 134 
#define  ISO3_CHARSET 133 
#define  ISO4_CHARSET 132 
 scalar_t__ IsDBCSLeadByteEx (int /*<<< orphan*/ ,scalar_t__) ; 
#define  KOI8_CHARSET 131 
 int /*<<< orphan*/  MFDRV_MetaExtTextOut (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*,int,scalar_t__*) ; 
#define  OEM_CHARSET 130 
 int /*<<< orphan*/  TCI_SRCCHARSET ; 
#define  TCVN_CHARSET 129 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ TranslateCharsetInfo (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULongToPtr (int) ; 
#define  VISCII_CHARSET 128 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_an (scalar_t__*,int) ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL MFDRV_ExtTextOut( PHYSDEV dev, INT x, INT y, UINT flags,
                       const RECT *lprect, LPCWSTR str, UINT count, const INT *lpDx )
{
    RECT16	rect16;
    LPINT16	lpdx16 = NULL;
    BOOL	ret;
    unsigned int i, j;
    LPSTR       ascii;
    DWORD len;
    CHARSETINFO csi;
    int charset = GetTextCharset( dev->hdc );
    UINT cp = CP_ACP;

    if(TranslateCharsetInfo(ULongToPtr(charset), &csi, TCI_SRCCHARSET))
        cp = csi.ciACP;
    else {
        switch(charset) {
	case OEM_CHARSET:
	    cp = GetOEMCP();
	    break;
	case DEFAULT_CHARSET:
	    cp = GetACP();
	    break;

	case VISCII_CHARSET:
	case TCVN_CHARSET:
	case KOI8_CHARSET:
	case ISO3_CHARSET:
	case ISO4_CHARSET:
	case ISO10_CHARSET:
	case CELTIC_CHARSET:
	  /* FIXME: These have no place here, but because x11drv
	     enumerates fonts with these (made up) charsets some apps
	     might use them and then the FIXME below would become
	     annoying.  Now we could pick the intended codepage for
	     each of these, but since it's broken anyway we'll just
	     use CP_ACP and hope it'll go away...
	  */
	    cp = CP_ACP;
	    break;


	default:
	    FIXME("Can't find codepage for charset %d\n", charset);
	    break;
	}
    }


    TRACE("cp == %d\n", cp);
    len = WideCharToMultiByte(cp, 0, str, count, NULL, 0, NULL, NULL);
    ascii = HeapAlloc(GetProcessHeap(), 0, len);
    WideCharToMultiByte(cp, 0, str, count, ascii, len, NULL, NULL);
    TRACE("mapped %s -> %s\n", debugstr_wn(str, count), debugstr_an(ascii, len));


    if (lprect)
    {
        rect16.left   = lprect->left;
        rect16.top    = lprect->top;
        rect16.right  = lprect->right;
        rect16.bottom = lprect->bottom;
    }

    if(lpDx) {
        lpdx16 = HeapAlloc( GetProcessHeap(), 0, sizeof(INT16)*len );
	for(i = j = 0; i < len; )
	    if(IsDBCSLeadByteEx(cp, ascii[i])) {
	        lpdx16[i++] = lpDx[j++];
		lpdx16[i++] = 0;
	    } else
	        lpdx16[i++] = lpDx[j++];
    }

    ret = MFDRV_MetaExtTextOut(dev,x,y,flags,lprect?&rect16:NULL,ascii,len,lpdx16);
    HeapFree( GetProcessHeap(), 0, ascii );
    HeapFree( GetProcessHeap(), 0, lpdx16 );
    return ret;
}