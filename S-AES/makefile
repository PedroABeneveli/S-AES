CXX = g++
CXXFLAGS = -Iheaders -Wall

SRC_DIR = src
HEADER_DIR = headers

SOURCES = $(SRC_DIR)/teste.cpp $(SRC_DIR)/NibbleMatrix.cpp $(SRC_DIR)/operations.cpp

OUTPUT = saes

$(OUTPUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OUTPUT)