CXX = g++
CXXFLAGS = -Iinclude -std=c++17

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

TARGET = GerenciadorTarefas.exe

all: build $(TARGET)

build:
	mkdir build 2>nul || true

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
	
clean:
	rmdir /S /Q build 2>nul || true
	del $(TARGET) 2>nul || true