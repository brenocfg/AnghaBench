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
struct TYPE_5__ {int* Bytes; int ByteCount; } ;
struct TYPE_4__ {int ExtensionBlockCount; TYPE_2__* ExtensionBlocks; } ;
typedef  TYPE_1__ Extensions ;
typedef  TYPE_2__ ExtensionBlock ;

/* Variables and functions */
 int GIF_ERROR ; 
 int GIF_OK ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char const*,int) ; 
 int* ungif_realloc (int*,int) ; 

__attribute__((used)) static int
AppendExtensionBlock(Extensions *New,
                     int Len,
                     const unsigned char ExtData[])
{
    ExtensionBlock *ep;

    if (New->ExtensionBlocks == NULL)
        return (GIF_ERROR);

    ep = &New->ExtensionBlocks[New->ExtensionBlockCount - 1];

    ep->Bytes = ungif_realloc(ep->Bytes, ep->ByteCount + Len + 1);
    if (ep->Bytes == NULL)
        return (GIF_ERROR);

    ep->Bytes[ep->ByteCount] = Len;

    if (ExtData)
        memcpy(ep->Bytes + ep->ByteCount + 1, ExtData, Len);

    ep->ByteCount += Len + 1;

    return (GIF_OK);
}