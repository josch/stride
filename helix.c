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

void Helix(CHAIN **Chain, int Cn, HBOND **HBond, COMMAND *Cmd, float **PhiPsiMap)
{

  int BondNumb, i;
  float *Prob, CONST;
  RESIDUE **r;

  CONST = 1+Cmd->C1_H;

  Prob = (float *)ckalloc(MAX_RES*sizeof(float));

  for( i=0; i<Chain[Cn]->NRes; i++ )
    Prob[i] = 0.0; 


  for( i=0; i<Chain[Cn]->NRes-5; i++ ) {

    r = &Chain[Cn]->Rsd[i];

    if( r[0]->Prop->PhiZn != ERR && r[0]->Prop->PsiZn != ERR &&
        r[1]->Prop->PhiZn != ERR && r[1]->Prop->PsiZn != ERR &&
        r[2]->Prop->PhiZn != ERR && r[2]->Prop->PsiZn != ERR &&
        r[3]->Prop->PhiZn != ERR && r[3]->Prop->PsiZn != ERR &&
        r[4]->Prop->PhiZn != ERR && r[4]->Prop->PsiZn != ERR ) {

      if( (BondNumb = FindPolInt(HBond,r[4],r[0])) != ERR ) {
	Prob[i] = HBond[BondNumb]->Energy*(CONST+Cmd->C2_H*
	    0.5*(PhiPsiMap[r[0]->Prop->PhiZn][r[0]->Prop->PsiZn]+
		 PhiPsiMap[r[4]->Prop->PhiZn][r[4]->Prop->PsiZn]));

      }
    }
  }
  
  for( i=0; i<Chain[Cn]->NRes-5; i++ ) {

    if( Prob[i] < Cmd->Treshold_H1 && Prob[i+1] < Cmd->Treshold_H1 ) {

      r = &Chain[Cn]->Rsd[i];

      r[1]->Prop->Asn = 'H'; 
      r[2]->Prop->Asn = 'H'; 
      r[3]->Prop->Asn = 'H'; 
      r[4]->Prop->Asn = 'H';
      if( r[0]->Prop->PhiZn!= ERR && r[0]->Prop->PsiZn != ERR &&
	  PhiPsiMap[r[0]->Prop->PhiZn][r[0]->Prop->PsiZn] > Cmd->Treshold_H3 )
	r[0]->Prop->Asn = 'H';
      if( r[5]->Prop->PhiZn != ERR && r[5]->Prop->PsiZn != ERR &&
	  PhiPsiMap[r[5]->Prop->PhiZn][r[5]->Prop->PsiZn] > Cmd->Treshold_H4 )
	r[5]->Prop->Asn = 'H';
    }
  }

  for( i=0; i<Chain[Cn]->NRes-4; i++ ) {

    r = &Chain[Cn]->Rsd[i];

    if(  FindBnd(HBond,r[3],r[0]) != ERR && FindBnd(HBond,r[4],r[1]) != ERR &&
       /*************************** This should be improved **************************/
         ( (r[1]->Prop->Asn != 'H' && r[2]->Prop->Asn != 'H') ||
	   (r[2]->Prop->Asn != 'H' && r[3]->Prop->Asn != 'H') ) ) 
       /******************************************************************************/
      {
	r[1]->Prop->Asn = 'G'; 
	r[2]->Prop->Asn = 'G'; 
	r[3]->Prop->Asn = 'G'; 
      }
  }

  for( i=0; i<Chain[Cn]->NRes-6; i++ ) {

    r = &Chain[Cn]->Rsd[i];

    if( FindBnd(HBond,r[5],r[0]) != ERR && FindBnd(HBond,r[6],r[1]) != ERR &&
        r[1]->Prop->Asn == 'C' && r[2]->Prop->Asn == 'C' && 
        r[3]->Prop->Asn == 'C' && r[4]->Prop->Asn == 'C' && 
        r[5]->Prop->Asn == 'C' ) {
      r[1]->Prop->Asn = 'I'; 
      r[2]->Prop->Asn = 'I';
      r[3]->Prop->Asn = 'I'; 
      r[4]->Prop->Asn = 'I'; 
      r[5]->Prop->Asn = 'I'; 
    }
  }

  if( Cmd->Info ) {
    fprintf(stdout,"%s%c\n",Chain[Cn]->File,Chain[Cn]->Id);

    for( i=0; i<Chain[Cn]->NRes-4; i++ ) {

      r = &Chain[Cn]->Rsd[i];

      if( r[0]->Prop->PhiZn != ERR && r[0]->Prop->PsiZn != ERR &&
	  r[4]->Prop->PhiZn != ERR && r[4]->Prop->PsiZn != ERR ) {
	
	fprintf(stdout,"%s (%d) %c %10.7f %8.5f %8.5f | %4d %4d\n",
		r[0]->PDB_ResNumb,i,r[0]->Prop->Asn,Prob[i],
		PhiPsiMap[r[0]->Prop->PhiZn][r[0]->Prop->PsiZn],
		PhiPsiMap[r[4]->Prop->PhiZn][r[4]->Prop->PsiZn],
		r[4]->Prop->PhiZn,r[4]->Prop->PsiZn);
      }
    }
  }
  free(Prob);
}







