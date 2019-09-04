#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ptr; int /*<<< orphan*/ * end; } ;
typedef  TYPE_2__ xmlbuf_t ;
struct assembly_identity {int dummy; } ;
struct TYPE_4__ {void* info; int /*<<< orphan*/  type; } ;
struct assembly {TYPE_1__ manifest; void* directory; } ;
struct actctx_loader {int /*<<< orphan*/  actctx; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_PATH_TYPE_NONE ; 
 int /*<<< orphan*/  ACTIVATION_CONTEXT_PATH_TYPE_WIN32_FILE ; 
 int /*<<< orphan*/  ASSEMBLY_MANIFEST ; 
 int /*<<< orphan*/  ASSEMBLY_SHARED_MANIFEST ; 
 int /*<<< orphan*/  DPRINT (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int IS_TEXT_UNICODE_REVERSE_SIGNATURE ; 
 int IS_TEXT_UNICODE_SIGNATURE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 scalar_t__ RtlIsTextUnicode (void const*,int,int*) ; 
 int /*<<< orphan*/  RtlMultiByteToUnicodeN (int /*<<< orphan*/ *,int,int*,void const*,int) ; 
 int /*<<< orphan*/  RtlMultiByteToUnicodeSize (int*,void const*,int) ; 
 int /*<<< orphan*/  RtlUshortByteSwap (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_SXS_CANT_GEN_ACTCTX ; 
 struct assembly* add_assembly (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_manifest_buffer (struct actctx_loader*,struct assembly*,struct assembly_identity*,TYPE_2__*) ; 
 void* strdupW (scalar_t__) ; 

__attribute__((used)) static NTSTATUS parse_manifest( struct actctx_loader* acl, struct assembly_identity* ai,
                                LPCWSTR filename, LPCWSTR directory, BOOL shared,
                                const void *buffer, SIZE_T size )
{
    xmlbuf_t xmlbuf;
    NTSTATUS status;
    struct assembly *assembly;
    int unicode_tests;

    DPRINT( "parsing manifest loaded from %S base dir %S\n", filename, directory );

    if (!(assembly = add_assembly(acl->actctx, shared ? ASSEMBLY_SHARED_MANIFEST : ASSEMBLY_MANIFEST)))
        return STATUS_SXS_CANT_GEN_ACTCTX;

    if (directory && !(assembly->directory = strdupW(directory)))
        return STATUS_NO_MEMORY;

    if (filename) assembly->manifest.info = strdupW( filename + 4 /* skip \??\ prefix */ );
    assembly->manifest.type = assembly->manifest.info ? ACTIVATION_CONTEXT_PATH_TYPE_WIN32_FILE
                                                      : ACTIVATION_CONTEXT_PATH_TYPE_NONE;

    unicode_tests = IS_TEXT_UNICODE_SIGNATURE | IS_TEXT_UNICODE_REVERSE_SIGNATURE;
    if (RtlIsTextUnicode(buffer, size, &unicode_tests ))
    {
        xmlbuf.ptr = buffer;
        xmlbuf.end = xmlbuf.ptr + size / sizeof(WCHAR);
        status = parse_manifest_buffer( acl, assembly, ai, &xmlbuf );
    }
    else if (unicode_tests & IS_TEXT_UNICODE_REVERSE_SIGNATURE)
    {
        const WCHAR *buf = buffer;
        WCHAR *new_buff;
        unsigned int i;

        if (!(new_buff = RtlAllocateHeap( RtlGetProcessHeap(), 0, size )))
            return STATUS_NO_MEMORY;
        for (i = 0; i < size / sizeof(WCHAR); i++)
            new_buff[i] = RtlUshortByteSwap( buf[i] );
        xmlbuf.ptr = new_buff;
        xmlbuf.end = xmlbuf.ptr + size / sizeof(WCHAR);
        status = parse_manifest_buffer( acl, assembly, ai, &xmlbuf );
        RtlFreeHeap( RtlGetProcessHeap(), 0, new_buff );
    }
    else
    {
        /* TODO: this doesn't handle arbitrary encodings */
        WCHAR *new_buff;
        ULONG sizeU;

        status = RtlMultiByteToUnicodeSize(&sizeU, buffer, size);
        if (!NT_SUCCESS(status))
        {
            DPRINT1("RtlMultiByteToUnicodeSize failed with %lx\n", status);
            return STATUS_SXS_CANT_GEN_ACTCTX;
        }

        new_buff = RtlAllocateHeap(RtlGetProcessHeap(), 0, sizeU);
        if (!new_buff)
            return STATUS_NO_MEMORY;

        status = RtlMultiByteToUnicodeN(new_buff, sizeU, &sizeU, buffer, size);
        if (!NT_SUCCESS(status))
        {
            DPRINT1("RtlMultiByteToUnicodeN failed with %lx\n", status);
            return STATUS_SXS_CANT_GEN_ACTCTX;
        }

        xmlbuf.ptr = new_buff;
        xmlbuf.end = xmlbuf.ptr + sizeU / sizeof(WCHAR);
        status = parse_manifest_buffer(acl, assembly, ai, &xmlbuf);
        RtlFreeHeap(RtlGetProcessHeap(), 0, new_buff);
    }
    return status;
}