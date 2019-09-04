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
typedef  int UINT ;
typedef  char TCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int GDI_HANDLE_GET_TYPE (int /*<<< orphan*/ ) ; 
#define  GDI_OBJECT_TYPE_BITMAP 146 
#define  GDI_OBJECT_TYPE_BRUSH 145 
#define  GDI_OBJECT_TYPE_COLORSPACE 144 
#define  GDI_OBJECT_TYPE_DC 143 
#define  GDI_OBJECT_TYPE_DCE 142 
#define  GDI_OBJECT_TYPE_DONTCARE 141 
#define  GDI_OBJECT_TYPE_EMF 140 
#define  GDI_OBJECT_TYPE_ENHMETADC 139 
#define  GDI_OBJECT_TYPE_ENHMETAFILE 138 
#define  GDI_OBJECT_TYPE_EXTPEN 137 
#define  GDI_OBJECT_TYPE_FONT 136 
#define  GDI_OBJECT_TYPE_MEMDC 135 
#define  GDI_OBJECT_TYPE_METADC 134 
#define  GDI_OBJECT_TYPE_METAFILE 133 
#define  GDI_OBJECT_TYPE_PALETTE 132 
#define  GDI_OBJECT_TYPE_PEN 131 
#define  GDI_OBJECT_TYPE_PFE 130 
#define  GDI_OBJECT_TYPE_REGION 129 
#define  GDI_OBJECT_TYPE_SILENT 128 

TCHAR*
GetTypeName(HANDLE handle)
{
	TCHAR* strText;
	UINT Type = GDI_HANDLE_GET_TYPE(handle);

	switch (Type)
	{
		case GDI_OBJECT_TYPE_DC:
			strText = L"DC";
			break;
		case GDI_OBJECT_TYPE_REGION:
			strText = L"Region";
			break;
		case GDI_OBJECT_TYPE_BITMAP:
			strText = L"Bitmap";
			break;
		case GDI_OBJECT_TYPE_PALETTE:
			strText = L"Palette";
			break;
		case GDI_OBJECT_TYPE_FONT:
			strText = L"Font";
			break;
		case GDI_OBJECT_TYPE_BRUSH:
			strText = L"Brush";
			break;
		case GDI_OBJECT_TYPE_EMF:
			strText = L"EMF";
			break;
		case GDI_OBJECT_TYPE_PEN:
			strText = L"Pen";
			break;
		case GDI_OBJECT_TYPE_EXTPEN:
			strText = L"ExtPen";
			break;
		case GDI_OBJECT_TYPE_COLORSPACE:
			strText = L"ColSpace";
			break;
		case GDI_OBJECT_TYPE_METADC:
			strText = L"MetaDC";
			break;
		case GDI_OBJECT_TYPE_METAFILE:
			strText = L"Metafile";
			break;
		case GDI_OBJECT_TYPE_ENHMETAFILE:
			strText = L"EMF";
			break;
		case GDI_OBJECT_TYPE_ENHMETADC:
			strText = L"EMDC";
			break;
		case GDI_OBJECT_TYPE_MEMDC:
			strText = L"MemDC";
			break;
		case GDI_OBJECT_TYPE_DCE:
			strText = L"DCE";
			break;
		case GDI_OBJECT_TYPE_PFE:
			strText = L"PFE";
			break;
		case GDI_OBJECT_TYPE_DONTCARE:
			strText = L"anything";
			break;
		case GDI_OBJECT_TYPE_SILENT:
		default:
			strText = L"unknown";
			break;
	}
	return strText;
}