# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./src

# Bibliotecas SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Diretórios
SRC_DIR = src
OBJ_DIR = obj

# Arquivos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Executável
TARGET = src/jogo

# Regra padrão
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(SFML_LIBS)

# Compilação dos .cpp para .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Limpeza completa
purge: clean
	rm -f *~
