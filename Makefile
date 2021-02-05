
all: heap tree array test

heap: heap.cpp comon.h
	g++ -o $@ $<
	
tree: suf_ar.o tree.cpp comon.h
	g++ -o $@ $^
	
array: suf_ar.o rmq.o array.cpp comon.h
	g++ -o $@ $^

suf_ar.o: suf_ar.cpp comon.h
	g++ -c $<

rmq.o: rmq.cpp comon.h
	g++ -c -fpermissive $<
	
test: test.sh
	cat test.sh > test
	chmod a+x test
	
clean:
	rm -f *.o *.out heap tree array test
