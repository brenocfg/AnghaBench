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
typedef  int SHORT ;

/* Variables and functions */
#define  VT_BLOB 140 
#define  VT_EMPTY 139 
#define  VT_I1 138 
#define  VT_I2 137 
#define  VT_I4 136 
#define  VT_I8 135 
#define  VT_LPSTR 134 
#define  VT_R4 133 
#define  VT_R8 132 
#define  VT_UI1 131 
#define  VT_UI2 130 
#define  VT_UI4 129 
#define  VT_UI8 128 

__attribute__((used)) static int tag_to_vt(SHORT tag)
{
    static const int tag2vt[] =
    {
        VT_EMPTY, /* 0 */
        VT_UI1,   /* IFD_BYTE 1 */
        VT_LPSTR, /* IFD_ASCII 2 */
        VT_UI2,   /* IFD_SHORT 3 */
        VT_UI4,   /* IFD_LONG 4 */
        VT_UI8,   /* IFD_RATIONAL 5 */
        VT_I1,    /* IFD_SBYTE 6 */
        VT_BLOB,  /* IFD_UNDEFINED 7 */
        VT_I2,    /* IFD_SSHORT 8 */
        VT_I4,    /* IFD_SLONG 9 */
        VT_I8,    /* IFD_SRATIONAL 10 */
        VT_R4,    /* IFD_FLOAT 11 */
        VT_R8,    /* IFD_DOUBLE 12 */
        VT_BLOB,  /* IFD_IFD 13 */
    };
    return (tag > 0 && tag <= 13) ? tag2vt[tag] : VT_BLOB;
}