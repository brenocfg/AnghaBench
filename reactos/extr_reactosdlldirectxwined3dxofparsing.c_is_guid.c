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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {int rem_bytes; char* buffer; scalar_t__ value; } ;
typedef  TYPE_1__ parse_buffer ;
struct TYPE_5__ {int Data2; int Data3; int* Data4; int /*<<< orphan*/  Data1; } ;
typedef  TYPE_2__ GUID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSIDFMT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int sscanf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static BOOL is_guid(parse_buffer* buf)
{
  char tmp[50];
  DWORD pos = 1;
  GUID class_id;
  DWORD tab[10];
  int ret;

  if (buf->rem_bytes < 38 || *buf->buffer != '<')
    return FALSE;
  tmp[0] = '<';
  while (pos < sizeof(tmp) - 2 && *(buf->buffer+pos) != '>')
  {
    tmp[pos] = *(buf->buffer+pos);
    pos++;
  }
  tmp[pos++] = '>';
  tmp[pos] = 0;
  if (pos != 38 /* <+36+> */)
  {
    TRACE("Wrong guid %s (%d)\n", tmp, pos);
    return FALSE;
  }
  buf->buffer += pos;
  buf->rem_bytes -= pos;

  ret = sscanf(tmp, CLSIDFMT, &class_id.Data1, tab, tab+1, tab+2, tab+3, tab+4, tab+5, tab+6, tab+7, tab+8, tab+9);
  if (ret != 11)
  {
    TRACE("Wrong guid %s (%d)\n", tmp, pos);
    return FALSE;
  }
  TRACE("Found guid %s (%d)\n", tmp, pos);

  class_id.Data2 = tab[0];
  class_id.Data3 = tab[1];
  class_id.Data4[0] = tab[2];
  class_id.Data4[1] = tab[3];
  class_id.Data4[2] = tab[4];
  class_id.Data4[3] = tab[5];
  class_id.Data4[4] = tab[6];
  class_id.Data4[5] = tab[7];
  class_id.Data4[6] = tab[8];
  class_id.Data4[7] = tab[9];

  *(GUID*)buf->value = class_id;

  return TRUE;
}