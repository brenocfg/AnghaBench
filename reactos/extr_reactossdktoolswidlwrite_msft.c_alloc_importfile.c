#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lcid2; } ;
struct TYPE_9__ {int** typelib_segment_data; TYPE_2__ typelib_header; TYPE_1__* typelib_segdir; } ;
typedef  TYPE_3__ msft_typelib_t ;
struct TYPE_10__ {int guid; int version; int /*<<< orphan*/  filename; int /*<<< orphan*/  lcid; } ;
struct TYPE_7__ {int length; } ;
typedef  TYPE_4__ MSFT_ImpFile ;

/* Variables and functions */
 size_t MSFT_SEG_IMPORTFILES ; 
 int ctl2_alloc_segment (TYPE_3__*,size_t,int,int /*<<< orphan*/ ) ; 
 int ctl2_encode_string (char const*,char**) ; 
 int /*<<< orphan*/  memcmp (char*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int alloc_importfile(
        msft_typelib_t *typelib,   /* [I] The type library to allocate in. */
        int guidoffset,            /* [I] The offset to the GUID for the imported library. */
        int major_version,         /* [I] The major version number of the imported library. */
        int minor_version,         /* [I] The minor version number of the imported library. */
        const char *filename)      /* [I] The filename of the imported library. */
{
    int length;
    int offset;
    MSFT_ImpFile *importfile;
    char *encoded_string;

    length = ctl2_encode_string(filename, &encoded_string);

    encoded_string[0] <<= 2;
    encoded_string[0] |= 1;

    for (offset = 0; offset < typelib->typelib_segdir[MSFT_SEG_IMPORTFILES].length;
	 offset += (((typelib->typelib_segment_data[MSFT_SEG_IMPORTFILES][offset + 0xd] << 8) |
	              typelib->typelib_segment_data[MSFT_SEG_IMPORTFILES][offset + 0xc]) >> 2) + 0xc) {
	if (!memcmp(encoded_string, typelib->typelib_segment_data[MSFT_SEG_IMPORTFILES] + offset + 0xc, length)) return offset;
    }

    offset = ctl2_alloc_segment(typelib, MSFT_SEG_IMPORTFILES, length + 0xc, 0);

    importfile = (MSFT_ImpFile *)&typelib->typelib_segment_data[MSFT_SEG_IMPORTFILES][offset];
    importfile->guid = guidoffset;
    importfile->lcid = typelib->typelib_header.lcid2;
    importfile->version = major_version | (minor_version << 16);
    memcpy(&importfile->filename, encoded_string, length);

    return offset;
}