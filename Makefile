
all:
	gcc -o producer producer.c
	gcc -o consumer consumer.c

clean:
	rm producer consumer consumer.txt producer.txt

rebuild: clean all
