SRCS	 = main.cpp graph.cpp checkPlanarity.cpp
CXX		 = g++-6
CXXFLAGS = -std=c++11 -fdiagnostics-color -O3
EXE		 = CheckPlanarity

CP:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) -D_GLIBCXX_DEBUG $(SRCS) -o $@

clean:
	-rm -f EIM
