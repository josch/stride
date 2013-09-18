/*
 * Copyright (C) 1992-1994 Dmitrij Frishman <d.frishman at wzw.tum.de>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "stride.h"

int Process_ATOM(BUFFER Buffer, CHAIN **Chain, int *ChainNumber, 
		 BOOLEAN *First_ATOM, COMMAND *Cmd)
{

  char *Field[MAX_FIELD];
  BUFFER Tmp;
  int CC, NR, NA;
  static char LastRes[MAX_CHAIN][RES_FIELD];
  RESIDUE *r;

  if( Cmd->NActive && !ChInStr(Cmd->Active,SpaceToDash(Buffer[21])) )
     return(SUCCESS);

  if( Buffer[16] != 'A' && Buffer[16] != ' ' && Buffer[16] != '1' ) 
    return(SUCCESS);

  if( *First_ATOM ) {
    for( CC=0; CC<MAX_CHAIN; CC++ ) 
      strcpy(LastRes[CC],"XXXX");
    *First_ATOM = NO;
  }
  
  for( CC=0; CC < *ChainNumber && Chain[CC]->Id != Buffer[21] ; CC++ );
  
  if( CC == *ChainNumber ) {
    InitChain(&Chain[CC]); 
    Chain[CC]->Id = Buffer[21];
    (*ChainNumber)++;
  }
  else
  if( Chain[CC]->Ter == 1 ) 
    return(SUCCESS);

  if( Buffer[34] != '.' || Buffer[42] != '.' || Buffer[50] != '.' )
    return(escape(FAILURE,"File %s has no coordinates\n",Cmd->InputFile));

  
  if( Cmd->Stringent && Buffer[63] != '.')
    return(escape(FAILURE,"File %s has no temperature factor\n",Cmd->InputFile));


  SplitString(Buffer+22,Field,1);
  if( strcmp(Field[0],LastRes[CC]) ) {
    if( strcmp(LastRes[CC],"XXXX") && !FindAtom(Chain[CC],Chain[CC]->NRes,"CA",&NA) ) {
      free(Chain[CC]->Rsd[Chain[CC]->NRes]);
      Chain[CC]->NRes--;
    }
    if( strcmp(LastRes[CC],"XXXX") ) Chain[CC]->NRes++;
    NR = Chain[CC]->NRes;
    strcpy(LastRes[CC],Field[0]);
    Chain[CC]->Rsd[NR] = (RESIDUE *)ckalloc(sizeof(RESIDUE));
    strcpy(Chain[CC]->Rsd[NR]->PDB_ResNumb,LastRes[CC]);
    Chain[CC]->Rsd[NR]->NAtom = 0;
    SplitString(Buffer+17,Field,1);
    strcpy(Chain[CC]->Rsd[NR]->ResType,Field[0]);
  }
  else 
    NR = Chain[CC]->NRes;
  
  NA = Chain[CC]->Rsd[NR]->NAtom;

  if( Buffer[16] != ' ' ) {
    strcpy(Tmp,Buffer);
    Tmp[16] = ' ';
    SplitString(Tmp+12,Field,1);
  }
  else
    SplitString(Buffer+12,Field,1);
  
  r = Chain[CC]->Rsd[NR];
  strcpy(r->AtomType[NA],Field[0]);


  strcpy(Tmp,Buffer);
  Buffer[38] = ' ';
  SplitString(Tmp+30,Field,1);
  r->Coord[NA][0] = atof(Field[0]);

  strcpy(Tmp,Buffer);
  Buffer[46] = ' ';
  SplitString(Tmp+38,Field,1);
  r->Coord[NA][1] = atof(Field[0]);

  strcpy(Tmp,Buffer);
  Buffer[54] = ' ';
  SplitString(Tmp+46,Field,1);
  r->Coord[NA][2] = atof(Field[0]);

  if( Buffer[57] == '.' ) {
    strcpy(Tmp,Buffer);
    Tmp[60] = ' ';
    SplitString(Tmp+54,Field,1);
    r->Occupancy[NA] = atof(Field[0]);
  }
  else 
    r->Occupancy[NA] = -1.00;
  
  SplitString(Buffer+63,Field,1);
  r->TempFactor[NA] = atof(Field[0]);

  r->NAtom++;

  if( r->NAtom > MAX_AT_IN_RES-1 )
    return(escape(FAILURE,"File %s has too many atoms in residue %s %s %c\n",
		  Cmd->InputFile,r->ResType,r->PDB_ResNumb,Chain[CC]->Id));

  return(SUCCESS);
}
