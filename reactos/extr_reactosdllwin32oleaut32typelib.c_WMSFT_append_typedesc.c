#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  encoded ;
struct TYPE_9__ {char* data; int len; } ;
struct TYPE_10__ {TYPE_2__ typdesc_seg; } ;
typedef  TYPE_3__ WMSFT_TLBFile ;
typedef  int VARTYPE ;
struct TYPE_8__ {int hreftype; int /*<<< orphan*/  lpadesc; TYPE_4__* lptdesc; } ;
struct TYPE_11__ {int vt; TYPE_1__ u; } ;
typedef  TYPE_4__ TYPEDESC ;
typedef  int INT16 ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int VT_BYREF ; 
 int VT_CARRAY ; 
 int VT_EMPTY ; 
 int VT_I4 ; 
#define  VT_INT 130 
 int VT_PTR ; 
 int VT_SAFEARRAY ; 
 int VT_TYPEMASK ; 
 int VT_UI4 ; 
#define  VT_UINT 129 
 int VT_USERDEFINED ; 
#define  VT_VOID 128 
 int WMSFT_append_arraydesc (int /*<<< orphan*/ ,TYPE_3__*) ; 
 char* heap_alloc (int) ; 
 char* heap_realloc (char*,int) ; 
 int /*<<< orphan*/  memcmp (char*,int*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 

__attribute__((used)) static DWORD WMSFT_append_typedesc(TYPEDESC *desc, WMSFT_TLBFile *file, DWORD *out_mix, INT16 *out_size)
{
    DWORD junk;
    INT16 junk2;
    DWORD offs = 0;
    DWORD encoded[2];
    VARTYPE vt, subtype;
    char *data;

    if(!desc)
        return -1;

    if(!out_mix)
        out_mix = &junk;
    if(!out_size)
        out_size = &junk2;

    vt = desc->vt & VT_TYPEMASK;

    if(vt == VT_PTR || vt == VT_SAFEARRAY){
        DWORD mix;
        encoded[1] = WMSFT_append_typedesc(desc->u.lptdesc, file, &mix, out_size);
        encoded[0] = desc->vt | ((mix | VT_BYREF) << 16);
        *out_mix = 0x7FFF;
        *out_size += 2 * sizeof(DWORD);
    }else if(vt == VT_CARRAY){
        encoded[0] = desc->vt | (0x7FFE << 16);
        encoded[1] = WMSFT_append_arraydesc(desc->u.lpadesc, file);
        *out_mix = 0x7FFE;
    }else if(vt == VT_USERDEFINED){
        encoded[0] = desc->vt | (0x7FFF << 16);
        encoded[1] = desc->u.hreftype;
        *out_mix = 0x7FFF; /* FIXME: Should get TYPEKIND of the hreftype, e.g. TKIND_ENUM => VT_I4 */
    }else{
        TRACE("Mixing in-place, VT: 0x%x\n", desc->vt);

        switch(vt){
        case VT_INT:
            subtype = VT_I4;
            break;
        case VT_UINT:
            subtype = VT_UI4;
            break;
        case VT_VOID:
            subtype = VT_EMPTY;
            break;
        default:
            subtype = vt;
            break;
        }

        *out_mix = subtype;
        return 0x80000000 | (subtype << 16) | desc->vt;
    }

    data = file->typdesc_seg.data;
    while(offs < file->typdesc_seg.len){
        if(!memcmp(&data[offs], encoded, sizeof(encoded)))
            return offs;
        offs += sizeof(encoded);
    }

    file->typdesc_seg.len += sizeof(encoded);
    if(!file->typdesc_seg.data)
        data = file->typdesc_seg.data = heap_alloc(file->typdesc_seg.len);
    else
        data = file->typdesc_seg.data = heap_realloc(file->typdesc_seg.data, file->typdesc_seg.len);

    memcpy(&data[offs], encoded, sizeof(encoded));

    return offs;
}