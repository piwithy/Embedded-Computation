//
// Created by salyd on 14/12/2020.
//
#include "AuAudioFile.h"
#include "common.h"
#include "stft/stft.h"
#include <tuple>
#include <iostream>
#include <fstream>
#include <signal_utils.h>
#include <fft/fft.h>
#include <execution>

AuAudioFile::AuAudioFile(std::string fileName, std::string style, bool verbose) : fileName(std::move(fileName)),
                                                                                  verbose(verbose),
                                                                                  big_endianness(false),
                                                                                  style(std::move(style)) {
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
    process_signal();
    if (audioFile.is_open())
        audioFile.close();
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
    if (h.data_size < KiB) {
        data_size_conv = h.data_size;
        size_unit = "B";
    } else if (h.data_size < MiB) {
        data_size_conv = (float) h.data_size / KiB;
        size_unit = "KiB";
    } else if (h.data_size < GiB) {
        data_size_conv = (float) h.data_size / MiB;
        size_unit = "MiB";
    } else {
        data_size_conv = (float) h.data_size / GiB;
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
    if (h->data_size < KiB) {
        data_size_conv = h->data_size;
        size_unit = " B";
    } else if (h->data_size < MiB) {
        data_size_conv = (float) h->data_size / KiB;
        size_unit = " KiB";
    } else if (h->data_size < GiB) {
        data_size_conv = (float) h->data_size / MiB;
        size_unit = " MiB";
    } else {
        data_size_conv = (float) h->data_size / GiB;
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
    std::size_t word_size = 0;
    if (this->verbose)
        std::cout << "Started Reading !" << std::endl;
    if (encoding == 3)
        word_size = 2;
    file.seekg(data_offset, std::ios_base::beg);
    for (size_t data_idx = 0; data_idx < data_size / word_size; data_idx++) {
        data.push_back((float) ((short) read_word(file, word_size, bigEndian)));
    }
    data.shrink_to_fit();
    if (this->verbose) {
        std::cout << "Finished Reading !" << std::endl;
        /*std::cout << data[0] << " " << data[100] << " " << data.back() << std::endl;
        std::cout << data.size() << std::endl;*/
    }
}

const std::vector<std::vector<Complex>> &AuAudioFile::getBins() const {
    return bins;
}

const std::vector<double> &AuAudioFile::getBinsAverage() const {
    return bins_average;
}

const std::vector<double> &AuAudioFile::getBinsStandardDeviation() const {
    return bins_standard_deviation;
}

void AuAudioFile::process_signal() {
    if (this->verbose)
        std::cout << "Started Signal Processing !" << std::endl;
    std::vector<double> average;
    std::vector<double> std_dev;
    std::size_t nBins = (data.size() / N);
    auto window = hamming_window();
    for (std::size_t bin_idx = 0; bin_idx < nBins; bin_idx++) {

        std::vector<Complex> even_bin(N), odd_bin(N);
        auto even_start = data.cbegin() + bin_idx * N;
        auto odd_start = data.cbegin() + (bin_idx * N) + (N / 2);
        std::copy(even_start, even_start + N, even_bin.begin());
        std::copy(odd_start, odd_start + N, odd_bin.begin());

        windowing(window, even_bin);
        windowing(window, odd_bin);
        ite_dit_fft(even_bin);
        ite_dit_fft(odd_bin);

        std::tuple<double, double> bin_avg_stddev_even = compute_avg_stddev(even_bin);
        std::tuple<double, double> bin_avg_stddev_odd = compute_avg_stddev(odd_bin);

        average.push_back(std::get<0>(bin_avg_stddev_even));
        std_dev.push_back(std::get<1>(bin_avg_stddev_even));

        bins_average.push_back(std::get<0>(bin_avg_stddev_odd));
        bins_standard_deviation.push_back(std::get<1>(bin_avg_stddev_odd));

        bins.push_back(even_bin);
        bins.push_back(odd_bin);
    }

    bins.shrink_to_fit();
    bins_average.shrink_to_fit();
    bins_standard_deviation.shrink_to_fit();
    if (this->verbose)
        std::cout << "Finished Signal Processing !" << std::endl;
}

std::tuple<double, double> AuAudioFile::compute_avg_stddev(const std::vector<Complex> &x) {
    double avg = std::reduce(std::execution::par, x.cbegin(), x.cend()).real() / x.size();
    double stddev = std::sqrt(std::transform_reduce(
            std::execution::par,
            x.cbegin(),
            x.cend(),
            0.,
            std::plus(),
            [avg](Complex c) {
                double c_r = c.real();
                return ((c_r - avg) * (c_r - avg));
            }) / (double) (x.size() - 1));
    return std::make_tuple(avg, stddev);
}

const std::string &AuAudioFile::getStyle() const {
    return style;
}

