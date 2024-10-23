PROG := main

$(PROG): $(PROG).cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

test: $(PROG)
	./$(PROG) < input

test1: $(PROG)
	./$(PROG) < input1

test2: $(PROG)
	./$(PROG) < input2

test3: $(PROG)
	./$(PROG) < input3
