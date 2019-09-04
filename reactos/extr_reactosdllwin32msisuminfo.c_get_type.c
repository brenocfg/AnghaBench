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

/* Variables and functions */
#define  PID_APPNAME 144 
#define  PID_AUTHOR 143 
#define  PID_CHARCOUNT 142 
#define  PID_CODEPAGE 141 
#define  PID_COMMENTS 140 
#define  PID_CREATE_DTM 139 
#define  PID_KEYWORDS 138 
#define  PID_LASTAUTHOR 137 
#define  PID_LASTPRINTED 136 
#define  PID_LASTSAVE_DTM 135 
#define  PID_PAGECOUNT 134 
#define  PID_REVNUMBER 133 
#define  PID_SECURITY 132 
#define  PID_SUBJECT 131 
#define  PID_TEMPLATE 130 
#define  PID_TITLE 129 
#define  PID_WORDCOUNT 128 
 int VT_EMPTY ; 
 int VT_FILETIME ; 
 int VT_I2 ; 
 int VT_I4 ; 
 int VT_LPSTR ; 

__attribute__((used)) static UINT get_type( UINT uiProperty )
{
    switch( uiProperty )
    {
#ifdef __REACTOS__
    case PID_CODEPAGE_MSI:
#else
    case PID_CODEPAGE:
#endif
         return VT_I2;

    case PID_SUBJECT:
    case PID_AUTHOR:
    case PID_KEYWORDS:
    case PID_COMMENTS:
    case PID_TEMPLATE:
    case PID_LASTAUTHOR:
    case PID_REVNUMBER:
    case PID_APPNAME:
    case PID_TITLE:
         return VT_LPSTR;

    case PID_LASTPRINTED:
    case PID_CREATE_DTM:
    case PID_LASTSAVE_DTM:
         return VT_FILETIME;

    case PID_WORDCOUNT:
    case PID_CHARCOUNT:
#ifdef __REACTOS__
    case PID_SECURITY_MSI:
#else
    case PID_SECURITY:
#endif
    case PID_PAGECOUNT:
         return VT_I4;
    }
    return VT_EMPTY;
}