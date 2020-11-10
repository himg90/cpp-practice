//
// Created by Himanshu Gupta on 10/11/20.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std;

struct file_part {
    string filename;
    int start_offset;
    int length;
};

int main(int argc, char** argv) {
    int CHUNK_SIZE  = 1000;
    vector<vector<file_part>> chunks(1);
    int current_chunk_size =0;

    vector<string> filenames = {"../input/my.txt"};

    for(auto it=filenames.begin(); it != filenames.end(); it++) {
        ifstream file;
        file.open(*it);
        if(!file.is_open()) {
            cout << "Error: Could not open file - "  << *it << endl;
            continue;
        }
        string line;
        int start_offset = 0;
        int bytes_read = 0;
        while(file.good()) {
            getline(file, line);
            bytes_read += (line.size() + (file.eof()?0:1));
            if(current_chunk_size + bytes_read >= CHUNK_SIZE) {
                //add current file_part to chunk
                chunks.back().push_back(file_part{.filename = *it, .start_offset = start_offset, bytes_read});
                current_chunk_size += bytes_read;

                //create new chunk
                chunks.push_back(vector<file_part>());
                current_chunk_size  = 0;
                start_offset += bytes_read;
                bytes_read = 0;
            } else if (file.eof()) {
                //add current file_part to chunk
                chunks.back().push_back(file_part{.filename = *it, .start_offset = start_offset, bytes_read});
                current_chunk_size += bytes_read;
            }
        }
    }

    int chunk_idx = 0;
    for(auto chunk_it = chunks.begin(); chunk_it != chunks.end(); chunk_it++)  {
        ++chunk_idx;
        for(auto file_part_it = chunk_it->begin(); file_part_it != chunk_it->end(); file_part_it++) {
            cout << "Chunk: " << chunk_idx << " Filename: " << file_part_it->filename
                                            << " start_offset: " << file_part_it->start_offset
                                            << " length: " << file_part_it->length << endl;
        }
    }

    return 0;
}