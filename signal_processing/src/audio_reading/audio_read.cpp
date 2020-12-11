//
// Created by salyd on 11/12/2020.
//

#include <fstream>
#include <memory>
#include <iostream>
#include "audio_read.h"

uint32_t read_word(std::ifstream &file, bool bigEndian) {
    uint32_t word = 0;
    uint8_t b;
    for (std::size_t i = 0; i < 4; i++) {
        file.read(reinterpret_cast<char *>(&b), sizeof(uint8_t));
        if (bigEndian)
            word = word | (b << ((3 - i) * 8));
        else
            word = word | (b << (i * 8));
    }
    return word;
}

std::ostream &operator<<(std::ostream &s, const auHeader *h) {
    return s << std::hex
             << "AU Header:\n"
             << "\tMagic Number\t=0x" << h->magic_number << "\n"
             << "\tData Offset\t=0x" << h->data_offset << "\n"
             << "\tData size\t=0x" << h->data_size << "\n"
             << "\tEncoding\t=0x" << h->encoding << "\n"
             << "\tSample Rate\t=0x" << h->sample_rate << "\n"
             << "\tChannels\t=0x" << h->channels
             << std::dec;
}


std::vector<float> readAuFile(const std::string &fileName) {
    FILE *fin = fopen(fileName.c_str(), "rb");
    std::ifstream myFile(fileName);
    std::vector<float> data;
    std::unique_ptr<auHeader> header = std::make_unique<auHeader>();

    uint32_t word = 0;
    uint8_t b;
    header->magic_number = read_word(myFile);
    header->data_offset = read_word(myFile);
    header->encoding = read_word(myFile);
    header->sample_rate = read_word(myFile);
    header->channels = read_word(myFile);

    std::cout << std::hex << header << std::endl;

    return data;

}