#Makefile for OliPow
#-DUNIX for Unix/Unicos/Linux systems, for Dos/Win remove this

CC     = gcc 
CFLAGS = -O3 -DUNIX

DLLIBS = 
DLOBJS = main.o

olipow: $(DLOBJS) $(OBJS)
	gcc $(CFLAGS) -o olipow $(DLOBJS) $(DLLIBS)

$(DLOBJS): main.h Makefile

clean:
	rm *.o olipow
