

all:
	@gcc -m64 -o a.out -Iinc/ drivers/verify.c src/functions.c

test: a.out 
	@./a.out < public_tests/inputs/t$(num).txt > myo$(num) 
	@diff myo$(num) public_tests/outputs/o$(num).txt  | tee  diff_output.txt > /dev/null
	@python3 drivers/file_check.py
	@rm -f diff_output.txt

clean: 
	@rm -f *.o *.out diff_output.txt
	@rm -f myo1
	@rm -f myo2
	@rm -f myo3
	@rm -f myo4
	@rm -f myo5
