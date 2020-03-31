# compiler
CC =	gcc

# set obj folder
OBJD =	obj

# set lib folder
LIBD =	lib 

# -Wall for debug -I for the location of header files 
CFLAGS =	-Wall -I$(LIBD)


OBJ =$(OBJD)/find.o \
		$(OBJD)/kmp.o \
		$(OBJD)/report.o \
		$(OBJD)/file.o \
                                                                       
vpath %.c src
vpath %.h $(LIBD)

all:	find

find: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@ 

$(OBJD)/%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $< 

$(OBJD)/kmp.o: kmp.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJD)/report.o: report.c report.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJD)/file.o: file.c report.h file.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJD)/find.o: find.c report.h kmp.h file.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:
	clean
clean:
	rm find obj/*.o