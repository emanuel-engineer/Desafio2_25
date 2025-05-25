# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
SRCDIR = src
INCDIR = include
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = programa

# Regla principal
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compilar archivos .cpp a .o
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
