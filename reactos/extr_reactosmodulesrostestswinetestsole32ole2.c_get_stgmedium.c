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
typedef  int /*<<< orphan*/  STGMEDIUM ;
typedef  int CLIPFORMAT ;

/* Variables and functions */
#define  CF_DIB 130 
#define  CF_ENHMETAFILE 129 
#define  CF_METAFILEPICT 128 
 int /*<<< orphan*/  create_dib (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_emf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_mfpict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void get_stgmedium(CLIPFORMAT cfFormat, STGMEDIUM *stgmedium)
{
    switch (cfFormat)
    {
    case CF_DIB:
        create_dib(stgmedium);
        break;
    case CF_METAFILEPICT:
        create_mfpict(stgmedium);
        break;
    case CF_ENHMETAFILE:
        create_emf(stgmedium);
        break;
    default:
        ok(0, "cf %x not implemented\n", cfFormat);
    }
}