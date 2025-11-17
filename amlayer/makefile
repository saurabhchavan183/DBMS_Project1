# Define a variable for the PF layer include path
PF_INCLUDE = -I../pflayer
# Define a variable for the PF layer library
PF_LIB = ../pflayer/pflayer.o

a.out : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o main.o amscan.o amprint.o
	cc am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../pflayer/pflayer.o main.o amscan.o amprint.o 

amlayer.o : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o amscan.o amprint.o
	ld -r am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o amscan.o amprint.o  -o amlayer.o

am.o : am.c am.h ../pflayer/pf.h
	cc -c am.c $(PF_INCLUDE)

amfns.o : amfns.c am.h ../pflayer/pf.h
	cc -c amfns.c $(PF_INCLUDE)

amsearch.o : amsearch.c am.h ../pflayer/pf.h
	cc -c amsearch.c $(PF_INCLUDE)

aminsert.o : aminsert.c am.h ../pflayer/pf.h
	cc -c aminsert.c $(PF_INCLUDE)

amscan.o : amscan.c am.h ../pflayer/pf.h
	cc -c amscan.c $(PF_INCLUDE)

amstack.o : amstack.c am.h ../pflayer/pf.h
	cc -c amstack.c $(PF_INCLUDE)

amglobals.o : amglobals.c am.h
	cc -c amglobals.c

amprint.o : amprint.c am.h ../pflayer/pf.h 
	cc -c amprint.c $(PF_INCLUDE)
	
main.o : main.c am.h ../pflayer/pf.h 
	cc -c main.c $(PF_INCLUDE)


