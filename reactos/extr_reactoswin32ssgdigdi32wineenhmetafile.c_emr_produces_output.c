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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  EMR_ALPHABLEND 176 
#define  EMR_ANGLEARC 175 
#define  EMR_ARC 174 
#define  EMR_ARCTO 173 
#define  EMR_BITBLT 172 
#define  EMR_CHORD 171 
#define  EMR_ELLIPSE 170 
#define  EMR_EXCLUDECLIPRECT 169 
#define  EMR_EXTFLOODFILL 168 
#define  EMR_EXTTEXTOUTA 167 
#define  EMR_EXTTEXTOUTW 166 
#define  EMR_FILLRGN 165 
#define  EMR_FRAMERGN 164 
#define  EMR_GDICOMMENT 163 
#define  EMR_INTERSECTCLIPRECT 162 
#define  EMR_INVERTRGN 161 
#define  EMR_LINETO 160 
#define  EMR_MASKBLT 159 
#define  EMR_MOVETOEX 158 
#define  EMR_PAINTRGN 157 
#define  EMR_PIE 156 
#define  EMR_PLGBLT 155 
#define  EMR_POLYBEZIER 154 
#define  EMR_POLYBEZIER16 153 
#define  EMR_POLYBEZIERTO 152 
#define  EMR_POLYBEZIERTO16 151 
#define  EMR_POLYDRAW 150 
#define  EMR_POLYDRAW16 149 
#define  EMR_POLYGON 148 
#define  EMR_POLYGON16 147 
#define  EMR_POLYLINE 146 
#define  EMR_POLYLINE16 145 
#define  EMR_POLYLINETO 144 
#define  EMR_POLYLINETO16 143 
#define  EMR_POLYPOLYGON 142 
#define  EMR_POLYPOLYGON16 141 
#define  EMR_POLYPOLYLINE 140 
#define  EMR_POLYPOLYLINE16 139 
#define  EMR_POLYTEXTOUTA 138 
#define  EMR_POLYTEXTOUTW 137 
#define  EMR_RECTANGLE 136 
#define  EMR_ROUNDRECT 135 
#define  EMR_SELECTOBJECT 134 
#define  EMR_SETDIBITSTODEVICE 133 
#define  EMR_SETPIXELV 132 
#define  EMR_SMALLTEXTOUT 131 
#define  EMR_STRETCHBLT 130 
#define  EMR_STRETCHDIBITS 129 
#define  EMR_TRANSPARENTBLT 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL emr_produces_output(int type)
{
    switch(type) {
    case EMR_POLYBEZIER:
    case EMR_POLYGON:
    case EMR_POLYLINE:
    case EMR_POLYBEZIERTO:
    case EMR_POLYLINETO:
    case EMR_POLYPOLYLINE:
    case EMR_POLYPOLYGON:
    case EMR_SETPIXELV:
    case EMR_MOVETOEX:
    case EMR_EXCLUDECLIPRECT:
    case EMR_INTERSECTCLIPRECT:
    case EMR_SELECTOBJECT:
    case EMR_ANGLEARC:
    case EMR_ELLIPSE:
    case EMR_RECTANGLE:
    case EMR_ROUNDRECT:
    case EMR_ARC:
    case EMR_CHORD:
    case EMR_PIE:
    case EMR_EXTFLOODFILL:
    case EMR_LINETO:
    case EMR_ARCTO:
    case EMR_POLYDRAW:
    case EMR_GDICOMMENT:
    case EMR_FILLRGN:
    case EMR_FRAMERGN:
    case EMR_INVERTRGN:
    case EMR_PAINTRGN:
    case EMR_BITBLT:
    case EMR_STRETCHBLT:
    case EMR_MASKBLT:
    case EMR_PLGBLT:
    case EMR_SETDIBITSTODEVICE:
    case EMR_STRETCHDIBITS:
    case EMR_EXTTEXTOUTA:
    case EMR_EXTTEXTOUTW:
    case EMR_POLYBEZIER16:
    case EMR_POLYGON16:
    case EMR_POLYLINE16:
    case EMR_POLYBEZIERTO16:
    case EMR_POLYLINETO16:
    case EMR_POLYPOLYLINE16:
    case EMR_POLYPOLYGON16:
    case EMR_POLYDRAW16:
    case EMR_POLYTEXTOUTA:
    case EMR_POLYTEXTOUTW:
    case EMR_SMALLTEXTOUT:
    case EMR_ALPHABLEND:
    case EMR_TRANSPARENTBLT:
        return TRUE;
    default:
        return FALSE;
    }
}