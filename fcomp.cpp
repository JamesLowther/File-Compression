// File compression | James Lowther | December 22, 2019

#include <iostream>
#include <fstream>
#include <string>

#include "fcomp.hpp"

using namespace std;

ifstream* open_input_file(string ifilename) {

    ifstream* ifile = new ifstream;

    ifile->open(ifilename, fstream::binary | fstream::in); // open input file in binary mode and read only
    
    // check if files opened successfully
    if (!*ifile) {
        cerr << "Unable to open input file '" << ifilename << "'" << endl << endl;

        delete ifile;
        ifile = nullptr;
        
        exit(1);
    }

    cout << "Input file '" << ifilename << "' opened successfully" << endl;

    return ifile;
}

ofstream* open_output_file(string ofilename) {

    ofstream* ofile = new ofstream;

    ofile->open(ofilename, fstream::binary | fstream::out); // open output file in binary mode and write only

    if (!*ofile) {
        cerr << "Unable to open output file '" << ofilename << "'" << endl << endl;

        delete ofile;
        ofile = nullptr;
        
        exit(1);
    }

    cout << "Output file '" << ofilename << "' opened successfully" << endl;

    return ofile;
}

void rl_compress(ifstream *ifile, ofstream *ofile) {

    char curr_byte;
    char write_byte;
    char byte_count;

    curr_byte = ifile->get();

    while (!ifile->eof()) {
        byte_count = 0;
        write_byte = curr_byte;

        while (curr_byte == write_byte) {
            byte_count++;
            curr_byte = ifile->get();
        }

        if (byte_count >= 2) {
            ofile->put(write_byte);
            ofile->put(write_byte);
            ofile->put(byte_count);
        } else {
            ofile->put(write_byte);
        }

    }

    cout << "Run-length file compression complete" << endl;

}

void rl_uncompress(ifstream *ifile, ofstream *ofile) { 

    char write_byte;
    char first_byte;
    char next_byte;
    char byte_count = 0;

    bool single_byte = false;

    first_byte = ifile->get();
    next_byte = ifile->get();

    write_byte = first_byte;

    //while (!(first_byte == EOF && next_byte == EOF)) {
    while (!ifile->eof()) {
        
        cout << hex << (int)first_byte << "," << (int)next_byte << "," << (int)byte_count << endl;

        if (first_byte == next_byte) {
            byte_count = ifile->get();
            first_byte = ifile->get();
            next_byte = ifile->get();

            single_byte = false;

        } else {
            byte_count = 1;
            first_byte = next_byte;
            next_byte = ifile->get();

            single_byte = true;
        }

        for (char i = 0; i < byte_count; i++) {
            ofile->put(write_byte);
        }


        write_byte = first_byte;

    }

    if (single_byte) {
        for (char i = 0; i < byte_count; i++) {
            ofile->put(write_byte);
        }
    }

    cout << "Run-length file uncompression complete" << endl;
}

int main(int argc, char *argv[]) {

    bool cli_mode = false;

    // check flags
    if (argc > 1 && argc < 4) {
        cerr << "You need to specify a input and output file" << endl;
        exit(1);

    } else if (argc == 1){
        cli_mode = true;
    }

    // check call from terminal vs terminal input

    string option;
    string ifilename;
    string ofilename;

    if (cli_mode) {

        cout << "File compression | James Lowther | Auguest 2, 2019" << endl << endl;

        cout << "'c' to compress and 'u' to uncompress" << endl;

        cout << "Enter command type: ";
        cin >> option;
        
        cout << endl << "Enter input file: ";
        cin >> ifilename;

        cout << endl << "Enter output file: ";
        cin >> ofilename;
        cout << endl;

    } else {
        option = argv[1];
        ifilename = argv[2];
        ofilename = argv[3];
    }

    // option selection

    ifstream* ifile;
    ofstream* ofile;

    if (option == "c") {
        ifile = open_input_file(ifilename);
        ofile = open_output_file(ofilename);
        rl_compress(ifile, ofile);

    } else if (option == "u") {
        ifile = open_input_file(ifilename);
        ofile = open_output_file(ofilename);
        rl_uncompress(ifile, ofile);

    } else {
        cerr << "Incorrect compression option" << endl << endl;
		
        exit(1);
    }

    if (cli_mode) {
        cout << endl;
    }

    ifile->close();
    ofile->close();

    delete ifile;
    delete ofile;

    ifile = nullptr;
    ofile = nullptr;

    return 0;

}