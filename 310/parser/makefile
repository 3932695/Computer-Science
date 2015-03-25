decafp: lex.yy.o y.tab.o
	g++ -o decafp lex.yy.o y.tab.o

y.tab.o: y.tab.c
	g++ -c y.tab.c

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

y.tab.h: decaf.y
	yacc -d decaf.y

y.tab.c: decaf.y
	yacc -d decaf.y

lex.yy.c: decaf.l y.tab.h
	flex decaf.l

clean:
	rm -rf *~ lex.yy.* *.o y.tab.* decafp a.out
