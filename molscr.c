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

int MolScript(CHAIN **Chain, int NChain, COMMAND *Cmd)
{

  int HelixBound[MAX_ASSIGN][2], SheetBound[MAX_ASSIGN][2], CoilBound[MAX_ASSIGN][2];
  int NHelix, NSheet, NCoil, i, Cn;
  char *Asn;
  FILE *fi;

  if( !(fi = fopen(Cmd->MolScriptFile,"w")) )
    return(escape(FAILURE,"\nCan not open molscript file %s\n\n",Cmd->MolScriptFile));

  fprintf(fi,"plot\n");
  fprintf(fi,"read mol \"%s\";\n",Chain[0]->File);
  fprintf(fi,"transform atom * by centre position in amino-acids\n");
  fprintf(fi,"by rotation z  0.0	\n");
  fprintf(fi,"by rotation y -260.0	\n");
  fprintf(fi,"by rotation x -40.0;\n");
      
  for( Cn=0; Cn<NChain; Cn++ ) {

    if( !Chain[Cn]->Valid )
       continue;

    Asn = (char *)ckalloc(Chain[Cn]->NRes*sizeof(char));

    ExtractAsn(Chain,Cn,Asn);
    for( i=0; i<Chain[Cn]->NRes; i++ )
      if( Asn[i] != 'H' && Asn[i] != 'E' )
	Asn[i] = 'C';

    NHelix = Boundaries(Asn,Chain[Cn]->NRes,'H',HelixBound);
    NSheet = Boundaries(Asn,Chain[Cn]->NRes,'E',SheetBound);
    NCoil  = Boundaries(Asn,Chain[Cn]->NRes,'C',CoilBound);

    free(Asn);
    
    for( i=0; i<NSheet; i++ )  
      if( SheetBound[i][1] != Chain[Cn]->NRes-1 ) 
	SheetBound[i][1]++;
    for( i=0; i<NHelix;  i++ ) 
      if( HelixBound[i][1] != Chain[Cn]->NRes-1 ) 
	HelixBound[i][1]++;
    for( i=0; i<NCoil;   i++ ) 
      if( CoilBound[i][1]  != Chain[Cn]->NRes-1 )
	CoilBound[i][1]++;
    
    for( i=0; i<NHelix; i++ )
      fprintf(fi,"helix from %c%s to %c%s;\n",
	      Chain[Cn]->Id,Chain[Cn]->Rsd[HelixBound[i][0]]->PDB_ResNumb,
	      Chain[Cn]->Id,Chain[Cn]->Rsd[HelixBound[i][1]]->PDB_ResNumb);
  
    for( i=0; i<NSheet; i++ )
      fprintf(fi,"strand from %c%s to %c%s;\n",
	      Chain[Cn]->Id,Chain[Cn]->Rsd[SheetBound[i][0]]->PDB_ResNumb,
	      Chain[Cn]->Id,Chain[Cn]->Rsd[SheetBound[i][1]]->PDB_ResNumb);
    
    for( i=0; i<NCoil; i++ )
      fprintf(fi,"coil from %c%s to %c%s;\n",
	      Chain[Cn]->Id,Chain[Cn]->Rsd[CoilBound[i][0]]->PDB_ResNumb,
	      Chain[Cn]->Id,Chain[Cn]->Rsd[CoilBound[i][1]]->PDB_ResNumb);
  }

  fprintf(fi,"end_plot\n");
  fclose(fi);
  
  return(SUCCESS);
}



