ProjectName = simulate
Compiler = g++
CA1Jobs = ca1_jobs.pl 7 10 5

$(ProjectName): $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	$(Compiler) -o $(ProjectName) $^

%.o: %.cpp $(wildcard *.h)
	$(Compiler) -c $<
	
test: $(ProjectName) JobInput.txt
	./$(ProjectName) < JobInput.txt | tee JobOutput.txt
	
demo: 
	make demo1
	make demo2
	make demo3
	
demo_input.txt: 
	$(CA1Jobs) > $@
	
demo_input2.txt:
	$(CA1Jobs) > $@
	
demo_input3.txt:
	$(CA1Jobs) > $@

demo1:  demo_input.txt $(ProjectName)
	./$(ProjectName) < demo_input.txt | tee demo_output1.txt
	
demo2:  demo_input2.txt $(ProjectName)
	./$(ProjectName) < demo_input2.txt | tee demo_output2.txt
	
demo3:  demo_input3.txt $(ProjectName)
	./$(ProjectName) < demo_input3.txt | tee demo_output3.txt