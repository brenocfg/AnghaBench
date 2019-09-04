#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sectionHdr ;
typedef  int /*<<< orphan*/  dwTemp ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_16__ {void* QuadPart; } ;
struct TYPE_13__ {scalar_t__ lVal; int /*<<< orphan*/  iVal; } ;
struct TYPE_15__ {TYPE_1__ u; void* vt; } ;
struct TYPE_14__ {scalar_t__ locale; int grfFlags; int /*<<< orphan*/  stm; int /*<<< orphan*/  codePage; int /*<<< orphan*/  name_to_propid; int /*<<< orphan*/  propid_to_prop; } ;
typedef  TYPE_2__ PropertyStorage_impl ;
typedef  TYPE_3__ PROPVARIANT ;
typedef  int PROPERTYSECTIONHEADER ;
typedef  int /*<<< orphan*/  PROPERTYIDOFFSET ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  TYPE_4__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ ,TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  PID_BEHAVIOR ; 
 int /*<<< orphan*/  PID_CODEPAGE ; 
 int /*<<< orphan*/  PID_LOCALE ; 
 int PROPSETFLAG_CASE_SENSITIVE ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_3__*) ; 
 int /*<<< orphan*/  PropertyStorage_MakeSectionHdr (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  PropertyStorage_WriteDictionaryToStream (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  PropertyStorage_WriteHeadersToStream (TYPE_2__*) ; 
 int /*<<< orphan*/  PropertyStorage_WritePropertiesToStream (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  PropertyStorage_WritePropertyToStream (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int*) ; 
 void* SECTIONHEADER_OFFSET ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  StorageUtl_WriteDWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* VT_I2 ; 
 void* VT_I4 ; 
 scalar_t__ dictionary_num_entries (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT PropertyStorage_WriteToStream(PropertyStorage_impl *This)
{
    PROPERTYSECTIONHEADER sectionHdr;
    HRESULT hr;
    ULONG count;
    LARGE_INTEGER seek;
    DWORD numProps, prop, sectionOffset, dwTemp;
    PROPVARIANT var;

    PropertyStorage_WriteHeadersToStream(This);

    /* Count properties.  Always at least one property, the code page */
    numProps = 1;
    if (dictionary_num_entries(This->name_to_propid))
        numProps++;
    if (This->locale != LOCALE_SYSTEM_DEFAULT)
        numProps++;
    if (This->grfFlags & PROPSETFLAG_CASE_SENSITIVE)
        numProps++;
    numProps += dictionary_num_entries(This->propid_to_prop);

    /* Write section header with 0 bytes right now, I'll adjust it after
     * writing properties.
     */
    PropertyStorage_MakeSectionHdr(0, numProps, &sectionHdr);
    seek.QuadPart = SECTIONHEADER_OFFSET;
    hr = IStream_Seek(This->stm, seek, STREAM_SEEK_SET, NULL);
    if (FAILED(hr))
        goto end;
    hr = IStream_Write(This->stm, &sectionHdr, sizeof(sectionHdr), &count);
    if (FAILED(hr))
        goto end;

    prop = 0;
    sectionOffset = sizeof(PROPERTYSECTIONHEADER) +
     numProps * sizeof(PROPERTYIDOFFSET);

    if (dictionary_num_entries(This->name_to_propid))
    {
        prop++;
        hr = PropertyStorage_WriteDictionaryToStream(This, &sectionOffset);
        if (FAILED(hr))
            goto end;
    }

    PropVariantInit(&var);

    var.vt = VT_I2;
    var.u.iVal = This->codePage;
    hr = PropertyStorage_WritePropertyToStream(This, prop++, PID_CODEPAGE,
     &var, &sectionOffset);
    if (FAILED(hr))
        goto end;

    if (This->locale != LOCALE_SYSTEM_DEFAULT)
    {
        var.vt = VT_I4;
        var.u.lVal = This->locale;
        hr = PropertyStorage_WritePropertyToStream(This, prop++, PID_LOCALE,
         &var, &sectionOffset);
        if (FAILED(hr))
            goto end;
    }

    if (This->grfFlags & PROPSETFLAG_CASE_SENSITIVE)
    {
        var.vt = VT_I4;
        var.u.lVal = 1;
        hr = PropertyStorage_WritePropertyToStream(This, prop++, PID_BEHAVIOR,
         &var, &sectionOffset);
        if (FAILED(hr))
            goto end;
    }

    hr = PropertyStorage_WritePropertiesToStream(This, prop, &sectionOffset);
    if (FAILED(hr))
        goto end;

    /* Now write the byte count of the section */
    seek.QuadPart = SECTIONHEADER_OFFSET;
    hr = IStream_Seek(This->stm, seek, STREAM_SEEK_SET, NULL);
    if (FAILED(hr))
        goto end;
    StorageUtl_WriteDWord((LPBYTE)&dwTemp, 0, sectionOffset);
    hr = IStream_Write(This->stm, &dwTemp, sizeof(dwTemp), &count);

end:
    return hr;
}