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
struct ParseTypedefData {char* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTS_ABORTIF (struct ParseTypedefData*,int) ; 
 int stabs_pts_read_number (struct ParseTypedefData*,long*) ; 

__attribute__((used)) static int stabs_pts_read_type_reference(struct ParseTypedefData* ptd,
                                         long* filenr, long* subnr)
{
    if (*ptd->ptr == '(')
    {
	/* '(' <int> ',' <int> ')' */
	ptd->ptr++;
	PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, filenr) == -1);
	PTS_ABORTIF(ptd, *ptd->ptr++ != ',');
	PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, subnr) == -1);
	PTS_ABORTIF(ptd, *ptd->ptr++ != ')');
    }
    else
    {
    	*filenr = 0;
	PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, subnr) == -1);
    }
    return 0;
}