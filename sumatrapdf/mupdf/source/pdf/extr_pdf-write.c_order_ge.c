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
 int USE_CATALOGUE ; 
 int USE_HINTS ; 
 int USE_OTHER_OBJECTS ; 
 int USE_PAGE1 ; 
 int USE_PAGE_OBJECT ; 
 int USE_PAGE_SHIFT ; 
 int USE_PARAMS ; 
 int USE_SHARED ; 

__attribute__((used)) static int
order_ge(int ui, int uj)
{
	/*
	For linearization, we need to order the sections as follows:

		Remaining pages					(Part 7)
		Shared objects					(Part 8)
		Objects not associated with any page		(Part 9)
		Any "other" objects
							(Header)(Part 1)
		(Linearization params)				(Part 2)
					(1st page Xref/Trailer)	(Part 3)
		Catalogue (and other document level objects)	(Part 4)
		First page					(Part 6)
		(Primary Hint stream)			(*)	(Part 5)
		Any free objects

	Note, this is NOT the same order they appear in
	the final file!

	(*) The PDF reference gives us the option of putting the hint stream
	after the first page, and we take it, for simplicity.
	*/

	/* If the 2 objects are in the same section, then page object comes first. */
	if (((ui ^ uj) & ~USE_PAGE_OBJECT) == 0)
		return ((ui & USE_PAGE_OBJECT) == 0);
	/* Put unused objects last */
	else if (ui == 0)
		return 1;
	else if (uj == 0)
		return 0;
	/* Put the hint stream before that... */
	else if (ui & USE_HINTS)
		return 1;
	else if (uj & USE_HINTS)
		return 0;
	/* Put page 1 before that... */
	else if (ui & USE_PAGE1)
		return 1;
	else if (uj & USE_PAGE1)
		return 0;
	/* Put the catalogue before that... */
	else if (ui & USE_CATALOGUE)
		return 1;
	else if (uj & USE_CATALOGUE)
		return 0;
	/* Put the linearization params before that... */
	else if (ui & USE_PARAMS)
		return 1;
	else if (uj & USE_PARAMS)
		return 0;
	/* Put other objects before that */
	else if (ui & USE_OTHER_OBJECTS)
		return 1;
	else if (uj & USE_OTHER_OBJECTS)
		return 0;
	/* Put shared objects before that... */
	else if (ui & USE_SHARED)
		return 1;
	else if (uj & USE_SHARED)
		return 0;
	/* And otherwise, order by the page number on which
	 * they are used. */
	return (ui>>USE_PAGE_SHIFT) >= (uj>>USE_PAGE_SHIFT);
}