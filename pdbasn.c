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

/*************************************************************************
**                                                                      **
** Get PDB secondary structure assignment for every residue             **
**                                                                      **
*************************************************************************/
void GetPdbAsn(CHAIN **Chain, int NChain)
{

  register int i, j, k;
  int Cn, Beg, End;
  char SecondStr;
  CHAIN *c;

  for( Cn=0; Cn<NChain; Cn++ ) {

    c = Chain[Cn];

    for( i=0; i<c->NHelix; i++ ) {

      switch( c->Helix[i]->Class ) {
      case 1:  SecondStr = 'H';
	break;
      case 3:  SecondStr = 'I';
	break;
      case 5:  SecondStr = 'G';
	break;
      }

      if( PdbN2SeqN(c,c->Helix[i]->PDB_ResNumb1,&Beg) &&
	  PdbN2SeqN(c,c->Helix[i]->PDB_ResNumb2,&End) )
	for( j=Beg; j<=End; j++ )
	  if( c->Rsd[j]->Prop->PdbAsn != 'H' )
	    c->Rsd[j]->Prop->PdbAsn = SecondStr;
    }
    
    for( i=0; i<c->NSheet; i++ )
      for( j=0; j<c->Sheet[i]->NStrand; j++ ) {
	  if( PdbN2SeqN(c,c->Sheet[i]->PDB_ResNumb1[j],&Beg) &&
	      PdbN2SeqN(c,c->Sheet[i]->PDB_ResNumb2[j],&End) )
	    for( k=Beg; k<=End; k++ )
	      if( c->Rsd[k]->Prop->PdbAsn != 'H' )
		c->Rsd[k]->Prop->PdbAsn = 'E';
	}

    for( i=0; i<c->NTurn; i++ ) { 
      if( PdbN2SeqN(c,c->Turn[i]->PDB_ResNumb1,&Beg) &&
	  PdbN2SeqN(c,c->Turn[i]->PDB_ResNumb2,&End) )
	for( j=Beg; j<=End; j++ )
	  if( c->Rsd[j]->Prop->PdbAsn != 'H' &&  c->Rsd[j]->Prop->PdbAsn != 'E' )
	    c->Rsd[j]->Prop->PdbAsn = 'T';
    }
  }
}



