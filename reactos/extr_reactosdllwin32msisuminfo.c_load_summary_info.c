#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_17__ {int /*<<< orphan*/  property; } ;
struct TYPE_16__ {int wByteOrder; size_t cbSection; int /*<<< orphan*/  cProperties; int /*<<< orphan*/  dwOffset; int /*<<< orphan*/  fmtid; } ;
typedef  TYPE_1__ PROPERTYSETHEADER ;
typedef  TYPE_1__ PROPERTYSECTIONHEADER ;
typedef  TYPE_3__ MSISUMMARYINFO ;
typedef  TYPE_1__* LPBYTE ;
typedef  TYPE_5__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ FORMATIDOFFSET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,size_t,...) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMTID_SummaryInformation ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,TYPE_1__*,size_t,size_t*) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_5__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSI_MAX_PROPS ; 
 size_t SECT_HDR_SIZE ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,size_t) ; 
 TYPE_1__* msi_alloc (size_t) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  read_properties_from_data (int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 

__attribute__((used)) static UINT load_summary_info( MSISUMMARYINFO *si, IStream *stm )
{
    PROPERTYSETHEADER set_hdr;
    FORMATIDOFFSET format_hdr;
    PROPERTYSECTIONHEADER section_hdr;
    LPBYTE data = NULL;
    LARGE_INTEGER ofs;
    ULONG count, sz;
    HRESULT r;

    TRACE("%p %p\n", si, stm);

    /* read the header */
    sz = sizeof set_hdr;
    r = IStream_Read( stm, &set_hdr, sz, &count );
    if( FAILED(r) || count != sz )
        return ERROR_FUNCTION_FAILED;

    if( set_hdr.wByteOrder != 0xfffe )
    {
        ERR("property set not big-endian %04X\n", set_hdr.wByteOrder);
        return ERROR_FUNCTION_FAILED;
    }

    sz = sizeof format_hdr;
    r = IStream_Read( stm, &format_hdr, sz, &count );
    if( FAILED(r) || count != sz )
        return ERROR_FUNCTION_FAILED;

    /* check the format id is correct */
    if( !IsEqualGUID( &FMTID_SummaryInformation, &format_hdr.fmtid ) )
        return ERROR_FUNCTION_FAILED;

    /* seek to the location of the section */
    ofs.QuadPart = format_hdr.dwOffset;
    r = IStream_Seek( stm, ofs, STREAM_SEEK_SET, NULL );
    if( FAILED(r) )
        return ERROR_FUNCTION_FAILED;

    /* read the section itself */
    sz = SECT_HDR_SIZE;
    r = IStream_Read( stm, &section_hdr, sz, &count );
    if( FAILED(r) || count != sz )
        return ERROR_FUNCTION_FAILED;

    if( section_hdr.cProperties > MSI_MAX_PROPS )
    {
        ERR("too many properties %d\n", section_hdr.cProperties);
        return ERROR_FUNCTION_FAILED;
    }

    data = msi_alloc( section_hdr.cbSection);
    if( !data )
        return ERROR_FUNCTION_FAILED;

    memcpy( data, &section_hdr, SECT_HDR_SIZE );

    /* read all the data in one go */
    sz = section_hdr.cbSection - SECT_HDR_SIZE;
    r = IStream_Read( stm, &data[ SECT_HDR_SIZE ], sz, &count );
    if( SUCCEEDED(r) && count == sz )
        read_properties_from_data( si->property, data, sz + SECT_HDR_SIZE );
    else
        ERR("failed to read properties %d %d\n", count, sz);

    msi_free( data );
    return ERROR_SUCCESS;
}