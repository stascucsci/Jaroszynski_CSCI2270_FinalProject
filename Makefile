all:
	g++ -Wall -std=c++11 *.cpp -o run

clean:
	rm -f run
