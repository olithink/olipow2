/* OliPow Version 2.2d (c) Losers Part */

void thinkloser(void)
{
int stellungswert=0,absmat=-LWK,legalanzahl=0,bzug=0,dfl2=0;
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
absmat+=LWK;
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
     maxtiefe=zugtiefe+LOSERSWEIT;
  maxtiefe=maxtiefe+6-absmat/2; 
  legalanzahl=genloser(&legals[0],&legalz[0],&kil[0],-1);
  if (legalanzahl==0) matt();
  { if (piecec[2]==0 || piecec[0]==0) matt(); }
  if (legalanzahl>ONEDEBUG || permbrain==1) 
  { for (i=0;i<legalanzahl;i++)
    {
	szug=legals[i]; 
	zug=legalz[i];
	ezug=szug+zug; drw=1;
	if (ZUFALL==0 || ner>ZUFEND) zugspec=0; 
	else zugspec=((zfall+i*i*i-6*i*i)%zuf);
	zugspec+=zugbonus(legals[i],legals[i]+legalz[i],kil[i],dran,kp);
	makemoveloser(kil[i]);
	numhalbz++; ply++;
	if (rep>5) if (kil[i]>=24 && kil[i]<=28) 
	{ repfl=0;re1=0;re2=0;
	  for (j=BANF;j<BEND;j++) 
	  { re1-=Board[j]*j*3;re2+=Board[j]*(j-70)*(j-80); }
	  for (j=1;j<=rep;j++) 
	    if (reph1[j]==re1 && reph2[j]==re2) repfl++;
	  if (repfl>=1) { w=DRAWL; drw=0; }
	  if (repfl>=2 || rep>100) { w=DRAWL; drw=0; dfl2=1; }
	}                        /* Drawn by repitition/50 moves*/
	if (drw) 
	w=searchloser(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
	SHOWB1
	if (i==0) 
	{ if (w<alpha) 
	 { alpha=SCHLECHT; beta=w;
	   if (drw)
	     w=searchloser(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
	 }
	 else if (w>=beta) 
	 { alpha=w; beta=GUT;
	   if (drw)
	     w=searchloser(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
	 }
	alpha=w; beta=alpha+1; 
	KopPV(0,legals[i],legalz[i]); bzug=i;
	HAUPT1
	}
	else 
	{ if (w>alpha) 
	 { maximum=alpha;alpha=w;beta=GUT;
	   if (drw)
	     w=searchloser(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
	   if (w>maximum) 
	   { alpha=w;beta=alpha+1;bzug=i;
	     KopPV(0,legals[i],legalz[i]);
	HAUPT1
	     History[legals[i]][legalz[i]+legals[i]]++;
	   }
	 }
	}
	numhalbz-=1; ply--; takebackloser(); 
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
	if (dfl2==1 && stellungswert==DRAWL) 
	{ if (rep>99) dr50=1;
	else drr=1; 
	printf("draw\n"); fflush(stdout);
	}

if (kib)
{ if (resign)
  { if (otim>7500 && stellungswert<=-29000)
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

	int genloser(int *lsu,int *lzu,int *kilu,int schach)
	{
	int ls[MAXMGL],lz[MAXMGL],kil[MAXMGL];
	int anz=0,dfeld,rfl,reihe,neben,tausch,ffl,FK2=FK,inc=1;
	int i,j,k,l,n,w,w2,fig,szugvar,bewpoint,kpos,janus;
	int reichw,bewbauer,diagonal,fessel[8],fesselr[8],anzfes;
	int leghilf=0,sflag=0;
	dfeld=1+dran; anz=0; anzfes=0;
{ kpos=koenig[dfeld];
schach=sattacked(kpos);
Schach[numhalbz]=schach;
if (schach==0)
for (i=0;i<8;i++)            /* bounded */
{ diagonal=stern[i]; ffl=0;
for(j=1;j<9;j++) 
{  w=Board[kpos+j*diagonal];
if (w==RAND) { ffl=0;break; }
w*=dran;
if (w>0) 
  if (ffl==0) ffl=kpos+j*diagonal;
  else { ffl=0;break; }
if (w<0) 
{ 
 if (w==LBQ || w==lstern[i]) break;
 else { ffl=0;break; } 
}
}
if (ffl>0) { fessel[anzfes]=ffl; 
	 fesselr[anzfes]=abs(diagonal);
	 anzfes++; }
} 
}

for (i=BANF;i<BEND;i++) 
{ w=Board[i];
if (w!=RAND) 
{ w*=dran;
if (w>0) 
{
fig=FP;
if (w==LWN) fig=FN;
 else if (w==LWB) fig=FB;
  else if (w==LWR) fig=FR;
   else if (w==LWQ) fig=FQ;
    else if (w==LWK) fig=FK; 
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
	{ 
	   if (schach!=0)
	      if (sistschach(ls[anz],lz[anz],kil[anz])!=0) inc=0;
	    for (n=0;n<anzfes;n++)
	      if (ls[anz]==fessel[n] && abs(lz[anz])!=fesselr[n])
		{ inc=0; break; }
	  
	}
	anz+=inc;
      }
    }   
  for (j=0;j<2;j++)
  { diagonal=dran*beweg[j];
    szugvar=i+diagonal; 
    w2=Board[szugvar];
    { for (n=0;n<anzfes;n++) 
	if (i==fessel[n])
	  if (abs(diagonal)!=fesselr[n]) w2=RAND;
    }
    if (w2!=RAND) 
    { w2*=dran;
      if (w2<0)
      { if (tausch==0)
	{ ls[anz]=i; lz[anz]=diagonal; kil[anz]=0; 
	  { if (schach!=0)
	      if (sistschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
	  }
	  anz++; 
	}
	else
	{ for (l=FN;l<FK2;l++)
	  { ls[anz]=i; lz[anz]=diagonal; kil[anz]=11+l*2;
	    { if (schach!=0)
		if (sistschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
	    }
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
    { for (n=0;n<anzfes;n++)
	if (i==fessel[n])
	  if (abs(diagonal)!=fesselr[n]) w2=RAND;
    }
    if (w2!=RAND) 
    { if (w2!=0) break;
      else 
      { if (tausch==0)
	{ ls[anz]=i;lz[anz]=diagonal*(k+1);kil[anz]=23;
	  { if (schach!=0)
	      if (sistschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
	  }
	  anz++; 
	}
	else
	{ for (l=FN;l<FK2;l++)
	  { ls[anz]=i;lz[anz]=diagonal*(k+1);kil[anz]=10+l*2;
	    { if (schach!=0)
		if (sistschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
	    }
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
      { for (n=0;n<anzfes;n++)
	  if (i==fessel[n])
	    if (abs(bewpoint)!=fesselr[n]) w2=RAND;
      }
      if (w2==RAND) break;
      else 
      { w2*=dran;
	if (w2>0) break;
	else 
	{ ls[anz]=i;
	  lz[anz]=k*bewpoint;
	  if (w2<0) { kil[anz]=fig; k=9; } 
	  else kil[anz]=fig+23;
	  { if (schach!=0 || fig==FK)
	    {
              if (sistschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
            }
          }
                  anz++; 
        }
      }
    }
  }
      if (fig==FK)   /* CASTLE */
      { if (rochiert[dfeld]==0)  
        { rfl=0; 
          for (j=numhalbz-2;j>2;j-=2)
            if (StartZug[j]==rochkoen[dfeld]) { rfl=1;break; }
          if (rfl==0)
             for (j=dfeld;j<dfeld+2;j++)
             { rfl=0; 
               for (n=numhalbz-2;n>2;n-=2)
                 if (StartZug[n]==rochturm[j]) { rfl=1;break; }
               if (rfl==0)
               { rfl=0; 
                 for (k=rochchk1[j];k<=rochchk2[j];k++)
                  if (Board[k]!=lrochfeld[j][k-rochchk1[j]]) { rfl=1; break; }
                 if (rfl==0)
                   for (k=rochchk3[j];k<=rochchk4[j];k++)
                     if (sattacked(k)>0) {rfl=1; break;} 
                 if (rfl==0)
                 { ls[anz]=rochkoen[j];
                   lz[anz]=rochdir[j]*2;
                   kil[anz]=30+j; 
                   anz++; 
                 }
               }
             }
           }
         }       
       }
     }
   }          
 }
  for (i=0;i<anz;i++) 
      if (kil[i]<12 || kil[i]==13 || kil[i]==15 || kil[i]==17 || kil[i]==19) { sflag=1;break; }
  if (sflag==1)
    {
  for (i=0;i<anz;i++) if (kil[i]<12 ||  kil[i]==13 || kil[i]==15 || kil[i]==17 || kil[i]==19)
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

void makemoveloser(int kilflag)
{
 KillFlag[numhalbz]=kilflag;
 if ( kilflag < 30 )
  {
   StartZug[numhalbz]=szug;
   EndZug[numhalbz]=ezug;
   SchlZug[numhalbz][0]=Board[ezug];
   if (kilflag<7)
   { material-=Board[ezug];
     piecec[1-dran]--;
     if (Board[ezug]==dran*LBP)
     { pawnline[ezug % 10][1-dran]--;
       pawnc[1-dran]--;
       pawnrank[ezug / 10][1-dran]--; }
   }
     Board[ezug]=Board[szug];
   if (kilflag<22) if (kilflag>11)
     { material-=Board[ezug];
       if (SchlZug[numhalbz][0]!=LEER)
       {
         material-=SchlZug[numhalbz][0];
         piecec[1-dran]--;
       }
       Board[ezug]=dran*losermat(Figur[(kilflag-10)/2]); 
       material+=Board[ezug];
       pawnline[szug % 10][dran+1]--;
       pawnrank[szug / 10][dran+1]--; 
       pawnc[1+dran]--;
      }
   if (kilflag==0 || kilflag==23 || kilflag==11)
   {
     pawnrank[szug / 10][dran+1]--;
     pawnrank[ezug / 10][dran+1]++;
   }
   if (kilflag==23)
   { if (zug==dran*20) EnPassant[numhalbz]=szug; }
   else    
     if (Board[szug]==dran*LWK) { koenig[dran+1]=ezug; }
   Board[szug]=LEER;
   if (kilflag==11)
     { material-=Board[ezug-dran*10];
       Board[ezug-dran*10]=LEER; 
       SchlZug[numhalbz][0]=dran*LBP; 
       piecec[1-dran]--;
       pawnline[ezug % 10][1-dran]--;
       pawnrank[ezug / 10][1-dran]--; 
       pawnc[1-dran]--;
     }
   if (kilflag==0 || kilflag==11)
   {
     pawnline[szug % 10][dran+1]--;
     pawnline[ezug % 10][dran+1]++;
   }
  }
  else
  {
   StartZug[numhalbz]=szug;
   EndZug[numhalbz]=ezug;
   SchlZug[numhalbz][0]=kilflag;
   Board[ezug]=Board[szug];
   Board[szug]=LEER;
   Board[szug+rochdir[kilflag-30]]=Board[rochturm[kilflag-30]];
   Board[rochturm[kilflag-30]]=LEER;
   Rochade[numhalbz]=kilflag;
   koenig[dran+1]=ezug;
   rochiert[dran+1]=1;
  }
}

void takebackloser(void)
{ int kilflag;
  kilflag=KillFlag[numhalbz];
  if ( Rochade[numhalbz]==0 )
  {
   EnPassant[numhalbz]=0;
   szug=StartZug[numhalbz];
   ezug=EndZug[numhalbz];
   if (kilflag==0 || kilflag==11)
   {
     pawnline[szug % 10][dran+1]++;
     pawnline[ezug % 10][dran+1]--;
   }
     Board[szug]=Board[ezug];
   if (kilflag>11) if (kilflag<23) 
   { material-=Board[szug];
     Board[szug]=dran*LWP;
     material+=Board[szug];
     if (SchlZug[numhalbz][0]!=LEER)
     {
       material+=SchlZug[numhalbz][0];
       piecec[1-dran]++;
     }
     pawnline[szug % 10][dran+1]++;
     pawnrank[szug / 10][dran+1]++; 
     pawnc[dran+1]++;
   }
   if (kilflag==0 || kilflag==23 || kilflag==11)
   {
     pawnrank[szug / 10][dran+1]++;
     pawnrank[ezug / 10][dran+1]--;
   }
   if (Board[ezug]==dran*LWK)
     koenig[dran+1]=szug;
   Board[ezug]=SchlZug[numhalbz][0];
   if (kilflag==11)
   { 
     Board[ezug]=LEER; 
     Board[ezug-dran*10]=dran*LBP; 
     material+=dran*LBP;
     piecec[1-dran]++;
     pawnline[ezug % 10][1-dran]++;
     pawnrank[ezug / 10][1-dran]++;
     pawnc[1-dran]++;
   } 
   if (kilflag<7)
   { material+=Board[ezug];
     piecec[1-dran]++;
     if (Board[ezug]==dran*LBP)
     { pawnline[ezug % 10][1-dran]++;
       pawnc[1-dran]++;
       pawnrank[ezug / 10][1-dran]++; }
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

void transboardloser()
{ int i,j;
  for (i=21;i<=91;i+=10)
    for (j=i;j<i+8;j++) Board[j]=losermat(Board[j]);
}

int searchloser(int alpha,int beta,int dist,int anz,int anz2,int kfl)
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
  legalanzahl=genloser(&legals[0],&legalz[0],&kil[0],-1);
  zugt=zugtiefe;
{ if (legalanzahl==0) maximum=GUT-ply; }

  for (i=0;i<legalanzahl;i++)
  {
    szug=legals[i]; zug=legalz[i]; sfl2=0; ezug=szug+zug;
    makemoveloser(kil[i]); numhalbz++; ply++;
    if (piecec[1-dran]==0) 
    { w=SCHLECHT+ply;
      nm++;
    }
    else
    {
    if (kfl<22 || kil[i]<22) if (ply<maxtiefe) sfl2=1;
    if (dist<=1 && sfl2==0)
    {
        w=evalloser(legalanzahl,anz); 
        Htief[ply]=ply;
        nm++;
    }
    else
    { 
        w=searchloser(-beta,-alpha,dist-1,legalanzahl,anz,kil[i]);
SHOWC1
    }
    }
    numhalbz--; ply--; takebackloser(); 
    if (w>maximum) {maximum=w;KopPV(ply,legals[i],legalz[i]);
       if (w>=beta) {if (i>0) {K3von[ply]=K2von[ply];K3nach[ply]=K2nach[ply];K2von[ply]=Kvon[ply];K2nach[ply]=Knach[ply];Kvon[ply]=legals[i];Knach[ply]=legalz[i];History[legals[i]][legalz[i]+legals[i]]++;}break;}
       if (w>alpha) {alpha=w;}}
    
  }
  dran*=WECHSEL;
  maximum*=WECHSEL;
  return maximum;  
}

int sattacked(int feld)
{
  int w2,szugvar,f,b,bewpoint,j,i,reichw,k;
  if (Board[feld+9*dran]==dran*LBP) return 1;
  if (Board[feld+11*dran]==dran*LBP) return 1;
  for (i=0;i<8;i++) if (Board[feld+beweg[8+i]]==dran*LBN) return 1;
  for (i=0;i<8;i++)
  { szugvar=feld;
    for (k=1;k<8;k++)
    { szugvar+=stern[i];
      w2=Board[szugvar];
      if (w2==RAND) break;
      else
      { if (w2!=0)
        { if (w2==dran*LBQ) return 1;
          if (w2==dran*LBK) if (k==1) return 1;
          if (w2==dran*lstern[i]) return 1;
          break;
        }
      }
    }
  }
return 0;
}

int sistschach(int s,int z,int k)
{
 int sch; numhalbz++;
 szug=s; zug=z; ezug=szug+zug;
 makemoveloser(k);
 sch=sattacked(koenig[dran+1]);
 takebackloser();
 numhalbz--; return sch;
}

int evalloser(int anz,int anz2)
{
  int wert;
  wert=-material;
{ int i,j,d,e,ds,dr,v;
  ds=0;dr=0;
  for (j=1;j<10;j++)
  { if (pawnline[j][0]==1) ds++;
    else
    { if (pawnline[j][0]>1)
      { wert+=LDOPPEL*(pawnline[j][0]-1); ds++; }
      else
      { if (ds==1) 
        { if (compfarbe==-1)
          {
            wert+=LISOLANI; 
            if (pawnline[j-1][2]>0) wert+=BLOCKED;
          }
        }
        ds=0;
      }
    }
    if (pawnline[j][2]==1) dr++;
    else
    { if (pawnline[j][2]>1)
      { wert-=LDOPPEL*(pawnline[j][2]-1); dr++; }
      else
      { if (dr==1) 
       { if (compfarbe==1)
          {
            wert-=LISOLANI; 
            if (pawnline[j-1][0]>0) wert-=BLOCKED;
          }
       }
       dr=0;
      }
    }
  }
  wert+=pawnrank[8][2]*LPT7;
  wert+=pawnrank[7][2]*LPT6;
  wert-=pawnrank[4][0]*LPT6;
  wert-=pawnrank[3][0]*LPT7;

  if (pawnc[0]>0)
    wert+=BPIEC/(1+piecec[0]-pawnc[0]); 
  if (pawnc[2]>0)
    wert-=BPIEC/(1+piecec[2]-pawnc[2]); 
}
 wert+=zugspec;
 wert*=dran;
 return (wert+MOBILS*(anz-anz2));
}

int losermat(int s)
{ if (s==WP) return LWP;if (s==BP) return (LBP);
  if (s==WR) return LWR;if (s==BR) return (LBR);
  if (s==WB) return LWB;if (s==BB) return (LBB);
  if (s==WN) return LWN;if (s==BN) return (LBN);
  if (s==WQ) return LWQ;if (s==BQ) return (LBQ);
  if (s==WK) return LWK;if (s==BK) return (LBK);
  if (s==RAND) return RAND; return LEER;
}

