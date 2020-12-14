//
// Created by salyd on 11/12/2020.
//

#ifndef SIGNAL_PROCESSING_AUAUDIOFILE_H
#define SIGNAL_PROCESSING_AUAUDIOFILE_H

#define KIB 1024
#define MIB 1048576
#define GIB 1073741824

#include <string>
#include <array>
#include <vector>


class AuAudioFile {
public:
    explicit AuAudioFile(std::string fileName, bool verbose = true);

    AuAudioFile(AuAudioFile &&) noexcept; // move constructor

    AuAudioFile(const AuAudioFile &) = default; // copy constructor

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

private:
    bool verbose, big_endianness;
    std::vector<std::array<float, 512>> bins;
    std::vector<float> data;
    uint64_t magic_number;
    uint64_t data_offset;
    uint64_t data_size;
    uint64_t encoding;
    uint64_t sample_rate;
    uint64_t channels;

    std::string fileName;

    static uint64_t read_word(std::ifstream &file, std::size_t byte_to_read = 4, bool bigEndian = true);

    void read_data(std::ifstream &file, bool bigEndian = true);


};


#endif //SIGNAL_PROCESSING_AUAUDIOFILE_H
