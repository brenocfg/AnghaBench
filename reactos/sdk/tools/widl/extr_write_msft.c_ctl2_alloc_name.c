#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nametablecount; char nametablechars; } ;
struct TYPE_9__ {int* typelib_namehash_segment; TYPE_1__ typelib_header; scalar_t__* typelib_segment_data; } ;
typedef  TYPE_2__ msft_typelib_t ;
struct TYPE_10__ {int hreftype; int next_hash; int /*<<< orphan*/  namelen; } ;
typedef  TYPE_3__ MSFT_NameIntro ;

/* Variables and functions */
 size_t MSFT_SEG_NAME ; 
 int ctl2_alloc_segment (TYPE_2__*,size_t,int,int /*<<< orphan*/ ) ; 
 int ctl2_encode_name (TYPE_2__*,char const*,char**) ; 
 int ctl2_find_name (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int ctl2_alloc_name(
	msft_typelib_t *typelib,  /* [I] The type library to allocate in. */
	const char *name)         /* [I] The name to store. */
{
    int length;
    int offset;
    MSFT_NameIntro *name_space;
    char *encoded_name;

    length = ctl2_encode_name(typelib, name, &encoded_name);

    offset = ctl2_find_name(typelib, encoded_name);
    if (offset != -1) return offset;

    offset = ctl2_alloc_segment(typelib, MSFT_SEG_NAME, length + 8, 0);

    name_space = (void *)(typelib->typelib_segment_data[MSFT_SEG_NAME] + offset);
    name_space->hreftype = -1;
    name_space->next_hash = -1;
    memcpy(&name_space->namelen, encoded_name, length);

    if (typelib->typelib_namehash_segment[encoded_name[2] & 0x7f] != -1)
	name_space->next_hash = typelib->typelib_namehash_segment[encoded_name[2] & 0x7f];

    typelib->typelib_namehash_segment[encoded_name[2] & 0x7f] = offset;

    typelib->typelib_header.nametablecount += 1;
    typelib->typelib_header.nametablechars += *encoded_name;

    return offset;
}