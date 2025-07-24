#include "argumentParser.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

ArgumentParser::ArgumentParser(int argc, char **argv) { parseArguments(argc, argv); }

bool ArgumentParser::hasFlag(const std::string &flag) const { return flags.find(flag) != flags.end(); }

std::string ArgumentParser::getValue(const std::string &key) const
{
  auto it = values.find(key);
  return (it != values.end()) ? it->second : "";
}

void ArgumentParser::showHelp() const
{
  std::cout << "Usage: tersedecompress++ [<input_file>] [<output_file>]" << std::endl;
  std::cout << "If <input_file> is omitted or '-', reads from stdin." << std::endl;
  std::cout << "If <output_file> is omitted or '-', writes to stdout." << std::endl;
  std::cout << "Always runs in binary mode (no EBCDIC->ASCII conversion)." << std::endl;
  std::cout << "Version: 5 (C++ port, pipeline mode)" << std::endl;
}

std::string ArgumentParser::getInputFile() const { return inputFile; }

std::string ArgumentParser::getOutputFile() const { return outputFile; }

void ArgumentParser::parseArguments(int argc, char **argv)
{
  std::vector< std::string > args(argv + 1, argv + argc);

  for (size_t i = 0; i < args.size(); ++i)
  {
    if (args[i] == "-h")
    {
      flags["-h"] = true;
    }
    else if (inputFile.empty())
    {
      inputFile = args[i];
    }
    else if (outputFile.empty())
    {
      outputFile = args[i];
    }
    else
    {
      std::cerr << "Unknown argument: " << args[i] << "\n";
      showHelp();
      std::exit(1);
    }
  }

  // If inputFile is empty or '-', use stdin
  if (inputFile.empty() || inputFile == "-")
  {
    inputFile = "-";
  }
  // If outputFile is empty or '-', use stdout
  if (outputFile.empty() || outputFile == "-")
  {
    outputFile = "-";
  }
}