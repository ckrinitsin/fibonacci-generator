all:
	g++ --std=c++23 -lgmp -lgmpxx ./main.cpp -o ./main

.PHONY:
clean:
	rm main
