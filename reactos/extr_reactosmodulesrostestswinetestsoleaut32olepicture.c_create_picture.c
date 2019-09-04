#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  desc ;
struct TYPE_10__ {int /*<<< orphan*/  hemf; } ;
struct TYPE_9__ {int xExt; int yExt; int /*<<< orphan*/  hmeta; } ;
struct TYPE_8__ {int /*<<< orphan*/  hicon; } ;
struct TYPE_7__ {int /*<<< orphan*/  hpal; int /*<<< orphan*/  hbitmap; } ;
struct TYPE_11__ {int cbSizeofstruct; short picType; TYPE_4__ emf; TYPE_3__ wmf; TYPE_2__ icon; TYPE_1__ bmp; } ;
typedef  TYPE_5__ PICTDESC ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  IPicture ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HPALETTE ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CloseEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateEnhMetaFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateMetaFileA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  IDI_APPLICATION ; 
 int /*<<< orphan*/  IID_IPicture ; 
 int /*<<< orphan*/  LoadIconA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OleCreatePictureIndirect (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
#define  PICTYPE_BITMAP 133 
#define  PICTYPE_ENHMETAFILE 132 
#define  PICTYPE_ICON 131 
#define  PICTYPE_METAFILE 130 
#define  PICTYPE_NONE 129 
#define  PICTYPE_UNINITIALIZED 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,short) ; 

__attribute__((used)) static HRESULT create_picture(short type, IPicture **pict)
{
    PICTDESC desc;

    desc.cbSizeofstruct = sizeof(desc);
    desc.picType = type;

    switch (type)
    {
    case PICTYPE_UNINITIALIZED:
        return OleCreatePictureIndirect(NULL, &IID_IPicture, TRUE, (void **)pict);

    case PICTYPE_NONE:
        break;

    case PICTYPE_BITMAP:
        desc.bmp.hbitmap = CreateBitmap(1, 1, 1, 1, NULL);
        desc.bmp.hpal = (HPALETTE)0xbeefdead;
        break;

    case PICTYPE_ICON:
        desc.icon.hicon = LoadIconA(NULL, (LPCSTR)IDI_APPLICATION);
        break;

    case PICTYPE_METAFILE:
    {
        HDC hdc = CreateMetaFileA(NULL);
        desc.wmf.hmeta = CloseMetaFile(hdc);
        desc.wmf.xExt = 1;
        desc.wmf.yExt = 1;
        break;
    }

    case PICTYPE_ENHMETAFILE:
    {
        HDC hdc = CreateEnhMetaFileA(0, NULL, NULL, NULL);
        desc.emf.hemf = CloseEnhMetaFile(hdc);
        break;
    }

    default:
        ok(0, "picture type %d is not supported\n", type);
        return E_NOTIMPL;
    }

    return OleCreatePictureIndirect(&desc, &IID_IPicture, TRUE, (void **)pict);
}