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

void BackboneAngles(CHAIN **Chain, int NChain)
{

  register int Res, Cn;

  for( Cn=0; Cn<NChain; Cn++ ) {

    for( Res=0; Res<Chain[Cn]->NRes; Res++ ) {
      PHI(Chain[Cn],Res);
      PSI(Chain[Cn],Res);
    }
  }
}

void DiscrPhiPsi(CHAIN **Chain, int NChain, COMMAND *Cmd)
{

  register int i, Res, Cn;
  RESIDUE *r;

  for( Cn=0; Cn<NChain; Cn++ ) {
    
    for( Res=0; Res<Chain[Cn]->NRes; Res++ ) {
      
      r = Chain[Cn]->Rsd[Res];
      
      r->Prop->PhiZn = ERR;
      r->Prop->PsiZn = ERR;
      
      if( Res != 0 ) {
	for( i=0; i<Cmd->NPixel; i++ )
	  if( r->Prop->Phi  >  MINPHIPSI+(float)(i)*Cmd->PhiPsiStep && 
	      r->Prop->Phi <=  MINPHIPSI+(float)(i+1)*Cmd->PhiPsiStep ) {
	    r->Prop->PhiZn = i;
	    break;
	  }
      }
      
      if( Res != Chain[Cn]->NRes-1 ) {
	for( i=0; i<Cmd->NPixel; i++ )
	  if( r->Prop->Psi  >  MINPHIPSI+(float)(i)*Cmd->PhiPsiStep && 
	      r->Prop->Psi <=  MINPHIPSI+(float)(i+1)*Cmd->PhiPsiStep ) {
	    r->Prop->PsiZn = i;
	    break;
	  }
      }
      
    }
    
    for(Res=0; Res<Chain[Cn]->NRes; Res++ )  {
      r = Chain[Cn]->Rsd[Res];
      if( Res != 0 && r->Prop->PsiZn == ERR )
	r->Prop->PsiZn = Chain[Cn]->Rsd[Res-1]->Prop->PsiZn;
      if( Res != Chain[Cn]->NRes-1 && r->Prop->PhiZn == ERR )
	r->Prop->PhiZn = Chain[Cn]->Rsd[Res+1]->Prop->PhiZn;
    }

  }
}


