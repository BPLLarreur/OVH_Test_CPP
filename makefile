# Makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall
BUILD_DIR = build
TARGET = secret

$(shell mkdir -p $(BUILD_DIR))

all: $(TARGET)

$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/robot.o $(BUILD_DIR)/scheduler.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/main.o: main.cpp robot.h scheduler.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/robot.o: robot.cpp robot.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/scheduler.o: scheduler.cpp scheduler.h robot.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)