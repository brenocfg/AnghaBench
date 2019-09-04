#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int DWORD ;

/* Variables and functions */
#define  CF_BITMAP 131 
#define  CF_DIB 130 
#define  CF_ENHMETAFILE 129 
#define  CF_METAFILEPICT 128 
 int TYMED_ENHMF ; 
 int TYMED_GDI ; 
 int TYMED_HGLOBAL ; 
 int TYMED_MFPICT ; 

__attribute__((used)) static inline DWORD tymed_from_cf( DWORD cf )
{
    switch( cf )
    {
    case CF_BITMAP:       return TYMED_GDI;
    case CF_METAFILEPICT: return TYMED_MFPICT;
    case CF_ENHMETAFILE:  return TYMED_ENHMF;
    case CF_DIB:
    default:              return TYMED_HGLOBAL;
    }
}