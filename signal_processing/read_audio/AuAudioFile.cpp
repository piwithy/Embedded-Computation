//
// Created by salyd on 11/12/2020.
//

#include "AuAudioFile.h"
#include "BadEncodingException.h"

#include <fstream>
#include <iostream>
#include <sstream>

AuAudioFile::AuAudioFile(std::string fileName, bool verbose) : fileName(std::move(fileName)), verbose(verbose),
                                                               big_endianness(false) {
    std::ifstream audioFile(this->fileName);
    this->magic_number = read_word(audioFile, 4, big_endianness);
    if (magic_number != 0x2e736e64) {
        if (verbose)
            std::cout << "Bad Endianness! (actual: Big Endian= " << std::boolalpha << big_endianness << ")"
                      << std::endl;
        big_endianness = !big_endianness;
        audioFile.seekg(0, std::ios_base::beg);
        this->magic_number = read_word(audioFile, 4, big_endianness);
    }
    this->data_offset = read_word(audioFile, 4, big_endianness);
    this->data_size = read_word(audioFile, 4, big_endianness);
    this->encoding = read_word(audioFile, 4, big_endianness);
    this->sample_rate = read_word(audioFile, 4, big_endianness);
    this->channels = read_word(audioFile, 4, big_endianness);
    if (this->verbose)
        std::cout << this << std::endl;
    read_data(audioFile);

}

AuAudioFile::AuAudioFile(AuAudioFile &&old) noexcept: fileName(std::move(old.fileName)), verbose(old.verbose),
                                                      big_endianness(old.big_endianness),
                                                      magic_number(old.magic_number), data_offset(old.data_offset),
                                                      data_size(old.data_offset), encoding(old.encoding),
                                                      sample_rate(old.sample_rate), channels(old.channels),
                                                      data(std::move(old.data)) {

    old.verbose = false;
    old.big_endianness = false;
    old.magic_number = 0;
    old.data_offset = 0;
    old.data_offset = 0;
    old.encoding = 0;
    old.sample_rate = 0;
    old.channels = 0;
}


const std::vector<float> &AuAudioFile::getData() const {
    return data;
}

uint32_t AuAudioFile::getMagicNumber() const {
    return magic_number;
}

uint32_t AuAudioFile::getDataOffset() const {
    return data_offset;
}

uint32_t AuAudioFile::getDataSize() const {
    return data_size;
}

uint32_t AuAudioFile::getEncoding() const {
    return encoding;
}

uint32_t AuAudioFile::getSampleRate() const {
    return sample_rate;
}

uint32_t AuAudioFile::getChannels() const {
    return channels;
}

uint64_t AuAudioFile::read_word(std::ifstream &file, std::size_t byte_to_read, bool bigEndian) {
    uint32_t word = 0;
    uint8_t b;
    for (std::size_t i = 0; i < byte_to_read; i++) {
        file.read(reinterpret_cast<char *>(&b), sizeof(uint8_t));
        if (bigEndian)
            word = word | (b << (((byte_to_read - 1) - i) * 8));
        else
            word = word | (b << (i * 8));
    }
    return word;
}

const std::string &AuAudioFile::getFileName() const {
    return fileName;
}

std::ostream &operator<<(std::ostream &s, const AuAudioFile &h) {
    char magic_str[5] = {
            (char) ((h.magic_number & 0xFF000000) >> 24u),
            (char) ((h.magic_number & 0x00FF0000) >> 16u),
            (char) ((h.magic_number & 0x0000FF00) >> 8u),
            (char) ((h.magic_number & 0x000000FF) >> 0u),
            '\0'
    };
    float data_size_conv;
    std::string size_unit;
    if (h.data_size < KIB) {
        data_size_conv = h.data_size;
        size_unit = "B";
    } else if (h.data_size < MIB) {
        data_size_conv = (float) h.data_size / KIB;
        size_unit = "KiB";
    } else if (h.data_size < GIB) {
        data_size_conv = (float) h.data_size / MIB;
        size_unit = "MiB";
    } else {
        data_size_conv = (float) h.data_size / GIB;
        size_unit = "GiB";
    }
    return s << "\"" << h.fileName << "\" Header:\n"
             << std::hex << "\tMagic Number\t= 0x" << h.magic_number << "\n"
             << "\tMagic String\t= \"" << magic_str << "\"\n"
             << std::dec << "\tData Offset\t\t= " << h.data_offset << "\n"
             << std::dec << "\tData size\t\t= " << data_size_conv << size_unit << "\n"
             << std::dec << "\tEncoding\t\t= " << h.encoding << "\n"
             << std::dec << "\tSample Rate\t\t= " << h.sample_rate << " sample/s \n"
             << std::dec << "\tChannels\t\t= " << h.channels
             << std::dec;
}

std::ostream &operator<<(std::ostream &s, const AuAudioFile *h) {
    char magic_str[5] = {
            (char) ((h->magic_number & 0xFF000000) >> 24u),
            (char) ((h->magic_number & 0x00FF0000) >> 16u),
            (char) ((h->magic_number & 0x0000FF00) >> 8u),
            (char) ((h->magic_number & 0x000000FF) >> 0u),
            '\0'
    };
    float data_size_conv;
    std::string size_unit;
    if (h->data_size < KIB) {
        data_size_conv = h->data_size;
        size_unit = " B";
    } else if (h->data_size < MIB) {
        data_size_conv = (float) h->data_size / KIB;
        size_unit = " KiB";
    } else if (h->data_size < GIB) {
        data_size_conv = (float) h->data_size / MIB;
        size_unit = " MiB";
    } else {
        data_size_conv = (float) h->data_size / GIB;
        size_unit = " GiB";
    }
    return s << "\"" << h->fileName << "\" Header:\n"
             << std::hex << "\tMagic Number\t= 0x" << h->magic_number << "\n"
             << "\tMagic String\t= \"" << magic_str << "\"\n"
             << std::dec << "\tData Offset\t\t= " << h->data_offset << "\n"
             << std::dec << "\tData size\t\t= " << data_size_conv << size_unit << "\n"
             << std::dec << "\tEncoding\t\t= " << h->encoding << "\n"
             << std::dec << "\tSample Rate\t\t= " << h->sample_rate << " sample/s \n"
             << std::dec << "\tChannels\t\t= " << h->channels
             << std::dec;
}

void AuAudioFile::read_data(std::ifstream &file, bool bigEndian) {
    std::size_t word_size;
    if (this->verbose)
        std::cout << "Started Reading !" << std::endl;
    switch (encoding) {
        case 2:
            word_size = 1;
            break;
        case 3:
            word_size = 2;
            break;
        case 4:
            word_size = 3;
            break;
        case 5:
            word_size = 4;
            break;
        default:
            std::ostringstream stringStream;
            stringStream << "Unsupported Encoding: " << this->encoding;
            throw BadEncodingException(stringStream.str());
    }
    file.seekg(data_offset, std::ios_base::beg);
    for (size_t data_idx = 0; data_idx < data_size / word_size; data_idx++) {
        data.push_back((float) ((short) read_word(file, word_size, bigEndian)));
    }
    data.shrink_to_fit();
    if (this->verbose)
        std::cout << "Finished Reading !" << std::endl;
}





