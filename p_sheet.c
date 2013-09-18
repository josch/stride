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

int Process_SHEET(BUFFER Buffer, CHAIN **Chain, int *ChainNumber, COMMAND *Cmd)
{
  int CC, SC, STC;
  char *Field[MAX_FIELD];
  BUFFER Tmp;
  static char PreviousChain, PreviousSheetId[RES_FIELD];

  if( Cmd->NActive && !ChInStr(Cmd->Active,SpaceToDash(Buffer[21])) )
     return(SUCCESS);

  for( CC=0; CC < *ChainNumber && Chain[CC]->Id != Buffer[21]; CC++ );

  if( CC == *ChainNumber ) {
    InitChain(&Chain[CC]); 
    Chain[CC]->Id = Buffer[21];
    (*ChainNumber)++;
  }

  if( Chain[CC]->NSheet == -1 ) {
    PreviousChain = '*';
    strcpy(PreviousSheetId,"*");
  }

  SplitString(Buffer+7,Field,2);

  if( atoi(Field[0]) == 1 || Buffer[21] != PreviousChain ) {
    if( Buffer[21] == PreviousChain && !strcmp(PreviousSheetId,Field[1]) )
      return(FAILURE);
/*      die("Here it is! -> %s%c\n", Chain[CC]->File,Chain[CC]->Id);*/
    Chain[CC]->NSheet++;
    SC = Chain[CC]->NSheet;
    Chain[CC]->Sheet[SC] =  (SHEET *)ckalloc(sizeof(SHEET));
    Chain[CC]->Sheet[SC]->NStrand = 0;
    STC = Chain[CC]->Sheet[SC]->NStrand;
    strcpy(Chain[CC]->Sheet[SC]->SheetId,Field[1]);
  }
  else
    {
      SC = Chain[CC]->NSheet;
      STC = Chain[CC]->Sheet[SC]->NStrand;
    }
  
  SplitString(Buffer+17,Field,1);
  strcpy(Chain[CC]->Sheet[SC]->ResType1[STC],Field[0]);

  SplitString(Buffer+28,Field,1);
  strcpy(Chain[CC]->Sheet[SC]->ResType2[STC],Field[0]);

  strcpy(Tmp,Buffer);
  Tmp[27] = ' ';
  Tmp[38] = ' ';
  SplitString(Tmp+22,Field,1);
  strcpy(Chain[CC]->Sheet[SC]->PDB_ResNumb1[STC],Field[0]);
  SplitString(Tmp+33,Field,1);
  strcpy(Chain[CC]->Sheet[SC]->PDB_ResNumb2[STC],Field[0]);

  Chain[CC]->Sheet[SC]->InsCode1[STC] = Buffer[26];
  Chain[CC]->Sheet[SC]->InsCode2[STC] = Buffer[37];

  SplitString(Buffer+38,Field,1);
  Chain[CC]->Sheet[SC]->Sence[STC] = atoi(Field[0]);

  if( Buffer[45] != ' ' ) {
    Chain[CC]->Sheet[SC]->RegYN[STC] = 1;
    SplitString(Buffer+45,Field,1);
    strcpy(Chain[CC]->Sheet[SC]->ResTypeReg1[STC],Field[0]);
    SplitString(Buffer+60,Field,1);
    strcpy(Chain[CC]->Sheet[SC]->ResTypeReg2[STC],Field[0]);
    
    Tmp[55] = ' ';
    Tmp[70] = ' ';
    SplitString(Tmp+50,Field,1);
    strcpy(Chain[CC]->Sheet[SC]->PDB_ResNumbReg1[STC],Field[0]);
    SplitString(Tmp+66,Field,1);
    strcpy(Chain[CC]->Sheet[SC]->PDB_ResNumbReg2[STC],Field[0]);
    
    Chain[CC]->Sheet[SC]->InsCodeReg1[STC] = Buffer[54];
    Chain[CC]->Sheet[SC]->InsCodeReg2[STC] = Buffer[69];
    
    Tmp[45] = ' ';
    Tmp[60] = ' ';
    SplitString(Tmp+41,Field,1);
    strcpy(Chain[CC]->Sheet[SC]->AtomNameReg1[STC],Field[0]);
    SplitString(Tmp+56,Field,1);
    strcpy(Chain[CC]->Sheet[SC]->AtomNameReg2[STC],Field[0]);
  }
  else Chain[CC]->Sheet[SC]->RegYN[STC] = 0;

  strcpy(PreviousSheetId,Chain[CC]->Sheet[SC]->SheetId);
  PreviousChain = Buffer[21];
  Chain[CC]->Sheet[SC]->NStrand++;

  return(SUCCESS);
}



 
