all:
	gcc -o nyc nyc.c
run:
	./nyc -read_csv
	./nyc -read_data
	./nyc -add_data
	./nyc -read_data
	./nyc -update_data
	./nyc -read_data