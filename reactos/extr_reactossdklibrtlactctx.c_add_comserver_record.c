#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct guidsection_header {int count; } ;
struct guid_index {int data_offset; int data_len; int rosterindex; int /*<<< orphan*/  guid; } ;
struct entity_array {unsigned int num; struct entity* base; } ;
struct TYPE_3__ {scalar_t__ progid; scalar_t__ version; scalar_t__ name; scalar_t__ miscstatusdocprint; scalar_t__ miscstatusicon; scalar_t__ miscstatusthumbnail; scalar_t__ miscstatuscontent; scalar_t__ miscstatus; int /*<<< orphan*/  tlbid; int /*<<< orphan*/  model; int /*<<< orphan*/  clsid; } ;
struct TYPE_4__ {TYPE_1__ comclass; } ;
struct entity {scalar_t__ kind; TYPE_2__ u; } ;
struct dll_redirect {scalar_t__ name; } ;
struct comclassredirect_data {int size; int name_len; int name_offset; int progid_len; int progid_offset; int clrdata_len; int clrdata_offset; int /*<<< orphan*/  miscmask; scalar_t__ miscstatusdocprint; scalar_t__ miscstatusicon; scalar_t__ miscstatusthumbnail; scalar_t__ miscstatuscontent; scalar_t__ miscstatus; int /*<<< orphan*/  tlbid; int /*<<< orphan*/  clsid; int /*<<< orphan*/  clsid2; int /*<<< orphan*/  alias; int /*<<< orphan*/  model; scalar_t__* res1; scalar_t__ res; } ;
struct clrclass_data {int size; int* res; int module_len; int module_offset; int name_len; int name_offset; int version_len; int version_offset; scalar_t__* res2; } ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION ; 
 int /*<<< orphan*/  MiscStatus ; 
 int /*<<< orphan*/  MiscStatusContent ; 
 int /*<<< orphan*/  MiscStatusDocPrint ; 
 int /*<<< orphan*/  MiscStatusIcon ; 
 int /*<<< orphan*/  MiscStatusThumbnail ; 
 int /*<<< orphan*/  RtlGUIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ aligned_string_len (int) ; 
 int /*<<< orphan*/  generate_uuid (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mscoree2W ; 
 scalar_t__ mscoreeW ; 
 int strlenW (scalar_t__) ; 

__attribute__((used)) static void add_comserver_record(const struct guidsection_header *section, const struct entity_array *entities,
    const struct dll_redirect *dll, struct guid_index **index, ULONG *data_offset, ULONG *module_offset,
    ULONG *seed, ULONG rosterindex)
{
    unsigned int i;

    for (i = 0; i < entities->num; i++)
    {
        struct entity *entity = &entities->base[i];
        if (entity->kind == ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION)
        {
            ULONG module_len, progid_len, str_len = 0;
            struct comclassredirect_data *data;
            struct guid_index *alias_index;
            struct clrclass_data *clrdata;
            UNICODE_STRING str;
            WCHAR *ptrW;

            if (entity->u.comclass.progid)
                progid_len = strlenW(entity->u.comclass.progid)*sizeof(WCHAR);
            else
                progid_len = 0;

            module_len = dll ? strlenW(dll->name)*sizeof(WCHAR) : strlenW(mscoreeW)*sizeof(WCHAR);

            /* setup new index entry */
            RtlInitUnicodeString(&str, entity->u.comclass.clsid);
            RtlGUIDFromString(&str, &(*index)->guid);

            (*index)->data_offset = *data_offset;
            (*index)->data_len = sizeof(*data); /* additional length added later */
            (*index)->rosterindex = rosterindex;

            /* Setup new index entry for alias guid. Alias index records are placed after
               normal records, so normal guids are hit first on search. Note that class count
               is doubled. */
            alias_index = (*index) + section->count/2;
            generate_uuid(seed, &alias_index->guid);
            alias_index->data_offset = (*index)->data_offset;
            alias_index->data_len = 0;
            alias_index->rosterindex = (*index)->rosterindex;

            /* setup data */
            data = (struct comclassredirect_data*)((BYTE*)section + (*index)->data_offset);
            data->size = sizeof(*data);
            data->res = 0;
            data->res1[0] = 0;
            data->res1[1] = 0;
            data->model = entity->u.comclass.model;
            data->clsid = (*index)->guid;
            data->alias = alias_index->guid;
            data->clsid2 = data->clsid;
            if (entity->u.comclass.tlbid)
            {
                RtlInitUnicodeString(&str, entity->u.comclass.tlbid);
                RtlGUIDFromString(&str, &data->tlbid);
            }
            else
                memset(&data->tlbid, 0, sizeof(data->tlbid));
            data->name_len = module_len;
            data->name_offset = *module_offset;
            data->progid_len = progid_len;
            data->progid_offset = data->progid_len ? data->size : 0; /* in case of clrClass additional offset is added later */
            data->clrdata_len = 0; /* will be set later */
            data->clrdata_offset = entity->u.comclass.name ? sizeof(*data) : 0;
            data->miscstatus = entity->u.comclass.miscstatus;
            data->miscstatuscontent = entity->u.comclass.miscstatuscontent;
            data->miscstatusthumbnail = entity->u.comclass.miscstatusthumbnail;
            data->miscstatusicon = entity->u.comclass.miscstatusicon;
            data->miscstatusdocprint = entity->u.comclass.miscstatusdocprint;

            /* mask describes which misc* data is available */
            data->miscmask = 0;
            if (data->miscstatus)
                data->miscmask |= MiscStatus;
            if (data->miscstatuscontent)
                data->miscmask |= MiscStatusContent;
            if (data->miscstatusthumbnail)
                data->miscmask |= MiscStatusThumbnail;
            if (data->miscstatusicon)
                data->miscmask |= MiscStatusIcon;
            if (data->miscstatusdocprint)
                data->miscmask |= MiscStatusDocPrint;

            if (data->clrdata_offset)
            {
                clrdata = (struct clrclass_data*)((BYTE*)data + data->clrdata_offset);

                clrdata->size = sizeof(*clrdata);
                clrdata->res[0] = 0;
                clrdata->res[1] = 2; /* FIXME: unknown field */
                clrdata->module_len = strlenW(mscoreeW)*sizeof(WCHAR);
                clrdata->module_offset = *module_offset + data->name_len + sizeof(WCHAR);
                clrdata->name_len = strlenW(entity->u.comclass.name)*sizeof(WCHAR);
                clrdata->name_offset = clrdata->size;
                clrdata->version_len = entity->u.comclass.version ? strlenW(entity->u.comclass.version)*sizeof(WCHAR) : 0;
                clrdata->version_offset = clrdata->version_len ? clrdata->name_offset + clrdata->name_len + sizeof(WCHAR) : 0;
                clrdata->res2[0] = 0;
                clrdata->res2[1] = 0;

                data->clrdata_len = clrdata->size + clrdata->name_len + sizeof(WCHAR);

                /* module name */
                ptrW = (WCHAR*)((BYTE*)section + clrdata->module_offset);
                memcpy(ptrW, mscoree2W, clrdata->module_len);
                ptrW[clrdata->module_len/sizeof(WCHAR)] = 0;

                ptrW = (WCHAR*)((BYTE*)section + data->name_offset);
                memcpy(ptrW, mscoreeW, data->name_len);
                ptrW[data->name_len/sizeof(WCHAR)] = 0;

                /* class name */
                ptrW = (WCHAR*)((BYTE*)clrdata + clrdata->name_offset);
                memcpy(ptrW, entity->u.comclass.name, clrdata->name_len);
                ptrW[clrdata->name_len/sizeof(WCHAR)] = 0;

                /* runtime version, optional */
                if (clrdata->version_len)
                {
                    data->clrdata_len += clrdata->version_len + sizeof(WCHAR);

                    ptrW = (WCHAR*)((BYTE*)clrdata + clrdata->version_offset);
                    memcpy(ptrW, entity->u.comclass.version, clrdata->version_len);
                    ptrW[clrdata->version_len/sizeof(WCHAR)] = 0;
                }

                if (data->progid_len)
                    data->progid_offset += data->clrdata_len;
                (*index)->data_len += sizeof(*clrdata);
            }
            else
            {
                clrdata = NULL;

                /* module name */
                ptrW = (WCHAR*)((BYTE*)section + data->name_offset);
                memcpy(ptrW, dll->name, data->name_len);
                ptrW[data->name_len/sizeof(WCHAR)] = 0;
            }

            /* progid string */
            if (data->progid_len)
            {
                ptrW = (WCHAR*)((BYTE*)data + data->progid_offset);
                memcpy(ptrW, entity->u.comclass.progid, data->progid_len);
                ptrW[data->progid_len/sizeof(WCHAR)] = 0;
            }

            /* string block length */
            str_len = 0;
            if (clrdata)
            {
                str_len += clrdata->name_len + sizeof(WCHAR);
                if (clrdata->version_len)
                    str_len += clrdata->version_len + sizeof(WCHAR);
            }
            if (progid_len)
                str_len += progid_len + sizeof(WCHAR);

            (*index)->data_len += aligned_string_len(str_len);
            alias_index->data_len = (*index)->data_len;

            /* move to next data record */
            (*data_offset) += sizeof(*data) + aligned_string_len(str_len);
            (*module_offset) += module_len + sizeof(WCHAR);

            if (clrdata)
            {
                (*data_offset) += sizeof(*clrdata);
                (*module_offset) += clrdata->module_len + sizeof(WCHAR);
            }
            (*index) += 1;
        }
    }
}