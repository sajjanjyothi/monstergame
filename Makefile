INCLUDE_DIR = -I ./ 
CPPUNIT_HEADER = -I /usr/local/Cellar/cppunit/1.14.0/include
CPP = g++
OUTPUT = main
TESTOUTPUT = unit_test
OBJECTFILES = main.o city.o monster.o
TESTOBJECT_FILES = unit_test.o city.o monster.o
LIBS = -lcppunit
CFLAGS = $(INCLUDE_DIR)
LIB_DIR = -L /usr/local/Cellar/cppunit/1.14.0/lib
EXTRA_FLAGS = -std=c++11

all:$(OUTPUT) $(TESTOUTPUT)
%.o : %.cpp
	$(CPP) -c -o $@ $^ $(CFLAGS) $(EXTRA_FLAGS) $(INCLUDE_DIR) $(CPPUNIT_HEADER)

$(OUTPUT):$(OBJECTFILES) 
	$(CPP) -o $@ $(OBJECTFILES) $(CFLAGS) $(EXTRA_FLAGS)
$(TESTOUTPUT):$(TESTOBJECT_FILES)
	$(CPP) -o $@ $(TESTOBJECT_FILES) $(CFLAGS) $(LIBS) $(EXTRA_FLAGS) $(LIB_DIR) 

clean:
	rm -rf $(OBJECTFILES) $(OUTPUT) $(TESTOBJECT_FILES) $(TESTOUTPUT)