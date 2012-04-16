all = main.o syntax.tab.o tree.o traverse.o

parser:$(all)
	gcc $(all) -lfl -ly -o parser
	
main.o:syntax.tab.h main.c tree.h
	gcc -c main.c
syntax.tab.o:syntax.tab.c lex.yy.c
	gcc -c syntax.tab.c -lfl -ly
tree.o:tree.c tree.h
	gcc -c tree.c	
traverse.o:traverse.c tree.h
	gcc -c traverse.c
syntax.tab.c syntax.tab.h:syntax.y tree.h
	bison -d syntax.y
lex.yy.c:lex.yy.l tree.h
	flex lex.yy.l

int:
	./parser int.cmm
float:
	./parser float.cmm
comment:
	./parser comment.cmm
test1:
	./parser test1.cmm
test2:
	./parser test2.cmm
test3:
	./parser test3.cmm
test4:
	./parser test4.cmm
	
clean:
	rm -f ${all}
	rm -f parser
	rm -f syntax.tab.c
	rm -f syntax.tab.h
