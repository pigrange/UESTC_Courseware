#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class RC4 {
 private:
  array<uint8_t, 256> sbox;
  uint8_t idx1;
  uint8_t idx2;

 public:
  void reset(const vector<uint8_t> &key, size_t len) {
    idx1 = 0;
    idx2 = 0;
    uint8_t j = 0;
    for (auto i = 0; i < sbox.size(); i++) sbox[i] = i;
    for (auto i = 0; i < sbox.size(); i++) {
      j += sbox[i] + key[i % len];
      swap(sbox[i], sbox[j]);
    }
  }

  void crypt(const vector<uint8_t> &in, vector<uint8_t> &out, size_t len) {
    uint8_t j = 0;
    for (auto i = 0; i < len; i++) {
      idx1++;
      idx2 += sbox[idx1];
      swap(sbox[idx1], sbox[idx2]);
      j = sbox[idx1] + sbox[idx2];
      out[i] = in[i] ^ sbox[j];
    }
  }
};

class FileHelper {
 public:
  vector<char> readPlain(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    vector<char> result;
    if (file != nullptr) {
      cout << "Reading file..." << endl;
      char a_char;
      while (!feof(file)) {
        fscanf(file, "%c", &a_char);
        result.emplace_back(a_char);
      }
      result.erase(result.end() - 1);
    } else {
      cout << "File not exist." << endl;
    }
    return result;
  }

  vector<char> readCiphertext(const char *filepath, int *len) {
    vector<char> cipher = readPlain(filepath);
    vector<char> res;
    int temp = 0, count = 0;
    for (int i = 0; i < cipher.size(); i++) {
      if (cipher[i] != ' ') {
        temp = temp * 10 + (cipher[i] - 48);
      } else {
        auto ch = (unsigned char)temp;
        count++;
        temp = 0;
        res.push_back(ch);
      }
    }
    *len = count;
    return res;
  }

  void writeCiphertext(vector<int> msg, const char *filepath) {
    ofstream outstream;
    outstream.open(filepath);
    for (auto i : msg) outstream << i << " ";
    outstream.close();
  }

  void writePlaintext(vector<uint8_t> msg, const char *filepath) {
    ofstream outstream;
    outstream.open(filepath);
    for (auto i : msg) outstream << i;
    outstream.close();
  }
};

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<options> <filepath> <key>" << endl;
    return 1;
  }

  FileHelper helper;

  int msglen;
  auto option = string(argv[1]);
  auto filepath = argv[2];
  auto keylen = string(argv[3]).length();

  vector<char> buffer;
  if (option == "-en") {
    buffer = helper.readPlain(filepath);
    msglen = buffer.size();
  } else if (option == "-de") {
    buffer = helper.readCiphertext(filepath, &msglen);
    cout << endl;
  } else {
    cout << "invaliate argument" << endl;
    return 1;
  }

  RC4 rc4;
  vector<uint8_t> key(keylen, 0), msg(msglen, 0);
  key.assign(argv[3], argv[3] + keylen);
  msg.assign(buffer.begin(), buffer.begin() + msglen);
  rc4.reset(key, keylen);
  rc4.crypt(msg, msg, msglen);

  if (option == "-en") {
    vector<int> msgCode;
    for (auto i : msg) {
      cout << (int)i << " ";
      msgCode.push_back(i);
    }
    helper.writeCiphertext(msgCode, filepath);
  } else {
    vector<uint8_t> msgRes;
    for (auto i : msg) msgRes.push_back(i);
    cout << msgRes.data() << endl;
    helper.writePlaintext(msgRes, filepath);
  }
  return 0;
}