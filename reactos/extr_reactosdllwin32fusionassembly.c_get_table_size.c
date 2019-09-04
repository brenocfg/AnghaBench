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
typedef  int /*<<< orphan*/  WORD ;
typedef  int ULONG ;
struct TYPE_5__ {TYPE_1__* tables; int /*<<< orphan*/  stringsz; int /*<<< orphan*/  blobsz; int /*<<< orphan*/  guidsz; } ;
struct TYPE_4__ {int /*<<< orphan*/  rows; } ;
typedef  int /*<<< orphan*/  TYPESPECTABLE ;
typedef  int /*<<< orphan*/  TYPEREFTABLE ;
typedef  int /*<<< orphan*/  TYPEDEFTABLE ;
typedef  int /*<<< orphan*/  STANDALONESIGTABLE ;
typedef  int /*<<< orphan*/  PROPERTYTABLE ;
typedef  int /*<<< orphan*/  PROPERTYMAPTABLE ;
typedef  int /*<<< orphan*/  PARAMTABLE ;
typedef  int /*<<< orphan*/  NESTEDCLASSTABLE ;
typedef  int /*<<< orphan*/  MODULETABLE ;
typedef  int /*<<< orphan*/  MODULEREFTABLE ;
typedef  int /*<<< orphan*/  METHODSEMANTICSTABLE ;
typedef  int /*<<< orphan*/  METHODIMPLTABLE ;
typedef  int /*<<< orphan*/  METHODDEFTABLE ;
typedef  int /*<<< orphan*/  MEMBERREFTABLE ;
typedef  int /*<<< orphan*/  MANIFESTRESTABLE ;
typedef  int /*<<< orphan*/  INTERFACEIMPLTABLE ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  IMPLMAPTABLE ;
typedef  int /*<<< orphan*/  FILETABLE ;
typedef  int /*<<< orphan*/  FIELDTABLE ;
typedef  int /*<<< orphan*/  FIELDRVATABLE ;
typedef  int /*<<< orphan*/  FIELDMARSHALTABLE ;
typedef  int /*<<< orphan*/  FIELDLAYOUTTABLE ;
typedef  int /*<<< orphan*/  EXPORTEDTYPETABLE ;
typedef  int /*<<< orphan*/  EVENTTABLE ;
typedef  int /*<<< orphan*/  EVENTMAPTABLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DECLSECURITYTABLE ;
typedef  int /*<<< orphan*/  CUSTOMATTRIBUTETABLE ;
typedef  int /*<<< orphan*/  CONSTANTTABLE ;
typedef  int /*<<< orphan*/  CLASSLAYOUTTABLE ;
typedef  int /*<<< orphan*/  ASSEMBLYTABLE ;
typedef  int /*<<< orphan*/  ASSEMBLYREFTABLE ;
typedef  int /*<<< orphan*/  ASSEMBLYREFPROCESSORTABLE ;
typedef  int /*<<< orphan*/  ASSEMBLYREFOSTABLE ;
typedef  int /*<<< orphan*/  ASSEMBLYPROCESSORTABLE ;
typedef  int /*<<< orphan*/  ASSEMBLYOSTABLE ;
typedef  TYPE_2__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TABLES_1BIT_ENCODE ; 
 int /*<<< orphan*/  MAX_TABLES_2BIT_ENCODE ; 
 int /*<<< orphan*/  MAX_TABLES_3BIT_ENCODE ; 
 int /*<<< orphan*/  MAX_TABLES_5BIT_ENCODE ; 
 int /*<<< orphan*/  MAX_TABLES_WORD ; 
 size_t TableFromToken (int const) ; 
 int TokenFromTable (int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  mdtAssembly 147 
#define  mdtAssemblyRef 146 
#define  mdtCustomAttribute 145 
#define  mdtEvent 144 
#define  mdtExportedType 143 
#define  mdtFieldDef 142 
#define  mdtFile 141 
#define  mdtInterfaceImpl 140 
#define  mdtManifestResource 139 
#define  mdtMemberRef 138 
#define  mdtMethodDef 137 
#define  mdtModule 136 
#define  mdtModuleRef 135 
#define  mdtParamDef 134 
#define  mdtPermission 133 
#define  mdtProperty 132 
#define  mdtSignature 131 
#define  mdtTypeDef 130 
#define  mdtTypeRef 129 
#define  mdtTypeSpec 128 

__attribute__((used)) static inline ULONG get_table_size(const ASSEMBLY *assembly, DWORD index)
{
    DWORD size;
    INT tables;

    switch (TokenFromTable(index))
    {
        case mdtModule:
        {
            size = sizeof(MODULETABLE) + (assembly->stringsz - sizeof(WORD)) +
                   2 * (assembly->guidsz - sizeof(WORD));
            break;
        }
        case mdtTypeRef:
        {
            size = sizeof(TYPEREFTABLE) + 2 * (assembly->stringsz - sizeof(WORD));

            /* ResolutionScope:ResolutionScope */
            tables = max(assembly->tables[TableFromToken(mdtModule)].rows,
                         assembly->tables[TableFromToken(mdtModuleRef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtAssemblyRef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtTypeRef)].rows);
            size += (tables > MAX_TABLES_2BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case mdtTypeDef:
        {
            size = sizeof(TYPEDEFTABLE) + 2 * (assembly->stringsz - sizeof(WORD));

            /* Extends:TypeDefOrRef */
            tables = max(assembly->tables[TableFromToken(mdtTypeDef)].rows,
                         assembly->tables[TableFromToken(mdtTypeRef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtTypeSpec)].rows);
            size += (tables > MAX_TABLES_2BIT_ENCODE) ? sizeof(WORD) : 0;

            size += (assembly->tables[TableFromToken(mdtFieldDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            size += (assembly->tables[TableFromToken(mdtMethodDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case mdtFieldDef:
        {
            size = sizeof(FIELDTABLE) + (assembly->stringsz - sizeof(WORD)) +
                   (assembly->blobsz - sizeof(WORD));
            break;
        }
        case mdtMethodDef:
        {
            size = sizeof(METHODDEFTABLE) + (assembly->stringsz - sizeof(WORD)) +
                   (assembly->blobsz - sizeof(WORD));

            size += (assembly->tables[TableFromToken(mdtParamDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case mdtParamDef:
        {
            size = sizeof(PARAMTABLE) + (assembly->stringsz - sizeof(WORD));
            break;
        }
        case mdtInterfaceImpl:
        {
            size = sizeof(INTERFACEIMPLTABLE);

            /* Interface:TypeDefOrRef */
            tables = max(assembly->tables[TableFromToken(mdtTypeDef)].rows,
                         assembly->tables[TableFromToken(mdtTypeRef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtTypeSpec)].rows);
            size += (tables > MAX_TABLES_2BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case mdtMemberRef:
        {
            size = sizeof(MEMBERREFTABLE) + (assembly->stringsz - sizeof(WORD)) +
                   (assembly->blobsz - sizeof(WORD));

            /* Class:MemberRefParent */
            tables = max(assembly->tables[TableFromToken(mdtTypeRef)].rows,
                         assembly->tables[TableFromToken(mdtModuleRef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtMethodDef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtTypeSpec)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtTypeDef)].rows);
            size += (tables > MAX_TABLES_3BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case 0x0B000000: /* FIXME */
        {
            size = sizeof(CONSTANTTABLE) + (assembly->blobsz - sizeof(WORD));

            /* Parent:HasConstant */
            tables = max(assembly->tables[TableFromToken(mdtParamDef)].rows,
                         assembly->tables[TableFromToken(mdtFieldDef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtProperty)].rows);
            size += (tables > MAX_TABLES_2BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case mdtCustomAttribute:
        {
            size = sizeof(CUSTOMATTRIBUTETABLE) + (assembly->blobsz - sizeof(WORD));

            /* Parent:HasCustomAttribute */
            tables = max(assembly->tables[TableFromToken(mdtMethodDef)].rows,
                         assembly->tables[TableFromToken(mdtFieldDef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtTypeRef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtTypeDef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtParamDef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtInterfaceImpl)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtMemberRef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtPermission)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtProperty)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtEvent)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtSignature)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtModuleRef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtTypeSpec)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtAssembly)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtFile)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtExportedType)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtManifestResource)].rows);
            size += (tables > MAX_TABLES_5BIT_ENCODE) ? sizeof(WORD) : 0;

            /* Type:CustomAttributeType */
            tables = max(assembly->tables[TableFromToken(mdtMethodDef)].rows,
                         assembly->tables[TableFromToken(mdtMemberRef)].rows);
            size += (tables > MAX_TABLES_3BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case 0x0D000000: /* FIXME */
        {
            size = sizeof(FIELDMARSHALTABLE) + (assembly->blobsz - sizeof(WORD));

            /* Parent:HasFieldMarshal */
            tables = max(assembly->tables[TableFromToken(mdtFieldDef)].rows,
                         assembly->tables[TableFromToken(mdtParamDef)].rows);
            size += (tables > MAX_TABLES_1BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case mdtPermission:
        {
            size = sizeof(DECLSECURITYTABLE) + (assembly->blobsz - sizeof(WORD));

            /* Parent:HasDeclSecurity */
            tables = max(assembly->tables[TableFromToken(mdtTypeDef)].rows,
                         assembly->tables[TableFromToken(mdtMethodDef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtAssembly)].rows);
            size += (tables > MAX_TABLES_2BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case 0x0F000000: /* FIXME */
        {
            size = sizeof(CLASSLAYOUTTABLE);
            size += (assembly->tables[TableFromToken(mdtTypeDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case 0x10000000: /* FIXME */
        {
            size = sizeof(FIELDLAYOUTTABLE);
            size += (assembly->tables[TableFromToken(mdtFieldDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case mdtSignature:
        {
            size = sizeof(STANDALONESIGTABLE) + (assembly->blobsz - sizeof(WORD));
            break;
        }
        case 0x12000000: /* FIXME */
        {
            size = sizeof(EVENTMAPTABLE);
            size += (assembly->tables[TableFromToken(mdtTypeDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            size += (assembly->tables[TableFromToken(mdtEvent)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case mdtEvent:
        {
            size = sizeof(EVENTTABLE) + (assembly->stringsz - sizeof(WORD));

            /* EventType:TypeDefOrRef */
            tables = max(assembly->tables[TableFromToken(mdtTypeDef)].rows,
                         assembly->tables[TableFromToken(mdtTypeRef)].rows);
            tables = max(tables, assembly->tables[TableFromToken(mdtTypeSpec)].rows);
            size += (tables > MAX_TABLES_2BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case 0x15000000:/* FIXME */
        {
            size = sizeof(PROPERTYMAPTABLE);
            size += (assembly->tables[TableFromToken(mdtTypeDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            size += (assembly->tables[TableFromToken(mdtProperty)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case mdtProperty:
        {
            size = sizeof(PROPERTYTABLE) + (assembly->stringsz - sizeof(WORD)) +
                   (assembly->blobsz - sizeof(WORD));
            break;
        }
        case 0x18000000: /* FIXME */
        {
            size = sizeof(METHODSEMANTICSTABLE);

            /* Association:HasSemantics */
            tables = max(assembly->tables[TableFromToken(mdtEvent)].rows,
                         assembly->tables[TableFromToken(mdtProperty)].rows);
            size += (tables > MAX_TABLES_1BIT_ENCODE) ? sizeof(WORD) : 0;

            size += (assembly->tables[TableFromToken(mdtMethodDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case 0x19000000: /* FIXME */
        {
            size = sizeof(METHODIMPLTABLE);

            /* MethodBody:MethodDefOrRef, MethodDeclaration:MethodDefOrRef */
            tables = max(assembly->tables[TableFromToken(mdtMethodDef)].rows,
                         assembly->tables[TableFromToken(mdtMemberRef)].rows);
            size += (tables > MAX_TABLES_1BIT_ENCODE) ? 2 * sizeof(WORD) : 0;

            size += (assembly->tables[TableFromToken(mdtTypeDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case mdtModuleRef:
        {
            size = sizeof(MODULEREFTABLE) + (assembly->stringsz - sizeof(WORD));
            break;
        }
        case mdtTypeSpec:
        {
            size = sizeof(TYPESPECTABLE) + (assembly->blobsz - sizeof(WORD));
            break;
        }
        case 0x1C000000: /* FIXME */
        {
            size = sizeof(IMPLMAPTABLE) + (assembly->stringsz - sizeof(WORD));

            /* MemberForwarded:MemberForwarded */
            tables = max(assembly->tables[TableFromToken(mdtFieldDef)].rows,
                         assembly->tables[TableFromToken(mdtMethodDef)].rows);
            size += (tables > MAX_TABLES_1BIT_ENCODE) ? sizeof(WORD) : 0;

            size += (assembly->tables[TableFromToken(mdtModuleRef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case 0x1D000000: /* FIXME */
        {
            size = sizeof(FIELDRVATABLE);
            size += (assembly->tables[TableFromToken(mdtFieldDef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case mdtAssembly:
        {
            size = sizeof(ASSEMBLYTABLE) + 2 * (assembly->stringsz - sizeof(WORD)) +
                   (assembly->blobsz - sizeof(WORD));
            break;
        }
        case 0x20000001: /* FIXME */
        {
            size = sizeof(ASSEMBLYPROCESSORTABLE);
            break;
        }
        case 0x22000000: /* FIXME */
        {
            size = sizeof(ASSEMBLYOSTABLE);
            break;
        }
        case mdtAssemblyRef:
        {
            size = sizeof(ASSEMBLYREFTABLE) + 2 * (assembly->stringsz - sizeof(WORD)) +
                   2 * (assembly->blobsz - sizeof(WORD));
            break;
        }
        case 0x24000000: /* FIXME */
        {
            size = sizeof(ASSEMBLYREFPROCESSORTABLE);
            size += (assembly->tables[TableFromToken(mdtAssemblyRef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case 0x25000000: /* FIXME */
        {
            size = sizeof(ASSEMBLYREFOSTABLE);
            size += (assembly->tables[TableFromToken(mdtAssemblyRef)].rows >
                     MAX_TABLES_WORD) ? sizeof(WORD) : 0;
            break;
        }
        case mdtFile:
        {
            size = sizeof(FILETABLE) + (assembly->stringsz - sizeof(WORD)) +
                   (assembly->blobsz - sizeof(WORD));
            break;
        }
        case mdtExportedType:
        {
            size = sizeof(EXPORTEDTYPETABLE) + 2 * (assembly->stringsz - sizeof(WORD));

            /* Implementation:Implementation */
            tables = max(assembly->tables[TableFromToken(mdtFile)].rows,
                         assembly->tables[TableFromToken(mdtMethodDef)].rows);
            size += (tables > MAX_TABLES_2BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case mdtManifestResource:
        {
            size = sizeof(MANIFESTRESTABLE) + (assembly->stringsz - sizeof(WORD));

            /* Implementation:Implementation */
            tables = max(assembly->tables[TableFromToken(mdtFile)].rows,
                         assembly->tables[TableFromToken(mdtAssemblyRef)].rows);
            size += (tables > MAX_TABLES_2BIT_ENCODE) ? sizeof(WORD) : 0;
            break;
        }
        case 0x29000000: /* FIXME */
        {
            size = sizeof(NESTEDCLASSTABLE);
            size += (assembly->tables[TableFromToken(mdtTypeDef)].rows >
                     MAX_TABLES_WORD) ? 2 * sizeof(WORD) : 0;
            break;
        }
        default:
            return 0;
    }

    return size;
}