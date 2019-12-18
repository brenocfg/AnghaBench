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
typedef  int /*<<< orphan*/  METAHEADER ;
typedef  int /*<<< orphan*/  HMETAFILE ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_METAFILE ; 
 int /*<<< orphan*/  alloc_gdi_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HMETAFILE MF_Create_HMETAFILE(METAHEADER *mh)
{
    return alloc_gdi_handle( mh, OBJ_METAFILE, NULL );
}