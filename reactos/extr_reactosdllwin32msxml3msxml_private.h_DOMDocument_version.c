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
typedef  int MSXML_VERSION ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  const CLSID_DOMDocument ; 
 int /*<<< orphan*/  const CLSID_DOMDocument30 ; 
 int /*<<< orphan*/  const CLSID_DOMDocument40 ; 
 int /*<<< orphan*/  const CLSID_DOMDocument60 ; 
#define  MSXML3 131 
#define  MSXML4 130 
#define  MSXML6 129 
#define  MSXML_DEFAULT 128 

__attribute__((used)) static inline const CLSID* DOMDocument_version(MSXML_VERSION v)
{
    switch (v)
    {
    default:
    case MSXML_DEFAULT: return &CLSID_DOMDocument;
    case MSXML3: return &CLSID_DOMDocument30;
    case MSXML4: return &CLSID_DOMDocument40;
    case MSXML6: return &CLSID_DOMDocument60;
    }
}