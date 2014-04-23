SOURCES = iobrazec.cpp \
	asciikontext.cpp \
	kruh.cpp \
	polygony.cpp \
	test.cpp

CXX = g++
CXXFLAGS = -g -W -Wall -Werror -std=c++11
LDFLAGS = -g

OBJECTS = $(SOURCES:.cpp=.o)

test: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean::
	$(RM) test

.cpp.o:
	$(CXX) -MD -MP $(CXXFLAGS) -o $@ -c $<

clean::
	$(RM) *.o

DEPENDS = $(SOURCES:.cpp=.d)

-include $(DEPENDS)

%.d:
	@touch $@

clean::
	$(RM) *.d
