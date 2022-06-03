NAME=main
main: $(NAME).cu
	nvcc  -arch=sm_70 -std=c++14 -Xcompiler -fopenmp $(NAME).cu -o $(NAME) 
	./main < input.txt
