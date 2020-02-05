# compiler
CC =	gcc

# set obj folder
OBJD =	obj

# set lib folder
LIBD =	lib 

# -Wall for debug -I for the location of header files 
CFLAGS =	-Wall -I$(LIBD)


OBJ =$(OBJD)/file.o \
		$(OBJD)/kmp.o \
		$(OBJD)/report.o \
                                                                       
vpath %.c src
vpath %.h $(LIBD)

all:	file 

file: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@ 

$(OBJD)/%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $< 

$(OBJD)/kmp.o: kmp.c kmp.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJD)/report.o: report.c report.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJD)/file.o: file.c report.h kmp.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:
	clean
clean:
	rm file obj/*.o




