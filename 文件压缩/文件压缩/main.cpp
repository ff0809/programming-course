#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <chrono> 
using namespace std;

//LZ4常量定义
const int MIN_MATCH = 4;
const int MAX_MATCH = 0xFFFF; 
const int HASH_TABLE_SIZE = 1 << 16;
const int WINDOW_SIZE = 1 << 16;

//哈希函数
inline uint32_t hash_func(const uint8_t* data) {
    uint32_t val = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]; 
    return (val * 2654435761U) & (HASH_TABLE_SIZE - 1); 
}

//匹配长度计算
size_t find_match_length(const vector<uint8_t>& input, size_t pos1, size_t pos2, size_t max_len) {
    size_t len = 0;
    size_t end = min(pos1 + max_len, input.size());
    while (pos1 + len < end && pos2 + len < input.size() && input[pos1 + len] == input[pos2 + len]) {
        len++;
    }
    return len;
}

//压缩函数
vector<uint8_t> lz4_compress(const vector<uint8_t>& input) {
    vector<uint8_t> output;
    const size_t input_size = input.size();
    if (input_size == 0) return output;

    vector<int> hash_table(HASH_TABLE_SIZE, -1);
    size_t pos = 0;
    size_t literal_start = 0; 

    while (pos < input_size) {
        size_t best_match_len = 0;
        int best_offset = 0;

        if (pos + MIN_MATCH <= input_size) {
            uint32_t hash = hash_func(input.data() + pos);
            int candidate_pos = hash_table[hash];

            if (candidate_pos != -1 && pos > static_cast<size_t>(candidate_pos)
                && pos - candidate_pos <= WINDOW_SIZE) {

                size_t max_len = min<size_t>(MAX_MATCH, input_size - pos);
                size_t match_len = find_match_length(input, pos, candidate_pos, max_len);

                if (match_len >= MIN_MATCH && match_len > best_match_len) {
                    best_match_len = match_len;
                    best_offset = static_cast<int>(pos - candidate_pos);
                }
            }

            hash_table[hash] = static_cast<int>(pos);
        }

        if (best_match_len >= MIN_MATCH) {
            size_t literal_len = pos - literal_start;
            uint8_t token = 0;

            if (literal_len < 15) {
                token |= static_cast<uint8_t>(literal_len << 4);
            }
            else {
                token |= 0xF0;
            }

            size_t encoded_match_len = best_match_len - MIN_MATCH;
            if (encoded_match_len < 15) {
                token |= static_cast<uint8_t>(encoded_match_len);
            }
            else {
                token |= 0x0F;
            }

            output.push_back(token);

            if (literal_len >= 15) {
                size_t remain = literal_len - 15;
                while (remain >= 0xFF) {
                    output.push_back(0xFF);
                    remain -= 0xFF;
                }
                output.push_back(static_cast<uint8_t>(remain));
            }

            if (literal_len > 0) {
                output.insert(output.end(), input.begin() + literal_start, input.begin() + pos);
            }

            output.push_back(static_cast<uint8_t>(best_offset & 0xFF));
            output.push_back(static_cast<uint8_t>((best_offset >> 8) & 0xFF));

            if (encoded_match_len >= 15) {
                size_t remain = encoded_match_len - 15;
                while (remain >= 0xFF) {
                    output.push_back(0xFF);
                    remain -= 0xFF;
                }
                output.push_back(static_cast<uint8_t>(remain));
            }

            pos += best_match_len;
            literal_start = pos;
        }
        else {
            if (pos == input_size - 1 || input_size - pos < MIN_MATCH) {
                size_t literal_len = input_size - literal_start;
                if (literal_len > 0) {
                    uint8_t token = static_cast<uint8_t>(min<size_t>(literal_len, 15) << 4);
                    output.push_back(token);

                    if (literal_len >= 15) {
                        size_t remain = literal_len - 15;
                        while (remain >= 0xFF) {
                            output.push_back(0xFF);
                            remain -= 0xFF;
                        }
                        output.push_back(static_cast<uint8_t>(remain));
                    }

                    output.insert(output.end(), input.begin() + literal_start, input.begin() + input_size);
                }
                break;
            }
            pos++;
        }
    }

    return output;
}

//解压函数
vector<uint8_t> lz4_decompress(const vector<uint8_t>& input) {
    vector<uint8_t> output;
    const size_t input_size = input.size();
    if (input_size == 0) return output;
    size_t pos = 0;
    while (pos < input_size) {
        uint8_t token = input[pos++];
        size_t literal_len = (token >> 4) & 0x0F;
        size_t match_len = token & 0x0F;
        if (literal_len == 0x0F) {
            while (pos < input_size) {
                uint8_t ext = input[pos++];
                literal_len += ext;
                if (ext != 0xFF) break;
            }
        }
        if (pos + literal_len > input_size) {
            literal_len = input_size - pos;
        }
        if (literal_len > 0) {
            output.insert(output.end(), input.begin() + pos, input.begin() + pos + literal_len);
            pos += literal_len;
        }
        if (pos >= input_size) break;
        if (pos + 1 >= input_size) {
            break;
        }

        uint16_t offset = static_cast<uint16_t>(input[pos]) | (static_cast<uint16_t>(input[pos + 1]) << 8);
        pos += 2;
        if (offset == 0 || offset > output.size()) {
            break;
        }

        if (match_len == 0x0F) {
            while (pos < input_size) {
                uint8_t ext = input[pos++];
                match_len += ext;
                if (ext != 0xFF) break;
            }
        }
        match_len += MIN_MATCH;
        size_t copy_pos = output.size() - offset;
        for (size_t i = 0; i < match_len; ++i) {
            uint8_t byte = output[copy_pos + (i % offset)];
            output.push_back(byte);
        }
    }

    return output;
}

//验证解压文件大小与原文件是否匹配
bool verify_compression(const vector<uint8_t>& original, const vector<uint8_t>& decompressed) {
    if (original.size() != decompressed.size()) {
        cout << "Verify failed: size mismatch. original=" << original.size()
            << ", decompressed=" << decompressed.size() << "\n";
        return false;
    }
    return true;
}

//以二进制方式读取文件
vector<uint8_t> read_file(const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Cannot open file: " << filename << "\n";
        exit(1);
    }
    fin.seekg(0, ios::end);
    size_t size = static_cast<size_t>(fin.tellg());
    fin.seekg(0, ios::beg);

    vector<uint8_t> data(size);
    if (size > 0) fin.read(reinterpret_cast<char*>(data.data()), size);
    fin.close();
    return data;
}

//以二进制方式写入文件
void write_file(const string& filename, const vector<uint8_t>& data) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Cannot write file: " << filename << "\n";
        exit(1);
    }
    if (!data.empty()) fout.write(reinterpret_cast<const char*>(data.data()), data.size());
    fout.close();
}

//带参的主函数
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <input> <output> <zip|unzip>\n";
        cerr << "Example: " << argv[0] << " input.txt output.lz4 zip\n";
        cout << "Press Enter to exit...";
        cin.get();
        return -1;
    }

    string input_file = argv[1];
    string output_file = argv[2];
    string cmd = argv[3];

    try {
        if (cmd == "zip") {
            vector<uint8_t> data = read_file(input_file);
            cout << "Original size: " << data.size() << " bytes\n";

            auto t0 = chrono::high_resolution_clock::now();
            vector<uint8_t> compressed = lz4_compress(data);
            auto t1 = chrono::high_resolution_clock::now();

            write_file(output_file, compressed);

            chrono::duration<double> dur = t1 - t0;
            double seconds = dur.count();
            double mb = static_cast<double>(data.size()) / (1024.0 * 1024.0);
            double speed = seconds > 0.0 ? mb / seconds : 0.0;

            cout << "Compression done. Compressed size: " << compressed.size() << " bytes\n";
            cout << "Compression ratio: " << (data.empty() ? 0.0 : (double)compressed.size() / data.size() * 100.0) << "%\n";
            cout << "Time: " << seconds << " s, Speed: " << speed << " MB/s\n";

            auto vt0 = chrono::high_resolution_clock::now();
            vector<uint8_t> test_decompressed = lz4_decompress(compressed);
            auto vt1 = chrono::high_resolution_clock::now();
            chrono::duration<double> vdur = vt1 - vt0;
            cout << "Decompression for verify time: " << vdur.count() << " s\n";

            if (verify_compression(data, test_decompressed)) {
                cout << "Verify: OK\n";
            }
            else {
                cout << "Verify: FAILED\n";
            }
        }
        else if (cmd == "unzip") {
            vector<uint8_t> compressed = read_file(input_file);
            cout << "Compressed file size: " << compressed.size() << " bytes\n";

            auto t0 = chrono::high_resolution_clock::now();
            vector<uint8_t> decompressed = lz4_decompress(compressed);
            auto t1 = chrono::high_resolution_clock::now();
            write_file(output_file, decompressed);

            chrono::duration<double> dur = t1 - t0;
            double seconds = dur.count();
            double mb = static_cast<double>(decompressed.size()) / (1024.0 * 1024.0);
            double speed = seconds > 0.0 ? mb / seconds : 0.0;

            cout << "Decompression done. Decompressed size: " << decompressed.size() << " bytes\n";
            cout << "Time: " << seconds << " s, Speed: " << speed << " MB/s\n";
        }
        else {
            cerr << "Unknown command. Supported: zip, unzip\n";
            return -1;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return -1;
    }
    return 0;
}