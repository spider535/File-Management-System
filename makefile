 # the build target executable:
	TARGET = main
final:
	g++ main.cpp -o main -std=c++11

clean:
	$(RM) $(TARGET)
