CXX = g++
CXXFLAGS = -Iheaders -Wall

SRC_DIR = src
HEADER_DIR = headers

SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/NibbleMatrix.cpp $(SRC_DIR)/operations.cpp $(SRC_DIR)/GaloisField.cpp $(SRC_DIR)/encrypt.cpp $(SRC_DIR)/utils.cpp

OUTPUT = saes

$(OUTPUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OUTPUT)