//
// Created by salyd on 14/12/2020.
//

#ifndef SIGNAL_PROCESSING_AUAUDIOFILE_H
#define SIGNAL_PROCESSING_AUAUDIOFILE_H


#include <string>
#include <vector>
#include "common.h"

class AuAudioFile {

public:
    explicit AuAudioFile(std::string fileName, std::string style, bool verbose = true);

    ~AuAudioFile() = default;

    [[nodiscard]] const std::vector<float> &getData() const;

    [[nodiscard]] uint32_t getMagicNumber() const;

    [[nodiscard]] uint32_t getDataOffset() const;

    [[nodiscard]] uint32_t getDataSize() const;

    [[nodiscard]] uint32_t getEncoding() const;

    [[nodiscard]] uint32_t getSampleRate() const;

    [[nodiscard]] uint32_t getChannels() const;

    const std::string &getFileName() const;

    friend std::ostream &operator<<(std::ostream &s, const AuAudioFile &h);

    friend std::ostream &operator<<(std::ostream &s, const AuAudioFile *h);

    const std::vector<std::vector<Complex>> &getBins() const;

    const std::vector<double> &getBinsAverage() const;

    const std::vector<double> &getBinsStandardDeviation() const;

    const std::string &getStyle() const;

private:
    bool verbose, big_endianness;
    std::vector<float> data;
    std::vector<std::vector<Complex>> bins;
    std::vector<double> bins_average;
    std::vector<double> bins_standard_deviation;
    std::string style;
    uint64_t magic_number;
    uint64_t data_offset;
    uint64_t data_size;
    uint64_t encoding;
    uint64_t sample_rate;
    uint64_t channels;

    std::string fileName;

    static uint64_t read_word(std::ifstream &file, std::size_t byte_to_read = 4, bool bigEndian = true);

    void read_data(std::ifstream &file, bool bigEndian = true);

    void process_signal();

    static std::tuple<double, double> compute_avg_stddev(const std::vector<Complex> &x);


};


#endif //SIGNAL_PROCESSING_AUAUDIOFILE_H
