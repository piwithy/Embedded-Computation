//
// Created by salyd on 11/12/2020.
//

#ifndef SIGNAL_PROCESSING_AUDIO_READ_H
#define SIGNAL_PROCESSING_AUDIO_READ_H

//32 bit word (unsigned)    field  Description/Content Hexadecimal numbers in C notation
//0                        magic number   the value 0x2e736e64 (four ASCII characters ".snd")
//1                        data offset    the offset to the data in bytes, must be divisible by 8. The minimum valid number is 24 (decimal), since this is the header length (six 32-bit words) with no space reserved for extra information (the annotation field). The minimum valid number with an annotation field present is 32 (decimal).
//2                        data size  data size in bytes. If unknown, the value 0xffffffff should be used.
//3                        encoding   Data encoding format:
//
//1 = 8-bit G.711 μ-law
//2 = 8-bit linear PCM
//3 = 16-bit linear PCM
//4 = 24-bit linear PCM
//5 = 32-bit linear PCM
//6 = 32-bit IEEE floating point
//7 = 64-bit IEEE floating point
//8 = Fragmented sample data
//9 = DSP program
//10 = 8-bit fixed point
//11 = 16-bit fixed point
//12 = 24-bit fixed point
//13 = 32-bit fixed point
//18 = 16-bit linear with emphasis
//19 = 16-bit linear compressed
//20 = 16-bit linear with emphasis and compression
//21 = Music kit DSP commands
//23 = 4-bit compressed using the ITU-T G.721 ADPCM voice data encoding scheme
//24 = ITU-T G.722 SB-ADPCM
//25 = ITU-T G.723 3-bit ADPCM
//26 = ITU-T G.723 5-bit ADPCM
//27 = 8-bit G.711 A-law
//
//4    sample rate    the number of samples/second, e.g., 8000
//5    channels   the number of interleaved channels, e.g., 1 for mono, 2 for stereo; more channels possible, but may not be supported by all readers.

#include <string>
#include <vector>

typedef struct au_head {
    uint32_t magic_number;
    uint32_t data_offset;
    uint32_t data_size;
    uint32_t encoding;
    uint32_t sample_rate;
    uint32_t channels;
} auHeader;

std::ostream &operator<<(std::ostream &s, const auHeader *h);


uint32_t read_word(std::ifstream &file, bool bigEndian = true);

std::vector<float> readAuFile(const std::string &fileName);


#endif //SIGNAL_PROCESSING_AUDIO_READ_H
