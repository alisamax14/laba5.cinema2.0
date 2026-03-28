CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
TARGET = cinema_db_cpp
SOURCES = main.cpp Film.cpp FilmArray.cpp File_Operations.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp Film.h FilmArray.h File_Operations.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) *.bin

run: $(TARGET)
	./$(TARGET)

run-with-file: $(TARGET)
	./$(TARGET) my_database.bin

.PHONY: all clean run run-with-file
