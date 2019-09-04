#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_17__ {int /*<<< orphan*/ * property; } ;
struct TYPE_16__ {int cbSection; size_t cProperties; int propid; int dwOffset; } ;
struct TYPE_15__ {int wByteOrder; int dwOSVer; int reserved; int dwOffset; int /*<<< orphan*/  fmtid; scalar_t__ wFormat; } ;
typedef  TYPE_1__ PROPERTYSETHEADER ;
typedef  TYPE_2__ PROPERTYSECTIONHEADER ;
typedef  TYPE_2__ PROPERTYIDOFFSET ;
typedef  TYPE_4__ MSISUMMARYINFO ;
typedef  TYPE_1__* LPBYTE ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ FORMATIDOFFSET ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMTID_SummaryInformation ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ *,TYPE_1__*,size_t,size_t*) ; 
 int MSI_MAX_PROPS ; 
 int get_property_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* msi_alloc_zero (size_t) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 
 size_t write_property_to_data (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static UINT save_summary_info( const MSISUMMARYINFO * si, IStream *stm )
{
    UINT ret = ERROR_FUNCTION_FAILED;
    PROPERTYSETHEADER set_hdr;
    FORMATIDOFFSET format_hdr;
    PROPERTYSECTIONHEADER section_hdr;
    PROPERTYIDOFFSET idofs[MSI_MAX_PROPS];
    LPBYTE data = NULL;
    ULONG count, sz;
    HRESULT r;
    int i;

    /* write the header */
    sz = sizeof set_hdr;
    memset( &set_hdr, 0, sz );
    set_hdr.wByteOrder = 0xfffe;
    set_hdr.wFormat = 0;
    set_hdr.dwOSVer = 0x00020005; /* build 5, platform id 2 */
    /* set_hdr.clsID is {00000000-0000-0000-0000-000000000000} */
    set_hdr.reserved = 1;
    r = IStream_Write( stm, &set_hdr, sz, &count );
    if( FAILED(r) || count != sz )
        return ret;

    /* write the format header */
    sz = sizeof format_hdr;
    format_hdr.fmtid = FMTID_SummaryInformation;
    format_hdr.dwOffset = sizeof format_hdr + sizeof set_hdr;
    r = IStream_Write( stm, &format_hdr, sz, &count );
    if( FAILED(r) || count != sz )
        return ret;

    /* add up how much space the data will take and calculate the offsets */
    section_hdr.cbSection = sizeof section_hdr;
    section_hdr.cbSection += (get_property_count( si->property ) * sizeof idofs[0]);
    section_hdr.cProperties = 0;
    for( i = 0; i < MSI_MAX_PROPS; i++ )
    {
        sz = write_property_to_data( &si->property[i], NULL );
        if( !sz )
            continue;
        idofs[ section_hdr.cProperties ].propid = i;
        idofs[ section_hdr.cProperties ].dwOffset = section_hdr.cbSection;
        section_hdr.cProperties++;
        section_hdr.cbSection += sz;
    }

    data = msi_alloc_zero( section_hdr.cbSection );

    sz = 0;
    memcpy( &data[sz], &section_hdr, sizeof section_hdr );
    sz += sizeof section_hdr;

    memcpy( &data[sz], idofs, section_hdr.cProperties * sizeof idofs[0] );
    sz += section_hdr.cProperties * sizeof idofs[0];

    /* write out the data */
    for( i = 0; i < MSI_MAX_PROPS; i++ )
        sz += write_property_to_data( &si->property[i], &data[sz] );

    r = IStream_Write( stm, data, sz, &count );
    msi_free( data );
    if( FAILED(r) || count != sz )
        return ret;

    return ERROR_SUCCESS;
}