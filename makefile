OBJ = main.o screen.o sound.o
APPNAME = sound.out
$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm
%.o : %.c
	gcc -c -o $@ $<
purge :
	rm $(OBJ) $(APPNAME)
tar:
	tar cf sound.tar *.c *.h makefile
