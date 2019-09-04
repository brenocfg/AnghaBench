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
typedef  int /*<<< orphan*/  uchar ;
typedef  int /*<<< orphan*/  DwarfBuf ;

/* Variables and functions */
#define  FormFlag 128 
 int /*<<< orphan*/  dwarfget1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
getuchar(DwarfBuf *b, int form, uchar *u)
{
    switch(form){
    default:
        return -1;

    case FormFlag:
        *u = dwarfget1(b);
        return 0;
    }
}