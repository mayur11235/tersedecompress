#include "TerseDecompresser.h"
#include "argumentParser.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  ArgumentParser parser(argc, argv);

  if (parser.hasFlag("-h"))
  {
    parser.showHelp();
    return 0;
  }

  std::istream* inStreamPtr = nullptr;
  std::ifstream inFile;
  if (parser.getInputFile() == "-") {
    inStreamPtr = &std::cin;
    std::cin.sync_with_stdio(false);
  } else {
    inFile.open(parser.getInputFile(), std::ios::binary);
    if (!inFile.is_open()) {
      std::cerr << "Error: Unable to open input file: " << parser.getInputFile() << "\n";
      return EXIT_FAILURE;
    }
    inStreamPtr = &inFile;
  }

  std::ostream* outStreamPtr = nullptr;
  std::ofstream outFile;
  if (parser.getOutputFile() == "-") {
    outStreamPtr = &std::cout;
    std::cout.sync_with_stdio(false);
  } else {
    outFile.open(parser.getOutputFile(), std::ios::binary);
    if (!outFile.is_open()) {
      std::cerr << "Error: Unable to open output file: " << parser.getOutputFile() << "\n";
      return EXIT_FAILURE;
    }
    outStreamPtr = &outFile;
  }

  try
  {
    auto decompresser = TerseDecompresser::create(*inStreamPtr, *outStreamPtr);
    decompresser->setTextFlag(false); // Always binary mode
    decompresser->decode();
  }
  catch (const std::exception &ex)
  {
    std::cerr << "An error occurred: " << ex.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
