# Makefile for easy compilation and execution of the code base

install:
	@wget -O Eigen.zip https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip
	@unzip Eigen.zip
	@sudo cp -r eigen-3.4.0/Eigen /usr/local/include
	@rm Eigen.zip
	@rm -r eigen-3.4.0

run:
	@g++ src/main.cpp -o main
	@./main
