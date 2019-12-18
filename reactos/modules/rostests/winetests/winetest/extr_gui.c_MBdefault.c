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

/* Variables and functions */
#define  IDABORT 134 
#define  IDCANCEL 133 
#define  IDIGNORE 132 
#define  IDNO 131 
#define  IDOK 130 
#define  IDRETRY 129 
#define  IDYES 128 
 int MB_DEFBUTTON2 ; 
 int MB_DEFMASK ; 
 int MB_TYPEMASK ; 

__attribute__((used)) static int
MBdefault (int uType)
{
    static const int matrix[][4] = {{IDOK,    0,        0,        0},
                                    {IDOK,    IDCANCEL, 0,        0},
                                    {IDABORT, IDRETRY,  IDIGNORE, 0},
                                    {IDYES,   IDNO,     IDCANCEL, 0},
                                    {IDYES,   IDNO,     0,        0},
                                    {IDRETRY, IDCANCEL, 0,        0}};
    int type = uType & MB_TYPEMASK;
    int def  = (uType & MB_DEFMASK) / MB_DEFBUTTON2;

    return matrix[type][def];
}