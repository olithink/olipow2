/* OliPow Version 2.2d (c) Suicide Part */

void thinksuic(void)
{
int stellungswert=0,absmat=-SWK,legalanzahl=0,bzug=0,dfl2=0;
int alpha=SCHLECHT,beta,maximum,drw,startd;
int i,j,w=0,d,kp,zfall=0,re1,re2,repfl=0,zuf=ZUFALL;
int legals[MAXMGL],legalz[MAXMGL],kil[MAXMGL];

nm=0;abbruch=0;ply=0;endtiefe=1;kib=1;
restnode=NODEC;zuf*=5;
altmat=material;balt=0;walt=wold;d=dran+1;ner++;
start=myget();
for (i=21;i<=91;i+=10)
 for (j=i;j<i+8;j++)
   if (dran*Board[j]>0) absmat++;
absmat+=SWK;
if (absmat<5) pawnstorm=2*PAWNS;

kp=koenig[d];
if (ZUFALL>=1 && numhalbz<40) zfall=(int)(12347*rand());
for (i=0;i<MAXTIEF-2;i++) 
{ Hvon[0][i]=Hvon[0][i+2]; Hnach[0][i]=Hnach[0][i+2];
  Kvon[i]=Kvon[i+2]; Knach[i]=Knach[i+2];
  K2von[i]=K2von[i+2]; K2nach[i]=K2nach[i+2];
  K3von[i]=K3von[i+2]; K3nach[i]=K3nach[i+2]; }

for (i=0;i<BDIM;i++) 
  for (j=0;j<BDIM;j++) History[i][j]=0;
startd=STARTDEPTH; 

for (zugtiefe=startd;zugtiefe<=ZUGMAX;zugtiefe++)
{ 
  Htief[ply]=ply;
  if (zugtiefe==STARTDEPTH) { alpha=SCHLECHT;beta=GUT; } 
  else { beta=alpha+WIND;alpha-=WIND; }
     maxtiefe=zugtiefe+SUICWEIT;
  maxtiefe=maxtiefe+6-absmat/2; 
  legalanzahl=gensuic(&legals[0],&legalz[0],&kil[0],-1);
  if (legalanzahl==0) matt();
  if (legalanzahl>ONEDEBUG || permbrain==1) 
  { for (i=0;i<legalanzahl;i++)
    {
	szug=legals[i]; 
	zug=legalz[i];
	ezug=szug+zug; drw=1;
	if (ZUFALL==0 || ner>ZUFEND) zugspec=0; 
	else zugspec=((zfall+i*i*i-6*i*i)%zuf);
	zugspec+=zugbonus(legals[i],legals[i]+legalz[i],kil[i],dran,kp);
	makemovesuic(kil[i]);
	numhalbz++; ply++;
	if (rep>5) if (kil[i]>=24 && kil[i]<=28) 
	{ repfl=0;re1=0;re2=0;
	  for (j=BANF;j<BEND;j++) 
	  { re1-=Board[j]*j*3;re2+=Board[j]*(j-70)*(j-80); }
	  for (j=1;j<=rep;j++) 
	    if (reph1[j]==re1 && reph2[j]==re2) repfl++;
	  if (repfl>=1) { w=DRAWS; drw=0; }
	  if (repfl>=2 || rep>100) { w=DRAWS; drw=0; dfl2=1; }
	}                        /* Drawn by repitition/50 moves*/
	if (drw) 
	w=searchsuic(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
	SHOWB1
	if (i==0) 
	{ if (w<alpha) 
	 { alpha=SCHLECHT; beta=w;
	   if (drw)
	     w=searchsuic(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
	 }
	 else if (w>=beta) 
	 { alpha=w; beta=GUT;
	   if (drw)
	     w=searchsuic(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
	 }
	alpha=w; beta=alpha+1; 
	KopPV(0,legals[i],legalz[i]); bzug=i;
	HAUPT1
	}
	else 
	{ if (w>alpha) 
	 { maximum=alpha;alpha=w;beta=GUT;
	   if (drw)
	     w=searchsuic(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
	   if (w>maximum) 
	   { alpha=w;beta=alpha+1;bzug=i;
	     KopPV(0,legals[i],legalz[i]);
	HAUPT1
	     History[legals[i]][legalz[i]+legals[i]]++;
	   }
	 }
	}
	numhalbz-=1; ply--; takebacksuic(); 
	if (abbruch>=1) {legalanzahl=i;break;}
	}
	}
	maximum=alpha;
	if (legalanzahl<=0) {bzug=0;maximum=walt;}
	stellungswert=maximum;
	if (legalanzahl==0 && zugtiefe>STARTDEPTH)
	{ zug=hzug;szug=hszug;kllz=hk;
	}
	else
	{ zug=legalz[bzug];
	szug=legals[bzug];
	kllz=kil[bzug];
	hszug=szug;hzug=zug;hk=kllz;
	}
	ezug=szug+zug;
	balt=bzug;walt=stellungswert;
	if (abbruch>=1) break;
	{ if (legalanzahl==ONEDEBUG) { kib=0;break; }
	ende=myget();
	if (ende-start>=timeformove/DEEPER) {abbruch=1;break;} 
	}
	if (stellungswert>29000) break;
	}
	if (abbruch==0) zugtiefe--;
	ende=myget();
	stim=stim+ende-start;
	wold=stellungswert;
	if (kib==1) 
	{ sprintf(wh,"whisper %g (%d/%d)%c\n",1.0*wold/100,zugtiefe
	,endtiefe,(abbruch==2 ? '~' : '#')); 
	if (stellungswert>29000)
	printf("kibitz Forced win in %d moves\n",(102-stellungswert%100)/2);
	}
	if (dfl2==1 && stellungswert==DRAWS) 
	{ if (rep>99) dr50=1;
	else drr=1; 
	printf("draw\n"); fflush(stdout);
	}
if (kib)
{ if (resign)
  { if (otim>7500 && stellungswert<=-29990)
    { stellungswert=-30001; }
  }
  if (CRBOOK>0) {
   StartZug[numhalbz]=szug; EndZug[numhalbz]=ezug;
   if (stellungswert>29000 && EDFLAG==0 && (ratdiff>=0)) createbook(dran);
   if (stellungswert<-29000 && EDFLAG==0 && CRBOOK>1) createbook(dran*WECHSEL);
  }
  if (stellungswert<=-30001)
  { printf("resign\n");
    printf(compfarbe==1 ? "Black Wins!\n":"White Wins!\n");
    fflush(stdout); eingzug(0,0); }
}

	}

	int gensuic(int *lsu,int *lzu,int *kilu,int schach)
	{
	int ls[MAXMGL],lz[MAXMGL],kil[MAXMGL];
	int anz=0,dfeld,rfl,reihe,neben,tausch,ffl,FK2=FK,inc=1;
	int i,j,k,l,n,w,w2,fig,szugvar,bewpoint,kpos,janus;
	int reichw,bewbauer,diagonal,fessel[8],fesselr[8],anzfes;
	int leghilf=0,sflag=0;
	dfeld=1+dran; anz=0; anzfes=0;
	FK2++;

for (i=BANF;i<BEND;i++) 
{ w=Board[i];
if (w!=RAND) 
{ w*=dran;
if (w>0) 
{
fig=FP;
if (w==SWN) fig=FN;
 else if (w==SWB) fig=FB;
  else if (w==SWR) fig=FR;
   else if (w==SWQ) fig=FQ;
    else if (w==SWK) fig=FK; 
if (fig==FP)                  /* Pawns */
{ reihe=(int)(i/10);
  if (reihe==siebtereihe[dfeld]) tausch=1;
      else tausch=0;
  if (reihe==zweitereihe[dfeld]) bewbauer=2;
      else bewbauer=1; 
  if (reihe==fuenftereihe[dfeld])
    if (EnPassant[numhalbz-1]>0) 
    { neben=EndZug[numhalbz-1]-i;
      if ((neben==1) || (neben==-1))
      { ls[anz]=i,lz[anz]=10*dran+neben;kil[anz]=11;inc=1;
	anz+=inc;
      }
    }   
  for (j=0;j<2;j++)
  { diagonal=dran*beweg[j];
    szugvar=i+diagonal; 
    w2=Board[szugvar];
    if (w2!=RAND) 
    { w2*=dran;
      if (w2<0)
      { if (tausch==0)
	{ ls[anz]=i; lz[anz]=diagonal; kil[anz]=0; 
	  anz++; 
	}
	else
	{ for (l=FN;l<FK2;l++)
	  { ls[anz]=i; lz[anz]=diagonal; kil[anz]=11+l*2;
	    anz++;  
	  }
	}
      }
    }
  }
  diagonal=dran*beweg[2];
  szugvar=i;
  for (k=0;k<bewbauer;k++)
  { szugvar=szugvar+diagonal;
    w2=Board[szugvar];
    if (w2!=RAND) 
    { if (w2!=0) break;
      else 
      { if (tausch==0)
	{ ls[anz]=i;lz[anz]=diagonal*(k+1);kil[anz]=23;
	  anz++; 
	}
	else
	{ for (l=FN;l<FK2;l++)
	  { ls[anz]=i;lz[anz]=diagonal*(k+1);kil[anz]=10+l*2;
	    anz++;
	  } 
	}
      }
    }
  }
}
else   /* other figures */
{ for (j=0;j<bewanz[fig];j++)
  { szugvar=i;
    bewpoint=beweg[fig*8+j];
    reichw=bewfla[fig];
    for (k=1;k<=reichw;k++)
    { szugvar=szugvar+bewpoint; 
      w2=Board[szugvar];
      if (w2==RAND) break;
      else 
      { w2*=dran;
	if (w2>0) break;
	else 
	{ ls[anz]=i;
	  lz[anz]=k*bewpoint;
	  if (w2<0) { kil[anz]=fig; k=9; } 
	  else kil[anz]=fig+23;
                  anz++; 
        }
      }
    }
  }
       }
     }
   }          
 }
  for (i=0;i<anz;i++) 
      if (kil[i]<12 || kil[i]==13 || kil[i]==15 || kil[i]==17 || kil[i]==19 || kil[i]==21) { sflag=1;break; }
  if (sflag==1)
    {
  for (i=0;i<anz;i++) if (kil[i]<12 ||  kil[i]==13 || kil[i]==15 || kil[i]==17 || kil[i]==19 || kil[i]==21)
      { kil[leghilf]=kil[i];
        ls[leghilf]=ls[i];
        lz[leghilf]=lz[i];
        leghilf++;
      }
    anz=leghilf;
    }
  j=0;for (i=0;i<anz;i++)
  { 
   if (ls[i]==Hvon[0][ply]) if (lz[i]==Hnach[0][ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
  }
  for (i=0;i<anz;i++)
  { 
   if (kil[i]>=0) 
   { if (ls[i]==Kvon[ply]) if (lz[i]==Knach[ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
   }
  }
  for (i=0;i<anz;i++)
  { 
   if (kil[i]>=0) 
   { if (ls[i]==K2von[ply]) if (lz[i]==K2nach[ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
   }
  }
  for (i=0;i<anz;i++)
  { 
   if (kil[i]>=0) 
   { if (ls[i]==K3von[ply]) if (lz[i]==K3nach[ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
   }
  }
  for (i=0;i<anz;i++)
  { 
   if (kil[i]>=0) 
   { if (kil[i]<22)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;}
   }
  }
  if (sflag==1) return anz;
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
   { if (History[ls[i]][ls[i]+lz[i]]>1)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;}
   }
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];j++;}
  }
  return anz;
}

void makemovesuic(int kilflag)
{
 KillFlag[numhalbz]=kilflag;
  {
   StartZug[numhalbz]=szug;
   EndZug[numhalbz]=ezug;
   SchlZug[numhalbz][0]=Board[ezug];
   if (kilflag<7)
   { material-=Board[ezug];
     piecec[1-dran]--;
   }
     Board[ezug]=Board[szug];
   if (kilflag<22) if (kilflag>11)
     { material-=Board[ezug];
       if (SchlZug[numhalbz][0]!=LEER)
       {
         material-=SchlZug[numhalbz][0];
         piecec[1-dran]--;
       }
       Board[ezug]=dran*suicmat(Figur[(kilflag-10)/2]); 
       material+=Board[ezug];
      }
   if (kilflag==23)
   { if (zug==dran*20) EnPassant[numhalbz]=szug; }
   else    
     if (Board[szug]==dran*SWK) { koenig[dran+1]=ezug; }
   Board[szug]=LEER;
   if (kilflag==11)
     { material-=Board[ezug-dran*10];
       Board[ezug-dran*10]=LEER; 
       SchlZug[numhalbz][0]=dran*SBP; 
       piecec[1-dran]--;
     }
  }
}

void takebacksuic(void)
{ int kilflag;
  kilflag=KillFlag[numhalbz];
  if ( Rochade[numhalbz]==0 )
  {
   EnPassant[numhalbz]=0;
   szug=StartZug[numhalbz];
   ezug=EndZug[numhalbz];
     Board[szug]=Board[ezug];
   if (kilflag>11) if (kilflag<23) 
   { material-=Board[szug];
     Board[szug]=dran*SWP;
     material+=Board[szug];
     if (SchlZug[numhalbz][0]!=LEER)
     {
       material+=SchlZug[numhalbz][0];
       piecec[1-dran]++;
     }
   }
   if (Board[ezug]==dran*SWK)
     koenig[dran+1]=szug;
   Board[ezug]=SchlZug[numhalbz][0];
   if (kilflag==11)
   { 
     Board[ezug]=LEER; 
     Board[ezug-dran*10]=dran*SBP; 
     material+=dran*SBP;
     piecec[1-dran]++;
   } 
   if (kilflag<7)
   { material+=Board[ezug];
     piecec[1-dran]++;
   }
  }
  else
  {
   rochiert[dran+1]=0;
   Rochade[numhalbz]=0;
   szug=StartZug[numhalbz];
   koenig[dran+1]=szug;
   ezug=EndZug[numhalbz];
   Board[szug]=Board[ezug];
   Board[ezug]=LEER;
   Board[rochturm[SchlZug[numhalbz][0]-30]]=Board[szug+rochdir[SchlZug[numhalbz][0]-30]];
   Board[szug+rochdir[SchlZug[numhalbz][0]-30]]=LEER; 
   }
}

void transboard()
{ int i,j;
  for (i=21;i<=91;i+=10)
    for (j=i;j<i+8;j++) Board[j]=suicmat(Board[j]);

}


int searchsuic(int alpha,int beta,int dist,int anz,int anz2,int kfl)
{
  int i,w,schfl=-1,sfl2,zugt;
  int maximum=SCHLECHT;int legalanzahl,wert;
  int legals[MAXMGL];
  int legalz[MAXMGL];
  int kil[MAXMGL]; /* REK */
  if (permbrain==0)
    { if (nm-restnode>0)
      { ende=myget();
        restnode+=NODEC;
        if (ende-start>=timeformove && zugtiefe>STARTDEPTH) abbruch=2;
      } 
    }
  if (abbruch==2) return SCHLECHT; 
  dran*=WECHSEL;
  Htief[ply]=ply;
  if (ply>endtiefe) endtiefe=ply;
  legalanzahl=gensuic(&legals[0],&legalz[0],&kil[0],-1);
  zugt=zugtiefe;
{ if (legalanzahl==0) 
  { if (piecec[1+dran]>piecec[1-dran]) maximum=SCHLECHT+ply;
    else { if (piecec[1+dran]<piecec[1-dran]) maximum=GUT-ply;
           else maximum=0; }
  }                   
}

  for (i=0;i<legalanzahl;i++)
  {
    szug=legals[i]; zug=legalz[i]; sfl2=0; ezug=szug+zug;
    makemovesuic(kil[i]); numhalbz++; ply++;
    if (piecec[1-dran]==0) 
    { w=SCHLECHT+ply;
      nm++;
    }
    else
    {
    if (kfl<22 || kil[i]<22) if (ply<maxtiefe) sfl2=1;
    if (dist<=1 && sfl2==0)
    {
        w=evalsuic(legalanzahl,anz); 
        Htief[ply]=ply;
        nm++;
    }
    else
    { 
        w=searchsuic(-beta,-alpha,dist-1,legalanzahl,anz,kil[i]);
SHOWC1
    }
    }
    numhalbz--; ply--; takebacksuic(); 
    if (w>maximum) {maximum=w;KopPV(ply,legals[i],legalz[i]);
       if (w>=beta) {if (i>0) {K3von[ply]=K2von[ply];K3nach[ply]=K2nach[ply];K2von[ply]=Kvon[ply];K2nach[ply]=Knach[ply];Kvon[ply]=legals[i];Knach[ply]=legalz[i];History[legals[i]][legalz[i]+legals[i]]++;}break;}
       if (w>alpha) {alpha=w;}}
    
  }
  dran*=WECHSEL;
  maximum*=WECHSEL;
  return maximum;  
}

int evalsuic(int anz,int anz2)
{
  int wert;
  wert=-material;
 wert+=zugspec;
 wert*=dran;
 return (wert+MOBILS*(anz-anz2));
}

int suicmat(int s)
{ if (s==WP) return SWP;if (s==BP) return (SBP);
  if (s==WR) return SWR;if (s==BR) return (SBR);
  if (s==WB) return SWB;if (s==BB) return (SBB);
  if (s==WN) return SWN;if (s==BN) return (SBN);
  if (s==WQ) return SWQ;if (s==BQ) return (SBQ);
  if (s==WK) return SWK;if (s==BK) return (SBK);
  if (s==RAND) return RAND;return LEER;
}

