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
#define CO_DIST                    6.0
    
void ContactOrder(CHAIN **Chain, int NChain, COMMAND *Cmd )
{

  register int Res1, Res2, At1, At2;
  int Cn, From, To, NumberOfContacts;
  char PDB_Start[RES_FIELD], PDB_End[RES_FIELD];
  double CO;
  
  for( Cn=0; Cn<NChain; Cn++ ) {
    
    if( !Chain[Cn]->Valid )
      continue;
    NumberOfContacts = 0;
    CO = 0.0;
    if( !strcmp(Cmd->FirstResidue,"") ) {
      From = 0;
      strcpy(PDB_Start,Chain[Cn]->Rsd[0]->PDB_ResNumb);
    }
    else { 
      if( !PdbN2SeqN(Chain[Cn],Cmd->FirstResidue,&From) ) {
	fprintf(stderr,"Residue %s does not exist in %s chain %c\n",
		Cmd->FirstResidue,Chain[Cn]->PdbIdent,SpaceToDash(Chain[Cn]->Id));
	exit(1);
      }
      strcpy(PDB_Start,Cmd->FirstResidue);
    }
    if( !strcmp(Cmd->LastResidue,"") ) {
      To = Chain[Cn]->NRes;
      strcpy(PDB_End,Chain[Cn]->Rsd[Chain[Cn]->NRes-1]->PDB_ResNumb);
    }
    else {
      if( !PdbN2SeqN(Chain[Cn],Cmd->LastResidue,&To) ) {
	fprintf(stderr,"Residue %s does not exist in %s chain %c\n",
		Cmd->LastResidue,Chain[Cn]->PdbIdent,SpaceToDash(Chain[Cn]->Id));
	exit(1);
      }
      strcpy(PDB_End,Cmd->LastResidue);
    }
    for( Res1=From; Res1<To-1; Res1++ ) {
      for( At1=0; At1<Chain[Cn]->Rsd[Res1]->NAtom; At1++ ) {
	if( !strcmp(Chain[Cn]->Rsd[Res1]->AtomType[At1],"H") )
	  continue;
	for( Res2 = Res1+1; Res2<To; Res2++ ) {
	  for( At2=0; At2<Chain[Cn]->Rsd[Res2]->NAtom; At2++ ) {
	    if( !strcmp(Chain[Cn]->Rsd[Res2]->AtomType[At2],"H") )
	      continue;
	    if( Dist(Chain[Cn]->Rsd[Res1]->Coord[At1],
		     Chain[Cn]->Rsd[Res2]->Coord[At2]) < CO_DIST) {
	      CO += abs(Res1-Res2);
	      NumberOfContacts++;
	    }
	  }
	}
      }
    }
    CO = 100.0*CO/NumberOfContacts;
    CO /= (To-From+1);
    
    printf("%s %c %d ( %s ) %d ( %s ) %5.1f\n",
	   Chain[Cn]->PdbIdent,SpaceToDash(Chain[Cn]->Id),From,PDB_Start,To-1,PDB_End,CO);
  }
  exit(0);
}
