
#pragma once

#include <fstream>

using namespace std;

ifstream* open_input_file(char* ifilename);

ofstream* open_output_file(char* ofilename);

void rl_compress(ifstream *ifile, ofstream *ofile);

void rl_uncompress(ifstream *ifile, ofstream *ofile);