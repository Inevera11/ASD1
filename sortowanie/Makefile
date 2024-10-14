CC=g++
CFLAGS=-Wall -std=c++11 -pedantic

OUTPUT_1=output_select.x
OUTPUT_2=output_heap.x
DIR := $(notdir $(CURDIR))

$(OUTPUT_1): selectsort.cpp
	$(CC) $(CFLAGS) -o $@ $^
$(OUTPUT_2): heapsort.cpp
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OUTPUT_1) $(OUTPUT_2)

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

# Uruchomienie programu
run_select: $(OUTPUT_1)
	./$(OUTPUT_1)

run_heap: $(OUTPUT_2)
	./$(OUTPUT_2)

.PHONY: clean tar run