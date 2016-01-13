CC=gcc
WARNINGS := -Wall
CFLAGS := -g -std=c99 $(WARNINGS)
LDFLAGS=-lm
SOURCES1= interface.c 
OBJECTS1=$(SOURCES1:.c=.o) PictureIndexation.o textIndexing.o 
EXE1= TestPictureIndexation.out
EXE=  1

all: $(EXE)

1:    $(OBJECTS1)
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJECTS1) $(LDFLAGS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:   $(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.out sto/base_descripteur_son sto/liste_base_son
