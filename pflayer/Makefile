#PUBLICDIR= /usr0/cs564/public/project

# NEW: Add CFLAGS to tell the compiler to look in the current directory for headers
CFLAGS = -I.

SRC= buf.c hash.c pf.c
OBJ= buf.o hash.o pf.o
HDR = pftypes.h pf.h 

pflayer.o: $(OBJ)
	cc -r -o pflayer.o $(OBJ)

tests: testhash testpf

testpf: testpf.o pflayer.o
	cc -o testpf testpf.o pflayer.o $(CFLAGS)

testhash: testhash.o pflayer.o
	cc -o testhash testhash.o pflayer.o $(CFLAGS)

$(OBJ): $(HDR)

testhash.o: $(HDR)

testpf.o: $(HDR)

lint: 
	lint $(SRC)

install: pflayer.o 

# NEW: Add a "clean" target to easily remove old files
clean:
	rm -f *.o pflayer.o testpf testhash a.out
