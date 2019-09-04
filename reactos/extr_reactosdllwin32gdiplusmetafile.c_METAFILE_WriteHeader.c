#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int Flags; int /*<<< orphan*/  Type; } ;
struct TYPE_9__ {int EmfPlusFlags; scalar_t__ LogicalDpiY; scalar_t__ LogicalDpiX; int /*<<< orphan*/  Version; TYPE_1__ Header; } ;
struct TYPE_8__ {scalar_t__ metafile_type; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_2__ GpMetafile ;
typedef  TYPE_3__ EmfPlusHeader ;

/* Variables and functions */
 scalar_t__ DT_RASDISPLAY ; 
 int /*<<< orphan*/  EmfPlusRecordTypeHeader ; 
 scalar_t__ GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  METAFILE_AllocateRecord (TYPE_2__*,int,void**) ; 
 int /*<<< orphan*/  METAFILE_WriteRecords (TYPE_2__*) ; 
 scalar_t__ MetafileTypeEmfPlusDual ; 
 scalar_t__ MetafileTypeEmfPlusOnly ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  TECHNOLOGY ; 
 int /*<<< orphan*/  VERSION_MAGIC2 ; 

__attribute__((used)) static GpStatus METAFILE_WriteHeader(GpMetafile *metafile, HDC hdc)
{
    GpStatus stat;

    if (metafile->metafile_type == MetafileTypeEmfPlusOnly || metafile->metafile_type == MetafileTypeEmfPlusDual)
    {
        EmfPlusHeader *header;

        stat = METAFILE_AllocateRecord(metafile, sizeof(EmfPlusHeader), (void**)&header);
        if (stat != Ok)
            return stat;

        header->Header.Type = EmfPlusRecordTypeHeader;

        if (metafile->metafile_type == MetafileTypeEmfPlusDual)
            header->Header.Flags = 1;
        else
            header->Header.Flags = 0;

        header->Version = VERSION_MAGIC2;

        if (GetDeviceCaps(hdc, TECHNOLOGY) == DT_RASDISPLAY)
            header->EmfPlusFlags = 1;
        else
            header->EmfPlusFlags = 0;

        header->LogicalDpiX = GetDeviceCaps(hdc, LOGPIXELSX);
        header->LogicalDpiY = GetDeviceCaps(hdc, LOGPIXELSY);

        METAFILE_WriteRecords(metafile);
    }

    return Ok;
}