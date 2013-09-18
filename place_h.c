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

int PlaceHydrogens(CHAIN *Chain)
{

  int Res, i, N, C, CA, H, PlacedCnt=0;
  float Length_N_C, Length_N_CA, Length_N_H;
  RESIDUE *r, *rr;
  
  for( Res=1; Res<Chain->NRes; Res++ ) {
    
    r  = Chain->Rsd[Res];
    rr = Chain->Rsd[Res-1];

      if( !strcmp(r->ResType,"PRO") ) continue;

      /* Replace deiterium atoms by hydrogens */
      if( FindAtom(Chain,Res,"D",&H) ) 
	strcmp(r->AtomType[H],"H");

      if( !FindAtom(Chain,Res,"H",&H)  && FindAtom(Chain,Res,"N",&N)   &&
	   FindAtom(Chain,Res-1,"C",&C) && FindAtom(Chain,Res,"CA",&CA) ) {

	H = r->NAtom;
	
	Length_N_C   = Dist(r->Coord[N],rr->Coord[C]);
	Length_N_CA  = Dist(r->Coord[N],r->Coord[CA]);
	
	for( i=0; i<3; i++ )
	  r->Coord[H][i] = r->Coord[N][i] - 
	      ( (rr->Coord[C][i] -  r->Coord[N][i])/Length_N_C +
	        (r->Coord[CA][i]  -  r->Coord[N][i])/Length_N_CA );

	Length_N_H = Dist(r->Coord[N],r->Coord[H]);

	for( i=0; i<3; i++ )
	  r->Coord[H][i] = r->Coord[N][i] + 
	    DIST_N_H*(r->Coord[H][i]-r->Coord[N][i])/Length_N_H;

	strcpy(r->AtomType[H],"H");
	r->NAtom++;
	PlacedCnt++;
      }
    }
  return(PlacedCnt);
}



