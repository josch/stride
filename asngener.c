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
** Remove short stretches of secondary structure from the assignment    **
**                                                                      **
** INPUT:   *Asn       String with one letter secondary structure       **
**                     assignment                                       **
**          Length     Length of the string                             **
**          SecStrType Type of the secondary structure to which this    **
**                     operation should be applied                      **
**          EditChar   Character to be used instead of removed symbols  **
**          MaxLength  Maximal length of secondary struture segments to **
**                     be removed                                       **
**                                                                      **
** OUTPUT:  *Asn       Edited secondary structure assignment            **
**                                                                      **
*************************************************************************/
void CorrectAsn(char *Asn, int Length, char SecStrType, char EditChar, int MaxLength)
{

  int NStr = 0, Res, Flag = 0, Bound[MAX_ASSIGN][2], i;

  for( Res=0; Res<Length; Res++ ) {
    if( Asn[Res] == SecStrType && Flag == 0 ) {
      Flag = 1; 
      Bound[NStr][0] = Res;
    }
    else
    if( Asn[Res] != SecStrType && Flag == 1 ) {
      Flag = 0; 
      Bound[NStr++][1] = Res-1;
    }
  }

  for( i=0; i<NStr; i++ )
    if( Bound[i][1]-Bound[i][0]+1 <= MaxLength )
      for( Res=Bound[i][0]; Res<=Bound[i][1]; Res++ ) 
	Asn[Res] = EditChar;
}

void CorrectAsnDouble(char *Asn1, char *Asn2, char *KnownAsn, int Length, 
		      char SecStrType, char EditChar)
{

  register int Res;

  for( Res=0; Res<Length; Res++ )
    if( (Asn1[Res] == SecStrType || Asn2[Res] == SecStrType) && KnownAsn[Res] != SecStrType &&
        ( (Res == 0 && Asn1[Res+1] != SecStrType && Asn2[Res+1] != SecStrType) ||
	  (Res == Length-1 && Asn1[Res-1] != SecStrType && Asn2[Res-1] != SecStrType) ||
          (Res > 0 && Res < Length-1 && 
	   Asn1[Res-1] != SecStrType && Asn2[Res-1] != SecStrType && 
	   Asn1[Res+1] != SecStrType && Asn2[Res+1] != SecStrType) ) )
      Asn1[Res] = Asn2[Res] = EditChar;
      
}

/*************************************************************************
**                                                                      **
** Calculate the number of true positives, true negatives, false        **
** negatives and false positives resulting from comparison of test and  **
** known secondary structure assignments for a particular secondary     **
** structure type                                                       **
**                                                                      **
** INPUT:   *TestAsn   String with one letter test secondary structure  **
**                     assignment                                       **
**          *KnownAsn  String with one letter known secondary structure **
**                     assignment                                       **
**          Length     Length of the assignment                         **
**          SecStrType Type of the secondary structure to which this    **
**                     operation should be applied                      **
**                                                                      **
** OUTPUT:  *Quality   Pointer to the structure with quality assessment **
**                                                                      **
*************************************************************************/
int Difference(char *TestAsn, char *KnownAsn, int Length, char SecStrType, QUALITY *Qual)
{
  register int Res;

  Qual->TP = Qual->TN = Qual->FP = Qual->FN = 0;

  for( Res=0; Res<Length; Res++ ) {
    if( KnownAsn[Res] != 'X' ) { 

      if( KnownAsn[Res] == SecStrType && TestAsn[Res]  == SecStrType ) Qual->TP++;
      else 
      if( KnownAsn[Res] != SecStrType && TestAsn[Res]  != SecStrType ) Qual->TN++;
      else 
      if( KnownAsn[Res] != SecStrType && TestAsn[Res]  == SecStrType ) Qual->FP++;
      else 
      if( KnownAsn[Res] == SecStrType && TestAsn[Res]  != SecStrType ) Qual->FN++;
    }
  }

  if( Qual->TP == 0 && Qual->TN == 0 && Qual->FP == 0 && Qual->FN == 0 )  {
    Qual->Perc = 0.0;
    return(FAILURE);
  }

  Qual->Perc = 
    ((float)Qual->TP+(float)Qual->TN)/
      ((float)Qual->TP+(float)Qual->TN+(float)Qual->FP+(float)Qual->FN);

  return(SUCCESS);
}

/*************************************************************************
**                                                                      **
** Calculate percent of the correctly assigned residues                 **
**                                                                      **
** INPUT:   *TestAsn   String with one letter test secondary structure  **
**                     assignment                                       **
**          *KnownAsn  String with one letter known secondary structure **
**                     assignment                                       **
**          Length     Length of the assignment                         **
**                                                                      **
** RETURNS:            Percent correct                                  **
**                                                                      **
*************************************************************************/
float PercentCorrect(char *TestAsn, char *KnownAsn, int Length)
{
  int Res, Count=0;;

  for( Res=0; Res<Length; Res++ )
    if( KnownAsn[Res] == TestAsn[Res] )
      Count++;

  return( ((float)Count/(float)Length) );
}

/*************************************************************************
**                                                                      **
** Calculate measures of secondary structure assignment quality based   **
** on the number of true positives, true negatives, false negatives and **
** false positives resulting from comparison of test and known          **
** assignments                                                          **
**                                                                      **
** INPUT:   *Quality   Pointer to the structure with quality assessment **
**                     assignment                                       **
** OUTPUT:  Quality->Corr  Correlation coefficient between the two      **
**                         assignments as suggested by B.Matthews       **
**                         (1975) Biochim. Biophys. Acta, 405, 442-451  **
**          Quality->Perc  Percent correct                              **
**                                                                      **
*************************************************************************/
int AssessCorr(QUALITY *Qual)
{

  float TP, TN, FP, FN;

  if( (Qual->TP == 0 && Qual->FN == 0) || (Qual->TP == 0 && Qual->FP == 0) ) return(FAILURE);
  else {
    TP = (float)Qual->TP; 
    TN = (float)Qual->TN; 
    FP = (float)Qual->FP; 
    FN =(float)Qual->FN;

    Qual->Corr = (TP*TN - FN*FP)/sqrt((TN+FN)*(TN+FP)*(TP+FN)*(TP+FP));

    return(SUCCESS);
  }
}

int AssessPerc(QUALITY *Qual)
{

  float TP, TN, FP, FN;

  TP = (float)Qual->TP; 
  TN = (float)Qual->TN; 
  FP = (float)Qual->FP; 
  FN =(float)Qual->FN;

  Qual->Perc = (TP+TN)/(TP+TN+FP+FN);

  return(SUCCESS);
}

void ExcludeObvious(char *Asn1, char *Asn2, char *KnownAsn, int Length)
{
  register int i;

  for( i=0; i<Length; i++ )
    if( Asn1[i] == Asn2[i] ) {
      KnownAsn[i] = 'X';
      Asn1[i] = 'X';
      Asn2[i] = 'X';
    }
}


