#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int USHORT ;
typedef  scalar_t__ ULONG ;
typedef  int UCHAR ;
struct TYPE_10__ {int* bpTarget; int* Codes; int dwFlags; int bAsciiLen; int bInstrLen; scalar_t__ szDisasm; } ;
struct TYPE_9__ {int flags; int name; int dest; scalar_t__ args; } ;
typedef  TYPE_1__ TOpcodeData ;
typedef  TYPE_2__ TDisassembler ;
typedef  unsigned int LPSTR ;

/* Variables and functions */
 TYPE_1__** Coproc1 ; 
 TYPE_1__** Coproc2 ; 
 int DIS_ADDRESS32 ; 
 int DIS_COPROC ; 
 int DIS_DATA32 ; 
 size_t DIS_GETADDRSIZE (int) ; 
 size_t DIS_GETDATASIZE (int) ; 
 size_t DIS_GETNAMEFLAG (int) ; 
 size_t DIS_GETREPENUM (int) ; 
 int DIS_ILLEGALOP ; 
 int DIS_MODRM ; 
 int DIS_REP ; 
 int DIS_REPNE ; 
 int DIS_SPECIAL ; 
 TYPE_1__** Groups ; 
 int NEXTUCHAR ; 
 scalar_t__ NEXTULONG ; 
 unsigned int NEXTUSHORT ; 
 TYPE_1__* Op1 ; 
 TYPE_1__* Op2 ; 
 scalar_t__ PICE_sprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  ScanExportsByAddress (unsigned int*,unsigned int) ; 
#define  _1 227 
#define  _2BESC 226 
#define  _3 225 
#define  _ADSIZ 224 
#define  _AH 223 
#define  _AL 222 
#define  _AX 221 
#define  _Ap 220 
#define  _BH 219 
#define  _BL 218 
#define  _CH 217 
#define  _CL 216 
#define  _CS 215 
#define  _Cd 214 
#define  _DH 213 
#define  _DL 212 
#define  _DS 211 
#define  _DX 210 
#define  _Dd 209 
#define  _ES 208 
#define  _Eb 207 
#define  _Ep 206 
#define  _EscD8 205 
#define  _EscD9 204 
#define  _EscDA 203 
#define  _EscDB 202 
#define  _EscDC 201 
#define  _EscDD 200 
#define  _EscDE 199 
#define  _EscDF 198 
#define  _Ev 197 
#define  _Ew 196 
#define  _FS 195 
#define  _GRP1a 194 
#define  _GRP1b 193 
#define  _GRP1c 192 
#define  _GRP2a 191 
#define  _GRP2b 190 
#define  _GRP2c 189 
#define  _GRP2d 188 
#define  _GRP2e 187 
#define  _GRP2f 186 
#define  _GRP3a 185 
#define  _GRP3b 184 
#define  _GRP4 183 
#define  _GRP5 182 
#define  _GRP6 181 
#define  _GRP7 180 
#define  _GRP8 179 
#define  _GRP9 178 
#define  _GS 177 
#define  _Gb 176 
#define  _Gv 175 
#define  _Ib 174 
#define  _Iv 173 
#define  _Iw 172 
#define  _Jb 171 
#define  _Jv 170 
#define  _M 169 
#define  _Ma 168 
#define  _Mp 167 
#define  _Mq 166 
#define  _Ms 165 
#define  _NDEF 164 
#define  _O 163 
#define  _OPSIZ 162 
#define  _REP 161 
#define  _REPNE 160 
#define  _Rd 159 
#define  _Rw 158 
#define  _SS 157 
#define  _ST 156 
#define  _ST0 155 
#define  _ST1 154 
#define  _ST2 153 
#define  _ST3 152 
#define  _ST4 151 
#define  _ST5 150 
#define  _ST6 149 
#define  _ST7 148 
#define  _S_CS 147 
#define  _S_DS 146 
#define  _S_ES 145 
#define  _S_FS 144 
#define  _S_GS 143 
#define  _S_SS 142 
#define  _Sw 141 
#define  _Td 140 
#define  _Xb 139 
#define  _Xv 138 
#define  _Yb 137 
#define  _Yv 136 
#define  _eAX 135 
#define  _eBP 134 
#define  _eBX 133 
#define  _eCX 132 
#define  _eDI 131 
#define  _eDX 130 
#define  _eSI 129 
#define  _eSP 128 
 unsigned int** sAdr1 ; 
 char* sBytePtr ; 
 unsigned int* sControl ; 
 unsigned int* sCoprocNames ; 
 unsigned int* sDebug ; 
 char* sDwordPtr ; 
 char* sFwordPtr ; 
 unsigned int** sGenReg16_32 ; 
 int /*<<< orphan*/ * sNames ; 
 char* sQwordPtr ; 
 unsigned int*** sRegs1 ; 
 unsigned int* sRegs2 ; 
 int /*<<< orphan*/ * sRep ; 
 unsigned int* sST ; 
 int /*<<< orphan*/ * sScale ; 
 unsigned int* sSeg ; 
 unsigned int* sSegOverride ; 
 int /*<<< orphan*/ * sSegOverrideDefaultDS ; 
 int /*<<< orphan*/ * sSegOverrideDefaultES ; 
 unsigned int* sTest ; 
 char* sWordPtr ; 
 int /*<<< orphan*/ * sXptr ; 
 int /*<<< orphan*/ * sYptr ; 

UCHAR Disassembler( TDisassembler *pDis )
{
    TOpcodeData *p;             // Pointer to a current instruction record
    UCHAR   *bpTarget;           // Pointer to the target code to be disassembled
    UCHAR   *bpCode;             // Pointer to code UCHARs
    ULONG   arg;                // Argument counter
    char   *sPtr;               // Message selection pointer
    int     nPos;               // Printing position in the output string
    UCHAR   *pArg;               // Pointer to record where instruction arguments are
    ULONG   dwULONG;            // Temporary ULONG storage
    USHORT    wUSHORT;              // Temporary USHORT storage
    UCHAR    bUCHAR;              // Temporary UCHAR storage
    UCHAR    bInstrLen;          // Current instruction length in UCHARs
    UCHAR    bOpcode;            // Current opcode that is being disassembled
    UCHAR    bSegOverride;       // 0 default segment. >0, segment index
    UCHAR    bMod=0;             // Mod field of the instruction
    UCHAR    bReg=0;             // Register field of the instruction
    UCHAR    bRm=0;                // R/M field of the instruction
    UCHAR    bW;                 // Width bit for the register selection

    UCHAR    bSib;               // S-I-B UCHAR for the instruction
    UCHAR    bSs;                // SS field of the s-i-b UCHAR
    UCHAR    bIndex;             // Index field of the s-i-b UCHAR
    UCHAR    bBase;              // Base field of the s-i-b UCHAR
    LPSTR    pSymbolName;        // used to symbolic name of value

    bInstrLen = 0;              // Reset instruction length to zero
    bSegOverride = 0;           // Set default segment (no override)
    nPos = 0;                   // Reset printing position
    sPtr = NULL;                // Points to no message by default
    bpTarget = pDis->bpTarget;  // Set internal pointer to a target address
    bpCode = pDis->Codes;       // Set internal pointer to code UCHARs

    do
    {
        bOpcode = NEXTUCHAR;     // Get the first opcode UCHAR from the target address
        p = &Op1[bOpcode];      // Get the address of the instruction record

        if( p->flags & DIS_SPECIAL )
        {
            // Opcode is one of the special ones, so do what needs to be done there

            switch( p->name )
            {
                case _EscD8:
                case _EscD9:
                case _EscDA:
                case _EscDB:
                case _EscDC:
                case _EscDD:
                case _EscDE:
                case _EscDF:        // Coprocessor escape: UCHARs D8 - DF
                    bOpcode = NEXTUCHAR;             // Get the modRM UCHAR of the instruction

                    if( bOpcode < 0xC0 )
                    {
                        // Opcodes 00-BF use Coproc1 table

                        bReg = (bOpcode >> 3) & 7;
                        p = &Coproc1[ p->name - _EscD8 ][ bReg ];

                        goto StartInstructionParseMODRM;
                    }
                    // Opcodes C0-FF use Coproc2 table

                    p = &Coproc2[ p->name - _EscD8 ][ bOpcode - 0xC0 ];

                goto StartInstructionNoMODRM;

                case _S_ES:         // Segment override
                case _S_CS:
                case _S_SS:
                case _S_DS:
                case _S_FS:
                case _S_GS:
                    bSegOverride = p->name - _S_ES + 1;
                continue;

                case _OPSIZ:        // Operand size override - toggle
                    pDis->dwFlags ^= DIS_DATA32;
                continue;

                case _ADSIZ:        // Address size override - toggle
                    pDis->dwFlags ^= DIS_ADDRESS32;
                continue;

                case _REPNE:        // REPNE/REPNZ prefix
                    pDis->dwFlags |= DIS_REPNE;
                continue;

                case _REP:          // REP/REPE/REPZ prefix
                    pDis->dwFlags |= DIS_REP;
                continue;

                case _2BESC:        // 2 UCHAR escape code 0x0F
                    bOpcode = NEXTUCHAR;             // Get the second UCHAR of the instruction
                    p = &Op2[bOpcode];              // Get the address of the instruction record

                    if( !(p->flags & DIS_SPECIAL) ) goto StartInstruction;
                    if( p->name < _GRP6 ) goto IllegalOpcode;

                case _GRP1a:        // Additional groups of instructions
                case _GRP1b:
                case _GRP1c:
                case _GRP2a:
                case _GRP2b:
                case _GRP2c:
                case _GRP2d:
                case _GRP2e:
                case _GRP2f:
                case _GRP3a:
                case _GRP3b:
                case _GRP4:
                case _GRP5:
                case _GRP6:
                case _GRP7:
                case _GRP8:
                case _GRP9:

                    bOpcode = NEXTUCHAR;             // Get the Mod R/M UCHAR whose...
                                                    // bits 3,4,5 select instruction

                    bReg = (bOpcode >> 3) & 7;
                    p = &Groups[p->name - _GRP1a][ bReg ];

                    if( !(p->flags & DIS_SPECIAL) ) goto StartInstructionParseMODRM;

                case _NDEF :        // Not defined or illegal opcode
                    goto IllegalOpcode;

                default :;          // Should not happen
            }
        }
        else
            goto StartInstruction;
    }
    while( bInstrLen < 15 );

IllegalOpcode:

    nPos += PICE_sprintf( pDis->szDisasm+nPos, "invalid");
    pDis->dwFlags |= DIS_ILLEGALOP;

    goto DisEnd;

StartInstruction:

    // If this instruction needs additional Mod R/M UCHAR, fetch it

    if( p->flags & DIS_MODRM )
    {
        // Get the next UCHAR (modR/M bit field)
        bOpcode = NEXTUCHAR;

        bReg = (bOpcode >> 3) & 7;

StartInstructionParseMODRM:

        // Parse that UCHAR and get mod, reg and rm fields
        bMod = bOpcode >> 6;
        bRm  = bOpcode & 7;
    }

StartInstructionNoMODRM:

    // Print the possible repeat prefix followed by the instruction

    if( p->flags & DIS_COPROC )
        nPos += PICE_sprintf( pDis->szDisasm+nPos, "%-6s ", sCoprocNames[ p->name ]);
    else
        nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s%-6s ",
                sRep[DIS_GETREPENUM(pDis->dwFlags)],
                sNames[ p->name + (DIS_GETNAMEFLAG(p->flags) & DIS_GETDATASIZE(pDis->dwFlags)) ] );

    // Do instruction argument processing, up to 3 times

    pArg = &p->dest;

    for( arg=p->args; arg!=0; arg--, pArg++, arg? nPos += PICE_sprintf( pDis->szDisasm+nPos,", ") : 0 )
    {
        switch( *pArg )
        {
             case _Eb :                                         // modR/M used - bW = 0
                bW = 0;
                goto _E;

             case _Ev :                                         // modR/M used - bW = 1
                bW = 1;
                goto _E;

             case _Ew :                                         // always USHORT size
                pDis->dwFlags &= ~DIS_DATA32;
                bW = 1;
                goto _E;

             case _Ms :                                         // fword ptr (sgdt,sidt,lgdt,lidt)
                sPtr = sFwordPtr;
                goto _E1;

             case _Mq :                                         // qword ptr (cmpxchg8b)
                sPtr = sQwordPtr;
                goto _E1;

             case _Mp :                                         // 32 or 48 bit pointer (les,lds,lfs,lss,lgs)
             case _Ep :                                         // Always a memory pointer (call, jmp)
                if( pDis->dwFlags & DIS_DATA32 )
                    sPtr = sFwordPtr;
                else
                    sPtr = sDwordPtr;
                goto _E1;

             _E:
                 // Do registers first so that the rest may be done together
                 if( bMod == 3 )
                 {
                      // Registers depending on the w field and data size
                      nPos+=PICE_sprintf(pDis->szDisasm+nPos, "%s", sRegs1[DIS_GETDATASIZE(pDis->dwFlags)][bW][bRm] );

                      break;
                 }

                 if( bW==0 )
                     sPtr = sBytePtr;
                 else
                     if( pDis->dwFlags & DIS_DATA32 )
                         sPtr = sDwordPtr;
                     else
                         sPtr = sWordPtr;

             case _M  :                                         // Pure memory pointer (lea,invlpg,floats)
                if( bMod == 3 ) goto IllegalOpcode;

             _E1:

                 if( sPtr )
                     nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sPtr );

             case _Ma :                                         // Used by bound instruction, skip the pointer info

                 // Print the segment if it is overriden
                 //
                 nPos += PICE_sprintf( pDis->szDisasm+nPos,"%s", sSegOverride[ bSegOverride ] );

                 //
                 // Special case when sib UCHAR is present in 32 address encoding
                 //
                 if( (bRm==4) && (pDis->dwFlags & DIS_ADDRESS32) )
                 {
                      //
                      // Get the s-i-b UCHAR and parse it
                      //
                      bSib = NEXTUCHAR;

                      bSs = bSib >> 6;
                      bIndex = (bSib >> 3) & 7;
                      bBase = bSib & 7;

                      // Special case for base=5 && mod==0 -> fetch 32 bit offset
                      if( (bBase==5) && (bMod==0) )
                      {
                          dwULONG = NEXTULONG;
                          if(ScanExportsByAddress(&pSymbolName,dwULONG))
                          {
                              nPos += PICE_sprintf( pDis->szDisasm+nPos,"[%s", pSymbolName );
                          }
                          else
                          {
                              nPos += PICE_sprintf( pDis->szDisasm+nPos,"[%08X", (unsigned int) dwULONG );
                          }
                      }
                      else
                          nPos += PICE_sprintf( pDis->szDisasm+nPos,"[%s", sGenReg16_32[ 1 ][ bBase ] );

                      // Scaled index, no index if bIndex is 4
                      if( bIndex != 4 )
                          nPos += PICE_sprintf( pDis->szDisasm+nPos,"+%s%s", sScale[ bSs ], sGenReg16_32[ 1 ][ bIndex ] );
                      else
                          if(bSs != 0)
                              nPos += PICE_sprintf( pDis->szDisasm+nPos,"<INVALID MODE>" );

                      // Offset 8 bit or 32 bit
                      if( bMod == 1 )
                      {
                          bUCHAR = NEXTUCHAR;
                          if( (signed char)bUCHAR < 0 )
                                 nPos += PICE_sprintf( pDis->szDisasm+nPos,"-%02X", 0-(signed char)bUCHAR );
                          else
                                 nPos += PICE_sprintf( pDis->szDisasm+nPos,"+%02X", bUCHAR );
                      }

                      if( bMod == 2 )
                      {
                          dwULONG = NEXTULONG;
                          nPos += PICE_sprintf( pDis->szDisasm+nPos,"+%08X", (unsigned int) dwULONG );
                      }

                      // Wrap up the instruction
                      nPos += PICE_sprintf( pDis->szDisasm+nPos,"]" );
                      break;
                 }

                 //
                 // 16 or 32 address bit cases with mod zero, one or two
                 //
                 // Special cases when r/m is 5 and mod is 0, immediate d16 or d32
                 if( bMod==0 && ((bRm==6 && !(pDis->dwFlags & DIS_ADDRESS32)) || (bRm==5 && (pDis->dwFlags & DIS_ADDRESS32))) )
                 {
                      if( pDis->dwFlags & DIS_ADDRESS32 )
                      {
                          dwULONG = NEXTULONG;
                          if(ScanExportsByAddress(&pSymbolName,dwULONG))
                              nPos += PICE_sprintf( pDis->szDisasm+nPos,"[%s]", pSymbolName );
                          else
                              nPos += PICE_sprintf( pDis->szDisasm+nPos,"[%08X]", (unsigned int) dwULONG );
                      }
                      else
                      {
                          wUSHORT = NEXTUSHORT;
                          nPos += PICE_sprintf( pDis->szDisasm+nPos,"[%04X]", wUSHORT );
                      }

                      break;
                 }

                 // Print the start of the line
                 nPos += PICE_sprintf( pDis->szDisasm+nPos,"[%s", sAdr1[DIS_GETADDRSIZE(pDis->dwFlags)][ bRm ] );

                 // Offset (8 or 16) or (8 or 32) bit - 16, 32 bits are unsigned
                 if( bMod==1 )
                 {
                      bUCHAR = NEXTUCHAR;
                      if( (signed char)bUCHAR < 0 )
                             nPos += PICE_sprintf( pDis->szDisasm+nPos,"-%02X", 0-(signed char)bUCHAR );
                      else
                             nPos += PICE_sprintf( pDis->szDisasm+nPos,"+%02X", bUCHAR );
                 }

                 if( bMod==2 )
                 {
                      if( pDis->dwFlags & DIS_ADDRESS32 )
                      {
                          dwULONG = NEXTULONG;
                          nPos += PICE_sprintf( pDis->szDisasm+nPos,"+%08X", (unsigned int) dwULONG );
                      }
                      else
                      {
                          wUSHORT = NEXTUSHORT;
                          nPos += PICE_sprintf( pDis->szDisasm+nPos,"+%04X", wUSHORT );
                      }
                 }

                 // Wrap up the instruction
                 nPos += PICE_sprintf( pDis->szDisasm+nPos,"]" );

             break;

             case _Gb :                                         // general, UCHAR register
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sRegs1[0][0][ bReg ] );
             break;

             case _Gv :                                         // general, (d)USHORT register
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sGenReg16_32[DIS_GETDATASIZE(pDis->dwFlags)][ bReg ] );
             break;

             case _Yb :                                         // ES:(E)DI pointer
             case _Yv :
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s%s", sSegOverrideDefaultES[ bSegOverride ], sYptr[DIS_GETADDRSIZE(pDis->dwFlags)] );
             break;

             case _Xb :                                         // DS:(E)SI pointer
             case _Xv :
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s%s", sSegOverrideDefaultDS[ bSegOverride ], sXptr[DIS_GETADDRSIZE(pDis->dwFlags)] );
             break;

             case _Rd :                                         // general register double USHORT
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sGenReg16_32[ 1 ][ bRm ] );
             break;

             case _Rw :                                         // register USHORT
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sGenReg16_32[ 0 ][ bMod ] );
             break;

             case _Sw :                                         // segment register
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sSeg[ bReg ] );
             break;

             case _Cd :                                         // control register
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sControl[ bReg ] );
             break;

             case _Dd :                                         // debug register
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sDebug[ bReg ] );
             break;

             case _Td :                                         // test register
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sTest[ bReg ] );
             break;


             case _Jb :                                         // immediate UCHAR, relative offset
                 bUCHAR = NEXTUCHAR;
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "short %08X", (unsigned int)(pDis->bpTarget + (signed char)bUCHAR + bInstrLen) );
             break;

             case _Jv :                                         // immediate USHORT or ULONG, relative offset
                 if( pDis->dwFlags & DIS_DATA32 )
                 {
                      dwULONG = NEXTULONG;
                      if(ScanExportsByAddress(&pSymbolName,(unsigned int)(pDis->bpTarget + (signed long)dwULONG + bInstrLen)))
                        nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", pSymbolName );
                      else
                        nPos += PICE_sprintf( pDis->szDisasm+nPos, "%08X", (unsigned int)(pDis->bpTarget + (signed long)dwULONG + bInstrLen) );
                 }
                 else
                 {
                     wUSHORT = NEXTUSHORT;
                     if(ScanExportsByAddress(&pSymbolName,(unsigned int)(pDis->bpTarget + (signed short)wUSHORT + bInstrLen)))
                        nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", pSymbolName );
                     else
                        nPos += PICE_sprintf( pDis->szDisasm+nPos, "%08X", (unsigned int)(pDis->bpTarget + (signed short)wUSHORT + bInstrLen) );
                 }
             break;

             case _O  :                                         // Simple USHORT or ULONG offset
                  if( pDis->dwFlags & DIS_ADDRESS32 )           // depending on the address size
                  {
                      dwULONG = NEXTULONG;
                      nPos += PICE_sprintf( pDis->szDisasm+nPos,"%s[%08X]", sSegOverride[ bSegOverride ], (unsigned int) dwULONG );
                  }
                  else
                  {
                      wUSHORT = NEXTUSHORT;
                      nPos += PICE_sprintf( pDis->szDisasm+nPos,"%s[%04X]", sSegOverride[ bSegOverride ], wUSHORT );
                  }
             break;

             case _Ib :                                         // immediate UCHAR
                 bUCHAR = NEXTUCHAR;
                 nPos += PICE_sprintf( pDis->szDisasm+nPos,"%02X", bUCHAR );
             break;

             case _Iv :                                         // immediate USHORT or ULONG
                 if( pDis->dwFlags & DIS_DATA32 )
                 {
                      dwULONG = NEXTULONG;
                      nPos += PICE_sprintf( pDis->szDisasm+nPos, "%08X", (unsigned int) dwULONG );
                 }
                 else
                 {
                     wUSHORT = NEXTUSHORT;
                     nPos += PICE_sprintf( pDis->szDisasm+nPos, "%04X", wUSHORT );
                 }
             break;

             case _Iw :                                         // Immediate USHORT
                 wUSHORT = NEXTUSHORT;
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%04X", wUSHORT );
             break;

             case _Ap :                                         // 32 bit or 48 bit pointer (call far, jump far)
                 if( pDis->dwFlags & DIS_DATA32 )
                 {
                      dwULONG = NEXTULONG;
                      wUSHORT = NEXTUSHORT;
                      nPos += PICE_sprintf( pDis->szDisasm+nPos, "%04X:%08X", wUSHORT, (unsigned int) dwULONG );
                 }
                 else
                 {
                     dwULONG = NEXTULONG;
                     nPos += PICE_sprintf( pDis->szDisasm+nPos, "%08X", (unsigned int) dwULONG );
                 }
             break;

             case _1 :                                          // numerical 1
                 nPos += PICE_sprintf( pDis->szDisasm+nPos,"1" );
             break;

             case _3 :                                          // numerical 3
                 nPos += PICE_sprintf( pDis->szDisasm+nPos,"3" );
             break;

                                                                // Hard coded registers
             case _DX: case _AL: case _AH: case _BL: case _BH: case _CL: case _CH:
             case _DL: case _DH: case _CS: case _DS: case _ES: case _SS: case _FS:
             case _GS:
                 nPos += PICE_sprintf( pDis->szDisasm+nPos,"%s", sRegs2[ *pArg - _DX ] );
             break;

             case _eAX: case _eBX: case _eCX: case _eDX:
             case _eSP: case _eBP: case _eSI: case _eDI:
                 nPos += PICE_sprintf( pDis->szDisasm+nPos, "%s", sGenReg16_32[DIS_GETDATASIZE(pDis->dwFlags)][ *pArg - _eAX ]);
             break;

             case _ST:                                          // Coprocessor ST
                nPos += PICE_sprintf( pDis->szDisasm+nPos,"%s", sST[9] );
             break;

            case _ST0:                                         // Coprocessor ST(0) - ST(7)
            case _ST1:
            case _ST2:
            case _ST3:
            case _ST4:
            case _ST5:
            case _ST6:
            case _ST7:
               nPos += PICE_sprintf( pDis->szDisasm+nPos,"%s", sST[ *pArg - _ST0 ] );
            break;

            case _AX:                                           // Coprocessor AX
                nPos += PICE_sprintf( pDis->szDisasm+nPos,"%s", sGenReg16_32[0][0] );
            break;
        }
    }

DisEnd:

    // Set the returning values and return with the bInstrLen field

    pDis->bAsciiLen = (UCHAR) nPos;
    pDis->bInstrLen = bInstrLen;

    return bInstrLen;
}