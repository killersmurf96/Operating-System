Project_Name = simulate
Compiler = g++
CA1Jobs = ca1_jobs.pl 7 10 5

$(Project_Name): $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	$(Compiler) -o $(Project_Name) $^

%.o: %.cpp $(wildcard *.h)
	$(Compiler) -c $<
	
test: $(Project_Name) JobInput.txt
	./$(Project_Name) < JobInput.txt | tee JobOutput.txt
	
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

demo1:  demo_input.txt $(Project_Name)
	./$(Project_Name) < demo_input.txt | tee demo_output1.txt
	
demo2:  demo_input2.txt $(Project_Name)
	./$(Project_Name) < demo_input2.txt | tee demo_output2.txt
	
demo3:  demo_input3.txt $(Project_Name)
	./$(Project_Name) < demo_input3.txt | tee demo_output3.txt