all:
	gcc -o nyc nyc.c
run:
	./nyc -read_csv
	./nyc -read_data
