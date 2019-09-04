#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nehd ;
typedef  scalar_t__ WORD ;
struct TYPE_6__ {int ne_restab; int ne_rsrctab; } ;
struct TYPE_5__ {int id; scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_4__ {int type_id; int count; } ;
typedef  TYPE_1__ NE_TYPEINFO ;
typedef  TYPE_2__ NE_NAMEINFO ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  TYPE_3__ IMAGE_OS2_HEADER ;
typedef  int /*<<< orphan*/  HFILE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IS_INTRESOURCE (int /*<<< orphan*/ ) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int LZRead (int /*<<< orphan*/ ,char*,int) ; 
 int LZSeek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL find_ne_resource( HFILE lzfd, LPCSTR typeid, LPCSTR resid,
                                DWORD *resLen, DWORD *resOff )
{
    IMAGE_OS2_HEADER nehd;
    NE_TYPEINFO *typeInfo;
    NE_NAMEINFO *nameInfo;
    DWORD nehdoffset;
    LPBYTE resTab;
    DWORD resTabSize;
    int count;

    /* Read in NE header */
    nehdoffset = LZSeek( lzfd, 0, SEEK_CUR );
    if ( sizeof(nehd) != LZRead( lzfd, (LPSTR)&nehd, sizeof(nehd) ) ) return FALSE;

    resTabSize = nehd.ne_restab - nehd.ne_rsrctab;
    if ( !resTabSize )
    {
        TRACE("No resources in NE dll\n" );
        return FALSE;
    }

    /* Read in resource table */
    resTab = heap_alloc( resTabSize );
    if ( !resTab ) return FALSE;

    LZSeek( lzfd, nehd.ne_rsrctab + nehdoffset, SEEK_SET );
    if ( resTabSize != LZRead( lzfd, (char*)resTab, resTabSize ) )
    {
        heap_free( resTab );
        return FALSE;
    }

    /* Find resource */
    typeInfo = (NE_TYPEINFO *)(resTab + 2);

    if (!IS_INTRESOURCE(typeid))  /* named type */
    {
        BYTE len = strlen( typeid );
        while (typeInfo->type_id)
        {
            if (!(typeInfo->type_id & 0x8000))
            {
                BYTE *p = resTab + typeInfo->type_id;
                if ((*p == len) && !strncasecmp( (char*)p+1, typeid, len )) goto found_type;
            }
            typeInfo = (NE_TYPEINFO *)((char *)(typeInfo + 1) +
                                       typeInfo->count * sizeof(NE_NAMEINFO));
        }
    }
    else  /* numeric type id */
    {
        WORD id = LOWORD(typeid) | 0x8000;
        while (typeInfo->type_id)
        {
            if (typeInfo->type_id == id) goto found_type;
            typeInfo = (NE_TYPEINFO *)((char *)(typeInfo + 1) +
                                       typeInfo->count * sizeof(NE_NAMEINFO));
        }
    }
    TRACE("No typeid entry found for %p\n", typeid );
    heap_free( resTab );
    return FALSE;

 found_type:
    nameInfo = (NE_NAMEINFO *)(typeInfo + 1);

    if (!IS_INTRESOURCE(resid))  /* named resource */
    {
        BYTE len = strlen( resid );
        for (count = typeInfo->count; count > 0; count--, nameInfo++)
        {
            BYTE *p = resTab + nameInfo->id;
            if (nameInfo->id & 0x8000) continue;
            if ((*p == len) && !strncasecmp( (char*)p+1, resid, len )) goto found_name;
        }
    }
    else  /* numeric resource id */
    {
        WORD id = LOWORD(resid) | 0x8000;
        for (count = typeInfo->count; count > 0; count--, nameInfo++)
            if (nameInfo->id == id) goto found_name;
    }
    TRACE("No resid entry found for %p\n", typeid );
    heap_free( resTab );
    return FALSE;

 found_name:
    /* Return resource data */
    if ( resLen ) *resLen = nameInfo->length << *(WORD *)resTab;
    if ( resOff ) *resOff = nameInfo->offset << *(WORD *)resTab;

    heap_free( resTab );
    return TRUE;
}