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
typedef  int WORD ;
typedef  int /*<<< orphan*/  GDILOOBJTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  GDILoObjType_LO_ALTDC_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_BITMAP_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_BRUSH_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_DC_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_EXTPEN_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_FONT_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_ICMLCS_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_METADC16_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_METAFILE16_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_METAFILE_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_PALETTE_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_PEN_TYPE ; 
 int /*<<< orphan*/  GDILoObjType_LO_REGION_TYPE ; 
#define  OBJ_BITMAP 141 
#define  OBJ_BRUSH 140 
#define  OBJ_COLORSPACE 139 
#define  OBJ_DC 138 
#define  OBJ_ENHMETADC 137 
#define  OBJ_ENHMETAFILE 136 
#define  OBJ_EXTPEN 135 
#define  OBJ_FONT 134 
#define  OBJ_MEMDC 133 
#define  OBJ_METADC 132 
#define  OBJ_METAFILE 131 
#define  OBJ_PAL 130 
#define  OBJ_PEN 129 
#define  OBJ_REGION 128 

__attribute__((used)) static
GDILOOBJTYPE
ConvertObjectType(
    WORD wType)
{
    /* Get the GDI object type */
    switch (wType)
    {
        case OBJ_PEN: return GDILoObjType_LO_PEN_TYPE;
        case OBJ_BRUSH: return GDILoObjType_LO_BRUSH_TYPE;
        case OBJ_DC: return GDILoObjType_LO_DC_TYPE;
        case OBJ_METADC: return GDILoObjType_LO_METADC16_TYPE;
        case OBJ_PAL: return GDILoObjType_LO_PALETTE_TYPE;
        case OBJ_FONT: return GDILoObjType_LO_FONT_TYPE;
        case OBJ_BITMAP: return GDILoObjType_LO_BITMAP_TYPE;
        case OBJ_REGION: return GDILoObjType_LO_REGION_TYPE;
        case OBJ_METAFILE: return GDILoObjType_LO_METAFILE16_TYPE;
        case OBJ_MEMDC: return GDILoObjType_LO_DC_TYPE;
        case OBJ_EXTPEN: return GDILoObjType_LO_EXTPEN_TYPE;
        case OBJ_ENHMETADC: return GDILoObjType_LO_ALTDC_TYPE;
        case OBJ_ENHMETAFILE: return GDILoObjType_LO_METAFILE_TYPE;
        case OBJ_COLORSPACE: return GDILoObjType_LO_ICMLCS_TYPE;
        default: return 0;
    }
}