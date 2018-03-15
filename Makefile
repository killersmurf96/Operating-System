Project_Name = simulate
Compiler = g++

$(Project_Name): $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	$(Compiler) -o $(Project_Name) $^

%.o: %.cpp $(wildcard *.h)
	$(Compiler) -c $<
	
test: $(Project_Name) JobInput.txt
	./$(Project_Name) < JobInput.txt | tee JobOutput.txt
	
demo1: $(Project_Name) ca1_jobs.pl
	./$(Project_Name) < ca1_jobs.pl | tee demo_output1.txt
	
demo2: $(Project_Name) ca1_jobs.pl
	./$(Project_Name) < ca1_jobs.pl | tee demo_output.txt
	
demo3: $(Project_Name) ca1_jobs.pl
	./$(Project_Name) < ca1_jobs.pl | tee demo_output3.txt