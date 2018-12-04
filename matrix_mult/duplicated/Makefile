# C compiler
CC = gcc -g

destDir = /tmp/mult/

all: gen_bin gen_data mv_bin 

gen_bin: mult.c gen.c print.c
	$(CC) $(CC_FLAGS) mult.c -o mult
	$(CC) $(CC_FLAGS) gen.c -o gen
	$(CC) $(CC_FLAGS) print.c -o print 

gen_data: gen_bin
	./gen 600
	./mult 600
	cp /tmp/mult/result_600 /tmp/mult/gold_600

mv_bin: gen_data
#	mkdir -p $(destDir)
#	mkdir -p lastDataCreated
#	cp *A *B result* gold* lastDataCreated
	mv gen mult print $(destDir)
	@echo "All Done, executables should be in the $(destDir)"

clean:
	rm -rfv *A *B result* gold*
