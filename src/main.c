#if defined(POWA)
#include "main.h.powa"
#elif defined(POWB)
#include "main.h.powb"
#elif defined(POWC)
#include "main.h.powc"
#elif defined(POWD)
#include "main.h.powd"
#elif defined(DISASTER)
#include "main.h.disas"
#else
#include "main.h"   /* OliPow Version 2.2e (c) Oliver Brausch, 27.August.97 */
#endif

#include "suic.c"
#include "loser.c"
#include "atom.c"


void main(int argc, char **argv)
{
  initchess(argc,argv);
  if (--prompt==0)
    printf("OliPow - Chess\n");printboard();
  while (-1)
  {
   debug=0;
   numhalbz++;
   if (dran!=compfarbe)
     {
        eingzug(argc,argv);
	if (debug==0) 
        { if (type==TYPES)
           makemovesuic(kllz);
          if (type==TYPEL)
           makemoveloser(kllz);
          if (type==TYPEA)
           makemoveatom(kllz);
          if (type==TYPEN)
           makemove(kllz);
          heintrag(kllz);
        }
        if (numhalbz<=2 && debug==2 && opening==1) ladebuch();
      }
   else
      {
        if (opening==1) buch();
        if (opening==0)
        { if (type==TYPES)
            thinksuic();
          if (type==TYPEL)
            thinkloser();
          if (type==TYPEA)
            thinkatom();
          if (type==TYPEN)
            think();
        }
	ausgzug();
         if (type==TYPES)
          makemovesuic(kllz);
         if (type==TYPEA)
          makemoveatom(kllz);
         if (type==TYPEL)
          makemoveloser(kllz);
         if (type==TYPEN)
          makemove(kllz);
        heintrag(kllz);
     }
     dran*=WECHSEL;
     if (debug!=2) printboard(); 
  }
}

void heintrag(int k)
{ int i;
  if (k<24 || k>28) rep=0;
  reph1[++rep]=0;reph2[rep]=0;
  for (i=BANF;i<BEND;i++) { reph1[rep]-=Board[i]*i*3;
                            reph2[rep]+=Board[i]*(i-70)*(i-80); }
  return; 
}

void initchess(int argc, char **argv)
{ int i,j;
  dran=1; numhalbz=0; opening=OPENBIB; timeformove=DEFAULTIME;
  for (i=1;i<argc;i++)
  { if (argv[i][0]=='-' && argv[i][1]=='c')
    { sscanf(argv[++i],"%d",&CRBOOK);
      if (CRBOOK>0) opening=1; }
    if (argv[i][0]=='-' && argv[i][1]=='t')
    { sscanf(argv[++i],"%d",&j);
      if (j>0) timeformove=j*100; }
    if (argv[i][0]=='-' && argv[i][1]=='a') type=TYPEA;
    if (argv[i][0]=='-' && argv[i][1]=='s') type=TYPES;
    if (argv[i][0]=='-' && argv[i][1]=='l') type=TYPEL;
    if (argv[i][0]=='-' && argv[i][1]=='d') xboard=0;
    if (argv[i][0]=='-' && argv[i][1]=='p') showpv=1;
    if (argv[i][0]=='-' && argv[i][1]=='x') CHECK=1;
    if (argv[i][0]=='-' && argv[i][1]=='n') opening=0;
    if (argv[i][0]=='-' && argv[i][1]=='r') resign=1;
  }
  srand(time(NULL));if (opening!=0) ladebuch();
  for (i=0;i<BDIM;i++) { Board[i]=GBoard[i];
    for (j=0;j<BDIM;j++) History[i][j]=0; }
  for (i=0;i<MAXTIEF;i++) { EnPassant[i]=0;Rochade[i]=0;
                            Hvon[0][i]=0;Hnach[0][i]=0;
                            Kvon[i]=0;Knach[i]=0;K2von[i]=0;
                            K2nach[i]=0; }
  for (i=0;i<10;i++)
    for (j=0;j<3;j++) { pawnline[i][j]=1; pawnrank[i][j]=0; }
  pawnline[9][0]=0;pawnline[9][2]=0;
  pawnrank[3][2]=8;pawnrank[8][0]=8;
  piecec[0]=piecec[2]=16;
  pawnc[0]=pawnc[2]=8;
  if (type==TYPEL) { piecec[0]--;piecec[2]--;transboardloser();}
  if (type==TYPES) transboard();
}
            
void editboard(void)
{ char s[60];
  int setzfarbe,piece=0;
  rochiert[0]=rochiert[2]=ROCHEDIT;
  EDFLAG=1;
  numhalbz=20;
  setzfarbe=1;
  clearboard();
  material=opening=0;
  for (;;) {
    gets(s); piece=0;
    if (s[0]=='c') { setzfarbe*=WECHSEL; }
    if (s[0]=='.') { if (material==0) 
                     { ner=-5;rochiert[0]=rochiert[2]=0; } 
                     if (type==TYPES) transboard();
                     if (type==TYPEL) transboardloser();
                     return;
                   }
    if (s[0]=='P') { piece=WP*setzfarbe; 
                     pawnline[s[1]-96][setzfarbe+1]++; 
                     pawnrank[s[2]-47][setzfarbe+1]++; }
    if (s[0]=='B') piece=WB*setzfarbe;
    if (s[0]=='N') piece=WN*setzfarbe;
    if (s[0]=='R') piece=WR*setzfarbe;
    if (s[0]=='Q') piece=WQ*setzfarbe;
    if (s[0]=='K') { piece=WK*setzfarbe;
                     koenig[1+setzfarbe]=(s[1]-96)+(s[2]-47)*10; 
                   }
    if (piece!=0)
    {
      piecec[setzfarbe+1]++;
      Board[(s[1]-96)+(s[2]-47)*10]=piece;
      ner=ZUFEND;
      if (type==TYPES)
        material+=suicmat(piece);
      else if (type==TYPEL)
             material+=losermat(piece);
           else
             material+=piece;
    }
  }
}
  
void clearboard(void)
{ int i,j;
  piecec[0]=piecec[2]=0;
  for (i=21;i<=91;i+=10)
    for (j=i;j<i+8;j++) Board[j]=LEER;
  for (i=0;i<9;i++) 
    for (j=0;j<3;j++) { pawnline[i][j]=0; pawnrank[i][j]=0; }
}

void ladebuch(void)
{ FILE *fp;
  signed char d;
  int i,j,st=0;
if (type==TYPEA)  /* mini Atomic book 1. Nf3/h3 1...f6 !*/
{ 
  if (compfarbe==-1) 
  { Of[0]=1; Of[1]=1; st=2;
    Os[1][0]=Os[1][1]=27; Oz[1][0]=19;Oz[1][1]=21;
    Os[2][0]=Os[2][1]=86; Oz[2][0]=Oz[2][1]=-10;
  }
  else { Of[0]=0;Of[1]=0; }
}
{ if (compfarbe==-1) { fp=fopen(blackbook[type],"rb"); NUMOPEN=NUMOPENB; }
                else { fp=fopen(whitebook[type],"rb"); NUMOPEN=NUMOPENW; }
}
  for (i=st;i<NUMOPEN;i++)
  { if (feof(fp)) { NUMOPEN=i-1;break; }
    for (j=1;j<=60;j++)
      { fread((char *)&d,1,sizeof(d),fp);Os[j][i]=(signed char)d;
        fread((char *)&d,1,sizeof(d),fp);Oz[j][i]=(signed char)d; 
  }                                      Of[i]=1; }
  fclose(fp); 
}
        
void matt(void)
{ 
  if (type==TYPEA) 
  { if (Board[koenig[0]]==LEER) printf("White mates!\n"); else
    printf(Board[koenig[2]]==LEER ? "Black mates!\n":"Drawn by Stalemate!\n");
  }
  if (type==TYPES || type==TYPEL)
  { if (piecec[2]==piecec[0]) printf("Drawn!\n");
    else printf(dran==1 ? "White wins!\n":"Black wins!\n");
  }
  if (type==TYPEN)
  { if (attacked(koenig[dran+1])==0) printf("Drawn by Stalemate!\n");
    else printf(dran==1 ? "Black mates!\n":"White mates!\n");
  }
  fflush(stdout); eingzug(1,0); 
}

void controltime(int t)
{   int h;
    if (type==TYPES)
    { h=(NMATCH/2-numhalbz); if (h<NEND/2) h=NEND/2; }
    else 
    { h=(NMATCH-numhalbz); if (h<NEND) h=NEND; }
    t=t-TIMEBUFFER; if (t<1) t=1;
    timeformove=t/h; if (t<2) pawnstorm=6*PAWNS; 
}

int myget(void)
{
#ifdef UNIX
  gettimeofday (&tv, NULL);
  return(tv.tv_sec*100+(tv.tv_usec/10000));
#else
  ftime(&tv);
  return(tv.time*100+tv.millitm/10);
#endif
}

void buch(void)
{ int i,j=0,anz,mgl[NUMOPENW];
  int legals[MAXMGL],legalz[MAXMGL],kil[MAXMGL];
  if (type==TYPES)
    anz=gensuic(&legals[0],&legalz[0],&kil[0],-1);
  if (type==TYPEL)
    anz=genloser(&legals[0],&legalz[0],&kil[0],-1);
  if (type==TYPEA)
    anz=genatom(&legals[0],&legalz[0],&kil[0],-1);
  if (type==TYPEN)
    anz=legalezuege(&legals[0],&legalz[0],&kil[0],-1);
  for (i=0;i<NUMOPEN;i++) 
  { if (Of[i]==1) { mgl[j]=i;j++;ezug=szug+zug; } }
  if (j==0) opening=0;
  else 
  { j=abs((int)(rand())) % j;
    szug=Os[numhalbz][mgl[j]];
    zug=Oz[numhalbz][mgl[j]];
    if (szug==127) { opening=0;return; }
    for (i=0;i<NUMOPEN;i++)
      if (Os[numhalbz][i]!=szug || Oz[numhalbz][i]!=zug) Of[i]=0;
    kllz=0;
    for (i=0;i<anz;i++)
      if ((legals[i]==szug) && (legalz[i]==zug)) { kllz=kil[i];break; }
  }             
}

void think(void)
{
  int stellungswert=0,absmat=-WK,legalanzahl=0,bzug=0,dfl2=0;
  int alpha=SCHLECHT,beta,maximum,drw,startd;
  int i,j,w=0,d,kp,zfall=0,re1,re2,repfl=0,zuf=ZUFALL;
  int legals[MAXMGL],legalz[MAXMGL],kil[MAXMGL];

  nm=0;abbruch=0;ply=0;endtiefe=1;kib=1;
  restnode=NODEC;
  if (type!=TYPEN) zuf*=4;
  altmat=material;balt=0;walt=wold;d=dran+1;ner++;
  start=myget();
  for (i=21;i<=91;i+=10)
    for (j=i;j<i+8;j++) 
      if (dran*Board[j]<WP) absmat-=dran*Board[j];
  if (absmat<ABSMATT) { endspiel=1;pawnstorm=3*PAWNS; }
  kp=koenig[d];
  if (ZUFALL>=1 && numhalbz<40) zfall=(int)(12347*rand());
  for (i=0;i<MAXTIEF-2;i++) 
  { Hvon[0][i]=Hvon[0][i+2]; Hnach[0][i]=Hnach[0][i+2];
    Kvon[i]=Kvon[i+2]; Knach[i]=Knach[i+2];
    K2von[i]=K2von[i+2]; K2nach[i]=K2nach[i+2];
  }
  for (i=0;i<BDIM;i++) 
    for (j=0;j<BDIM;j++) History[i][j]=0;

  for (zugtiefe=STARTDEPTH;zugtiefe<=maxt;zugtiefe++)
  { 
    Htief[ply]=ply;
    if (zugtiefe==STARTDEPTH) { alpha=SCHLECHT;beta=GUT; } 
    else { beta=alpha+WIND;alpha-=WIND; }
    legalanzahl=legalezuege(&legals[0],&legalz[0],&kil[0],-1);

    if (legalanzahl==0) matt();

  if (legalanzahl>ONEDEBUG) 
  { for (i=0;i<legalanzahl;i++)
    { szug=legals[i]; 
      zug=legalz[i];
      ezug=szug+zug; drw=1;
      if (ZUFALL==0 || ner>ZUFEND) zugspec=0; 
      else zugspec=((zfall+i*i*i-6*i*i)%zuf);
      zugspec+=zugbonus(legals[i],legals[i]+legalz[i],kil[i],dran,kp);
      makemove(kil[i]);
      numhalbz++; ply++;
      if (rep>5) if (kil[i]>=24 && kil[i]<=28) 
        { repfl=0;re1=0;re2=0;
          for (j=BANF;j<BEND;j++) 
          { re1-=Board[j]*j*3;
            re2+=Board[j]*(j-70)*(j-80); 
          }
          for (j=1;j<=rep;j++) 
            if (reph1[j]==re1 && reph2[j]==re2) repfl++;
          if (repfl>=1) { w=DRAW; drw=0; }
          if (repfl>=2 || rep>100) { w=DRAW; drw=0; dfl2=1; }
        }                        /* Drawn by repitition/50 moves*/
      if (drw) 
        w=-search(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
SHOWB1
      if (i==0 && abbruch==0) 
       { if (w<alpha) 
         { alpha=SCHLECHT; beta=w;
           if (drw)
             w=-search(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]); }
         else if (w>=beta) 
         { alpha=w; beta=GUT;
           if (drw)
             w=-search(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
         }
       alpha=w; beta=alpha+1; 
       KopPV(0,legals[i],legalz[i]); bzug=i;
HAUPT1
       }
       else 
       { if (w>alpha) 
         { maximum=alpha;alpha=w;beta=GUT;
           if (drw)
             w=-search(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
           if (w>maximum) 
           { alpha=w;beta=alpha+1;bzug=i;
             KopPV(0,legals[i],legalz[i]);
HAUPT1
             History[legals[i]][legalz[i]+legals[i]]+=zugtiefe;
           }
         }
       }
      numhalbz--; ply--; takeback(); 
      if (abbruch>=1) {legalanzahl=i;break;}
    }
  }
  maximum=alpha;
  if (legalanzahl<=0) {bzug=0;maximum=walt;}
SHOWA1
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
   balt=bzug; walt=stellungswert;
   if (abbruch>=1) break;
   if (legalanzahl==ONEDEBUG) { kib=0;break; }
   ende=myget();
   if (ende-start>=timeformove/DEEPER) {abbruch=1;break;} 
   if (stellungswert>29000) {abbruch=1;break;}
  }
  if (abbruch==0) zugtiefe--;
  stim=stim+ende-start;
  if (i>1) wold=stellungswert;
   if (kib==1) 
   { sprintf(wh,"whisper %g (%d/%d)%c\n",1.0*wold/100,zugtiefe
     ,endtiefe+1,(abbruch==2 ? '~' : '#')); 
     if (stellungswert>29000)
       printf("kibitz Forced win in %d moves\n",(101-(stellungswert-1)%100)/2);
   }
   if (xboard!=1) 
     printf(" Eval: %d %d (%d) in %ld %%sec, all time: %ld %%sec\n",stellungswert,nm,endtiefe,ende-start,stim);
   if (dfl2==1 && stellungswert==DRAW) 
   { if (rep>99) dr50=1;
     else drr=1; 
     printf("draw\n"); fflush(stdout);
   }
if (kib)
{ if (resign)
  { if (otim>7500 && stellungswert<=-350)
    { if ((stellungswert+700-ratdiff-(otim-8500)/30)<0) stellungswert=-30001; }
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

void createbook(int d)
{ int i,pf=0;signed char du;
  FILE *fp,*fb;
  EDFLAG=1;
  if (d==-1) 
  { fp=fopen("blackc.book","a");fb=fopen(blackbook[type],"ab"); }
  else 
  { fp=fopen("whitec.book","a");fb=fopen(whitebook[type],"ab"); }
  for (i=1;i<=60;i++) 
  { if (KillFlag[i]>=12 && KillFlag[i]<=21) pf=1;
    if (i>numhalbz || i>58 || pf==1) 
    { fprintf(fp,"----");du=127;
      fwrite((char *)&du,1,sizeof(du),fb);
      fwrite((char *)&du,1,sizeof(du),fb); 
    }
    else 
    { fprintf(fp,"%c%c%c%c ",StartZug[i]%10+96,StartZug[i]/10+47,EndZug[i]%10+96,EndZug[i]/10+47);
      du=(signed char)StartZug[i];
      fwrite((char *)&du,1,sizeof(du),fb);
      du=(signed char)(EndZug[i]-StartZug[i]);
      fwrite((char *)&du,1,sizeof(du),fb); 
    }
  }
  fprintf(fp,"\n");
  fclose(fp);fclose(fb);
}

int attacked(int feld)
{
  int w2,szugvar,f,b,bewpoint,j,i,reichw,k;
  if (Board[feld+9*dran]==dran*BP) return 1;
  if (Board[feld+11*dran]==dran*BP) return 1;
  for (i=0;i<8;i++) if (Board[feld+beweg[8+i]]==dran*BN) return 1;
  for (i=0;i<8;i++) 
  { szugvar=feld;
    for (k=1;k<8;k++) 
    { szugvar+=stern[i];
      w2=Board[szugvar];
      if (w2==RAND) break;
      else 
      { if (w2!=0) 
        { if (w2==dran*BQ) return 1;
          if (w2==dran*BK) if (k==1) return 1;
          if (w2==dran*sternfig[i]) return 1;
          break; 
        }
      }
    }
  }
return 0;
}

int legalezuege(int *lsu,int *lzu,int *kilu,int schach)
{
  int ls[MAXMGL],lz[MAXMGL],kil[MAXMGL];
  int anz=0,dfeld,rfl,reihe,neben,tausch,ffl,FK2=FK,inc=1;
  int i,j,k,l,n,w,w2,fig,szugvar,bewpoint,kpos,janus;
  int reichw,bewbauer,diagonal,fessel[8],fesselr[8],anzfes;
  dfeld=1+dran; anz=0; anzfes=0;
{ kpos=koenig[dfeld];
  if (schach<0) schach=attacked(kpos);
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
         if (w==BQ || w==sternfig[i]) break;
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
        if (w==WN) fig=FN;
         else if (w==WB) fig=FB;
          else if (w==WR) fig=FR;
           else if (w==WQ) fig=FQ;
            else if (w==WK) fig=FK; 
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
                  { if (schach!=0)
                      if (istschach(ls[anz],lz[anz],kil[anz])!=0) inc=0;
                    for (n=0;n<anzfes;n++)
                      if (ls[anz]==fessel[n] && abs(lz[anz])!=fesselr[n])
                        { inc=0; break; }
                  }
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
                      if (istschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
                  }
                  anz++; 
                }
                else
                { for (l=FN;l<FK2;l++)
                  { ls[anz]=i; lz[anz]=diagonal; kil[anz]=11+l*2;
                    { if (schach!=0)
                        if (istschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
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
                      if (istschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
                  }
                  anz++; 
                }
                else
                { for (l=FN;l<FK2;l++)
                  { ls[anz]=i;lz[anz]=diagonal*(k+1);kil[anz]=10+l*2;
                    { if (schach!=0)
                        if (istschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
                    }
                    anz++;
                  } 
                }
              }
            }
          }
        }
        else   /* other figures */
        {
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
                      if (istschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
                  }
                  anz++; 
                }
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
                  if (Board[k]!=rochfeld[j][k-rochchk1[j]]) { rfl=1; break; }
                 if (rfl==0)
                   for (k=rochchk3[j];k<=rochchk4[j];k++)
                     if (attacked(k)>0) {rfl=1; break;} 
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
   if (kil[i]==0)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;}
  }
  for (i=0;i<anz;i++)
  { 
   if (kil[i]>=0) 
   { if (kil[i]<22)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;}
   }
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
   { if (History[ls[i]][ls[i]+lz[i]]>2)
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

int schlagzuege(int *lsu,int *lzu,int *kilu,int schach)
{
  int ls[MAXMGL],lz[MAXMGL],kil[MAXMGL];
  int anz=0,dfeld,rfl,reihe,neben,tausch,ffl,FK2=FK,inc=1;
  int i,j,k,l,n,w,w2,fig,szugvar,bewpoint,kpos,janus;
  int reichw,bewbauer,diagonal,fessel[8],fesselr[8],anzfes;
  dfeld=1+dran; anz=0; anzfes=0;
        
  for (i=BANF;i<BEND;i++) 
  { w=Board[i];
    if (w!=RAND) 
    { w*=dran;
      if (w>0) 
      {
        fig=FP;
        if (w==WN) fig=FN;
         else if (w==WB) fig=FB;
          else if (w==WR) fig=FR;
           else if (w==WQ) fig=FQ;
            else if (w==WK) fig=FK; 
        if (fig==FP)                  /* Pawns */
        { reihe=(int)(i/10);
          if (reihe==siebtereihe[dfeld]) tausch=1;
              else tausch=0;
          if (reihe==fuenftereihe[dfeld])
            if (EnPassant[numhalbz-1]>0) 
            { neben=EndZug[numhalbz-1]-i;
              if ((neben==1) || (neben==-1))
              { ls[anz]=i,lz[anz]=10*dran+neben;kil[anz]=11;inc=1;
                { 
                  if (istschach(ls[anz],lz[anz],kil[anz])!=0) inc=0;
                }
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
                    {
                      if (istschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
                    }
                  anz++; 
                }
                else
                { for (l=FN;l<FK2;l++)
                  { ls[anz]=i; lz[anz]=diagonal; kil[anz]=11+l*2;
                    { 
                        if (istschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
                    }
                    anz++;  
                  }
                }
              }
            }
          }
          if (tausch!=0)
          { 
            { w2=Board[i+dran*10];
              if (w2==LEER)
              { for (l=FN;l<FK2;l++)
                  { ls[anz]=i;lz[anz]=dran*10;kil[anz]=10+l*2;
                    if (istschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
                    anz++;
                  }
              }
            }
          }
        }
        else   /* other figures */
        {
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
                { if (w2<0)
                  {
                  ls[anz]=i;
                  lz[anz]=k*bewpoint;
                  kil[anz]=fig; k=9;  
                  { 
                      if (istschach(ls[anz],lz[anz],kil[anz])!=0) anz--;
                  }
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
   if (kil[i]==0)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;}
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];j++;}
  }
  return anz;
}

void makemove(int kilflag)
{
 KillFlag[numhalbz]=kilflag;
 if ( kilflag < 30 )
  {
   StartZug[numhalbz]=szug;
   EndZug[numhalbz]=ezug;
   SchlZug[numhalbz][0]=Board[ezug];
   if (kilflag<7)
   { material-=Board[ezug];
     if (Board[ezug]==dran*BP) 
     { pawnline[ezug % 10][1-dran]--; 
       pawnc[1-dran]--;
       pawnrank[ezug / 10][1-dran]--; }
   }
 {
     Board[ezug]=Board[szug];
   if (kilflag<22) if (kilflag>11)
     { material-=Board[ezug];
       material-=SchlZug[numhalbz][0];
       Board[ezug]=dran*Figur[(kilflag-10)/2]; 
       material+=Board[ezug];
       pawnline[szug % 10][dran+1]--; 
       pawnrank[szug / 10][dran+1]--; }
 }
   if (kilflag==0 || kilflag==23 || kilflag==11)
   {
     pawnrank[szug / 10][dran+1]--;
     pawnrank[ezug / 10][dran+1]++;
   }
   if (kilflag==23)
   { if (zug==dran*20) EnPassant[numhalbz]=szug; }
   else    
     if (Board[szug]==dran*WK) { koenig[dran+1]=ezug; }
   Board[szug]=LEER;
   if (kilflag==11)
     { material-=Board[ezug-dran*10];
       Board[ezug-dran*10]=LEER; 
       SchlZug[numhalbz][0]=dran*BP; 
       pawnline[ezug % 10][1-dran]--; 
       pawnrank[ezug / 10][1-dran]--; }

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

void takeback(void)
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
 {
     Board[szug]=Board[ezug];
   if (kilflag>11) if (kilflag<23) 
   { material-=Board[szug];
     Board[szug]=dran*WP;
     material+=Board[szug];
     material+=SchlZug[numhalbz][0];
     pawnline[szug % 10][dran+1]++;
     pawnrank[szug / 10][dran+1]++; }
 }
   if (kilflag==0 || kilflag==23 || kilflag==11)
   {
     pawnrank[szug / 10][dran+1]++;
     pawnrank[ezug / 10][dran+1]--;
   }
   if (Board[ezug]==dran*WK)
     koenig[dran+1]=szug;
   Board[ezug]=SchlZug[numhalbz][0];
   if (kilflag==11)
   { 
     Board[ezug]=LEER; 
     Board[ezug-dran*10]=dran*BP; 
     material+=dran*BP;
     pawnline[ezug % 10][1-dran]++; 
     pawnrank[ezug / 10][1-dran]++; 
   } 
   if (kilflag<7)
   { material+=Board[ezug];
     if (Board[ezug]==dran*BP) 
     { pawnline[ezug % 10][1-dran]++; 
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

void TermSearch(int sig) {abbruch=2;}

void Die(int sig) {exit(0);}

void eingzug(int argc, char **argv)
{
  int i,j,anz,efl,ti,r1,r2;
  int legals[MAXMGL];
  int legalz[MAXMGL];
  int kil[MAXMGL];
  char eingabe[32],s[32],e0,e1,e2,e3,e4;
  if (!CHECK) {i=rochiert[0];j=rochiert[2];rochiert[0]=rochiert[2]=0;}
  if (type==TYPES)
    anz=gensuic(&legals[0],&legalz[0],&kil[0],-1);
  if (type==TYPEL)
    anz=genloser(&legals[0],&legalz[0],&kil[0],-1);
  if (type==TYPEA)
    anz=genatom(&legals[0],&legalz[0],&kil[0],-1);
  if (type==TYPEN)
    anz=legalezuege(&legals[0],&legalz[0],&kil[0],-1);
  lzz=anz;
  if (!CHECK) {rochiert[0]=i;rochiert[2]=j;}
  if (anz==0) matt();
  if (type==TYPEL) { if (piecec[2]==0 || piecec[0]==0) matt(); }
  signal(SIGINT,TermSearch);
#ifdef UNIX
  signal(SIGQUIT,Die);
#endif
  gets(eingabe);for (i=0;i<32;i++) s[i]=eingabe[i];
  if(feof(stdin)||ferror(stdin)||ferror(stdout)) Die(0);
  e0=eingabe[0];e1=eingabe[1];e2=eingabe[2];e3=eingabe[3];e4=eingabe[4];
  if (e0=='q') if (e1=='u' && e2=='i') exit(0);
  if (e0=='f') if (e1=='o' && e2=='r') 
     { gets(eingabe);e0=eingabe[0];e1=eingabe[1];e2=eingabe[2];
       if (e0=='a') {compfarbe=1;dran=1;eingabe[0]='&';}}
  if (e0=='#') if (e1=='\0') 
     { editboard();printboard();fflush(stdout);}
  if (e0=='t') if (e1=='i') 
     { sscanf(eingabe+5,"%d",&ti); controltime(ti); }
  if (e0=='o') if (e1=='t') 
     { sscanf(eingabe+5,"%d",&otim); }
  if (e0=='u') if (e1=='n') { debug=1;
       dran*=WECHSEL; numhalbz--; takeback();
       compfarbe*=WECHSEL; dran*=WECHSEL;numhalbz--;return;}
  if (e0=='b') if (e1=='l') {compfarbe=-1;force=0;}
  if (e0=='w') if (e1=='h') {compfarbe=1;force=0;}
  if (e0=='g') if (e1=='o') 
     { debug=2;numhalbz--;dran*=WECHSEL;return; }
  if (e0=='r') if(e1=='a') 
     { sscanf(eingabe+7,"%d %d",&r1,&r2);ratdiff=r2-r1;}
  if (e0=='T') if(e1=='Y') 
     { sscanf(eingabe+5,"%s",s);
       if (s[0]=='S' || s[1]=='u') { type=TYPES; main(argc,argv); }
       if (s[0]=='l' && s[1]=='o') { type=TYPEL; main(argc,argv); }
       if (s[0]=='A' && s[1]=='t') { type=TYPEA; main(argc,argv); }
       if (s[0]=='l' && s[1]=='i') { maxt=MAXLIGHT; }
       if (s[0]=='B' && s[1]=='u') { maxt=MAXLIGHT; }
     }
  if (e0<'a' || e0>'h' || e1<'1' || e1>'8' || force==1) eingzug(argc,argv); 
  else
  {
    e0-=96; e1-=47; e2-=96; e3-=47;
    szug=e1*10+e0; ezug=e3*10+e2;
    zug=ezug-szug;
  efl=0;kllz=0;
  for (i=0;i<anz;i++)
    if ((legals[i]==szug) && (legalz[i]==zug)) {efl=1;kllz=kil[i];}
  if (efl==0 && CHECK==1) 
    { printf("Illegal move (no matching move)%s\n",s);
      fflush(stdout); eingzug(argc,argv); }
  if (kllz>=14 && kllz<=21)         /* Promotion */
  { if (e4=='n') kllz=12+(kllz%2);
    if (e4=='b') kllz=14+(kllz%2);
    if (e4=='r') kllz=16+(kllz%2); 
    if (e4=='q') kllz=18+(kllz%2); }  /* else King ... */
  if (opening==1) for (i=0;i<NUMOPEN;i++)
    if (Os[numhalbz][i]!=szug || Oz[numhalbz][i]!=zug)
      Of[i]=0;
#if ATOMICDIS
  displayexplode(s);
#endif
  }
}

void ausgzug(void)
{
  char ausgabe[6];
  ezug=szug+zug;
  ausgabe[1]=(szug / 10)+47;
  ausgabe[3]=(ezug / 10)+47;
  ausgabe[0]=(szug % 10)+96;
  ausgabe[2]=(ezug % 10)+96;
  ausgabe[4]='\0';ausgabe[5]='\0';
  if (kllz==12 || kllz==13) ausgabe[4]='n';
  if (kllz==14 || kllz==15) ausgabe[4]='b';
  if (kllz==16 || kllz==17) ausgabe[4]='r';
  if (kllz==18 || kllz==19) ausgabe[4]='q';
  if (kllz==20 || kllz==21) ausgabe[4]='k';
  printf("%d. ... %s\n",(numhalbz+1)/2,ausgabe);fflush(stdout);
  if (dr50) {printf("draw\n");/*printf("Drawn by 50 moves rule!\n");*/}
  if (drr) {printf("draw\n");/*printf("Drawn by repition!\n");*/}
  if (kib==1) printf("%s",wh);
  fflush(stdout);
#if ATOMICDIS
  displayexplode(ausgabe);
#endif
}

void printboard(void)
{
  int i,j,w,c,fig;
  if (xboard!=0) return;
  for (j=90;j>10;j-=10)
  { for (i=1;i<9;i++)
    { w=Board[i+j];
      c=((w<0) ? '*' : ' '); w=abs(w);
      for (fig=FP;fig<=FK;fig++)
      { 
        if (w==ValFig[type][fig]) 
        { printf (" %c%c",name[fig],c); break; }
      }
    if (fig>FK) printf (" . "); 
   }  printf("\n"); 
  }
  printf(" material %d blpiec %d whpiec %d blpawn %d whpawn %d \n",material,piecec[0],piecec[2],pawnc[0],pawnc[2]);
  zugspec=0;printf(" instant value %d for white \n",dran*evalsuic(0,0)); fflush(stdout);
}

int quiesce(int alpha,int beta,int anz,int anz2,int kfl)
{
  int i,w,schfl=-1,sfl2,zugt;
  int maximum=alpha;int legalanzahl,wert;
  int legals[MAXMGL];
  int legalz[MAXMGL];
  int kil[MAXMGL]; /* REL */
  if (nm-restnode>0)
      { ende=myget();
        restnode+=NODEC;
        if (ende-start>=timeformove && zugtiefe>STARTDEPTH) abbruch=2;
      }
  if (abbruch>0) return GUT; 
  Htief[ply]=ply;
  if (ply>endtiefe) endtiefe=ply;
  nm++;
  dran*=WECHSEL;
  schfl=attacked(koenig[dran+1]); 
  if (schfl>0) 
  { legalanzahl=legalezuege(&legals[0],&legalz[0],&kil[0],schfl);
    if (legalanzahl==0)  
         alpha=SCHLECHT+ply;
  }
  else
  {
    wert=eval(anz2,anz); 
#if defined(POWD)
    if (wert>=beta || ply>1) {dran*=WECHSEL;return (wert);}
#elif defined(DISASTER)
    if (wert>=beta || ply>-1) {dran*=WECHSEL;return (wert);}
#else
    if (wert>=beta) {dran*=WECHSEL;return (wert);}
#endif
    if (wert>alpha) alpha=wert;
    legalanzahl=schlagzuege(&legals[0],&legalz[0],&kil[0],schfl);
  }

  for (i=0;i<legalanzahl;i++)
  {
    szug=legals[i]; zug=legalz[i]; sfl2=0; ezug=szug+zug;
    makemove(kil[i]); 
        numhalbz+=1; ply++;
        w=-quiesce(-beta,-alpha,legalanzahl,anz,kil[i]);
        numhalbz-=1; ply--;
        takeback();
    if (w>alpha) {alpha=w;KopPV(ply,legals[i],legalz[i]);
       if (w>=beta) 
       { if (i>0) 
         { 
           K2von[ply]=Kvon[ply];K2nach[ply]=Knach[ply];
           Kvon[ply]=legals[i];Knach[ply]=legalz[i];
          } 
       dran*=WECHSEL;return(w);}
       }
  }
  dran*=WECHSEL;
  return (alpha);  
}

int search(int alpha,int beta,int dist,int anz,int anz2,int kfl)
{
  int i,w,schfl=-1,sfl2,zugt;
  int maximum=SCHLECHT;int legalanzahl=0,wert;
  int legals[MAXMGL];
  int legalz[MAXMGL];
  int kil[MAXMGL];
  if (nm-restnode>0)   /* Here we check each NODEC nodes for time */
      { ende=myget();
        restnode+=NODEC;
        if (ende-start>=timeformove && zugtiefe>STARTDEPTH) abbruch=2;
      }
  if (abbruch>0) return GUT; /* You can call the next line most important */
  if (dist<=0) 
  { 
      return(quiesce(alpha,beta,anz,anz2,kfl));
  }
  dran*=WECHSEL;
{ schfl=attacked(koenig[dran+1]); 
  if (schfl>0) dist++;
}
  nm++;
  if (ply>endtiefe) endtiefe=ply;
  Htief[ply]=ply;
  legalanzahl=legalezuege(&legals[0],&legalz[0],&kil[0],schfl);
  zugt=zugtiefe;
  if (legalanzahl==0) if (attacked(koenig[dran+1])==0) maximum=0;
                      else maximum=SCHLECHT+ply;

  for (i=0;i<legalanzahl;i++)
  {
    szug=legals[i]; zug=legalz[i]; ezug=szug+zug;
    makemove(kil[i]); 
        numhalbz++; ply++;
        w=-search(-beta,-alpha,dist-1,legalanzahl,anz,kil[i]);
        numhalbz--; ply--;
SHOWC1
        takeback();
        if (abbruch>0) {dran*=WECHSEL;return GUT;}
    if (w>maximum) {maximum=w;KopPV(ply,legals[i],legalz[i]);
       if (w>=beta) 
       { if (i>0) 
         { 
           K2von[ply]=Kvon[ply];K2nach[ply]=Knach[ply];
           Kvon[ply]=legals[i];Knach[ply]=legalz[i];
           History[legals[i]][legalz[i]+legals[i]]+=dist;} 
       dran*=WECHSEL;return (w);}
       if (w>alpha) {alpha=w;}}
    
  }
  dran*=WECHSEL;
  return maximum;  
}

void KopPV(int a,int s,int z)
{
  int i;
  Hvon[a][a]=s; Hnach[a][a]=z; 
  Htief[a]=Htief[a+1];
  for (i=a+1;i<Htief[a+1];i++)
  {  
     Hvon[a][i]=Hvon[a+1][i];
     Hnach[a][i]=Hnach[a+1][i];
  }
}

int istschach(int s,int z,int k)
{
 int sch; numhalbz++;
 szug=s; zug=z; ezug=szug+zug;
 makemove(k);
   sch=attacked(koenig[dran+1]);
 takeback();
 numhalbz--; return sch;
}

int zugbonus(int s,int e,int k,int d,int p)
{ int zu=0;int rfl,df,l,i;
        if (STELL==0) return 0;
  if (type!=TYPES && type!=TYPEL)
  {     df=d+1;
        if (numhalbz>40) if (k==23 || k==0) zu+=d*pawnstorm;
        if (numhalbz<30) if (k==27) zu-=d*DAM;
        if (endspiel==0) { if (k==28 || k==5) { if (rochiert[df]==0) zu-=d*KNG; else zu-=d*KNG/4;}
        if (s==p+d*9) {zu-=d*KSAV;if (k==0) zu-=d*KSAV;}
        if (s==p+d*10) {zu-=d*KSAV;if (k==0) zu-=d*KSAV;}
        if (s==p+d*11) {zu-=d*KSAV;if (k==0) zu-=d*KSAV;}
        if (s==p+d*19) zu-=d*KSAV;if (s==p+d*20) zu-=d*KSAV;
        if (s==p+d*21) zu-=d*KSAV;
        if (e==p+d*9) zu+=d*KSAV;if (e==p+d*10) zu+=d*KSAV;
        if (e==p+d*11) zu+=d*KSAV;if (e==p+d*19) zu+=d*KSAV;
        if (e==p+d*20) zu+=d*KSAV;if (e==p+d*21) zu+=d*KSAV;
        if (k>29)  
           { if (k==30) p=81;if (k==31) p=87;
             if (k==32) p=31;if (k==33) p=37;
             rfl=0;if (Board[p]==d*WP && Board[p+1]==d*WP) rfl=1;
             if (Board[p+d*10]==d*WP && Board[p+1]==d*WP) rfl=1;
             if (Board[p]==d*WP && Board[p+d*10+1]==d*WP) rfl=1;
             if (rfl==1) 
             { if (k==31 || k==33) zu+=d*ROCH; }
             else zu-=2*d*ROCH;
           }
        if (k==24 || k==1) zu+=d*(Zentrum[e]-20)/2;
        }
        if (k==26 || k==3) 
        { if (pawnline[s%10][df]>0 && pawnline[s%10][2-df]>0)
          { if (pawnline[e%10][df]==0) zu+=d*ROOKF;
            else if (pawnline[e%10][df]==1 && pawnline[e%10][2-df]==0)
                  zu+=d*ROOKF/2;
          }
        } 
        if (s==ent1[df]) if (k==24 || k==1) zu+=d*NDAM;
        if (s==ent2[df]) if (k==24 || k==1) zu+=d*NKON;
        if (s==ent3[df]) if (k==25 || k==2) zu+=d*BDAM;
        if (s==ent4[df]) if (k==25 || k==2) zu+=d*BKON;
        if (s==ent5[df]) if (k==23) zu+=d*PDAM;
        if (s==ent6[df]) if (k==23) zu+=d*PKON;
        if (s==ent7[df]) if (k==23) zu+=d*CPWN;
        if (e==ent5[df]+d*10) if (Board[ent5[df]]==WP*d) zu-=d*PDAM;
        if (e==ent6[df]+d*10) if (Board[ent6[df]]==WP*d) zu-=d*PKON;
        if (e==ent7[df]+d*10) if (Board[ent7[df]]==WP*d) zu-=d*CPWN;
    }
    else
      if (k==23 || k==0) zu+=d*pawnstorm;
   return zu;
}

int eval(int anz,int anz2)
{
  int j,d,e,ds,dr,v;int wert;
  wert=material; e=koenig[0];d=koenig[2];
  wert+=(rochiert[2]-rochiert[0])*ROCH;
  ds=0;dr=0;
  for (j=1;j<10;j++) 
  { if (pawnline[j][0]==1) ds++;
    else 
    { if (pawnline[j][0]>1) 
      { wert+=DOPPEL*(pawnline[j][0]-1); ds++; }
      else 
      { if (ds==1) wert+=ISOLANI; ds=0; }
    }
    if (pawnline[j][2]==1) dr++;
    else
    { if (pawnline[j][2]>1) 
      { wert-=DOPPEL*(pawnline[j][2]-1); dr++; }
      else
      { if (dr==1) wert-=ISOLANI; dr=0; }
    }
  }
  wert+=pawnrank[8][2]*PT7;
  wert+=pawnrank[7][2]*PT6;
  wert-=pawnrank[4][0]*PT6;
  wert-=pawnrank[3][0]*PT7;

  if (endspiel==1)
  { 
    wert+=Zentrum[d];wert-=Zentrum[e]; 
    ds=d/10-e/10;dr=d%10-e%10;
    v=ds*ds+dr*dr;
    wert-=2*compfarbe*v;
  }
  else
  { if (pawnline[d%10][2]==0) wert-=KSAV;
    if (pawnline[d%10+1][2]==0) wert-=KSAV;
    if (pawnline[d%10-1][2]==0) wert-=KSAV;
    if (pawnline[e%10-1][0]==0) wert+=KSAV;
    if (pawnline[e%10+1][0]==0) wert+=KSAV;
    if (pawnline[e%10][0]==0) wert+=KSAV;
  }
   wert+=zugspec;
  wert*=dran;
  return (wert+MOBIL*(anz-anz2));
}
