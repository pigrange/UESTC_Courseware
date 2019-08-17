#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class RC4 {
 public:
  explicit RC4(void){};
  void reset(const vector<uint8_t> &key, size_t len);
  void crypt(const vector<uint8_t> &in, vector<uint8_t> &out, size_t len);
  ~RC4(void){};

 private:
  array<uint8_t, 256> sbox;
  uint8_t idx1;
  uint8_t idx2;
  explicit RC4(const RC4 &) = delete;
  explicit RC4(const RC4 &&) = delete;
  const RC4 &operator=(const RC4 &) = delete;
  const RC4 &&operator=(const RC4 &&) = delete;
};

void RC4::reset(const vector<uint8_t> &key, size_t len) {
  uint8_t j = 0;

  for (auto i = 0; i < sbox.size(); i++) sbox[i] = i;
  idx1 = 0;
  idx2 = 0;

  for (auto i = 0; i < sbox.size(); i++) {
    j += sbox[i] + key[i % len];
    swap(sbox[i], sbox[j]);
  }
}

void RC4::crypt(const vector<uint8_t> &in, vector<uint8_t> &out, size_t len) {
  uint8_t j = 0;

  for (auto i = 0; i < len; i++) {
    idx1++;
    idx2 += sbox[idx1];
    swap(sbox[idx1], sbox[idx2]);
    j = sbox[idx1] + sbox[idx2];
    out[i] = in[i] ^ sbox[j];
  }
}

char *readFile(const char *filepath) {
  ifstream filestream;
  filestream.open(filepath);

  if (filestream.is_open()) {
    cout << "Reading file..." << endl;
    filebuf *pbuf;
    long size;
    char *buffer;
    //获取filestr对象的指针
    pbuf = filestream.rdbuf();

    // 调用buffer对象方法获取文件大小
    size = pbuf->pubseekoff(0, ios::end, ios::in);
    pbuf->pubseekpos(0, ios::in);

    buffer = new char[size];
    pbuf->sgetn(buffer, size);
    buffer[size] = 0;

    // char small_buffer[1024];
    // char total_buffer[2048];
    // memset(total_buffer, 0, 2048 * sizeof(char));
    // int length = 0;
    // while (!filestream.eof()) {
    //   filestream.getline(small_buffer, 1024);
    //   memcpy(&total_buffer[length], small_buffer, strlen(small_buffer) + 1);
    //   length += strlen(small_buffer) + 1;
    // }

    filestream.close();
    return buffer;
  } else {
    cout << "File not exist." << endl;
    return nullptr;
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <key> <filepath>" << endl;
    return 1;
  }
  auto filepath = argv[2];
  char *buffer = readFile(filepath);
  auto keylen = string(argv[1]).length(), msglen = string(buffer).length();

  RC4 rc4;
  vector<uint8_t> key(keylen, 0), msg(msglen, 0);
  key.assign(argv[1], argv[1] + keylen);
  msg.assign(buffer, buffer + msglen);

  cout << "message: ";
  for_each(msg.begin(), msg.end(), [](uint8_t i) { cout << i; });
  cout << endl;
  rc4.reset(key, keylen);
  rc4.crypt(msg, msg, msglen);
  cout << "encrypt: ";
  for (auto i : msg) {
    cout << hex << (i >> 4);
    cout << hex << (i & 0x0f) << " ";
  }
  cout << endl;
  rc4.reset(key, keylen);
  rc4.crypt(msg, msg, msglen);
  cout << "decrypt: ";
  for_each(msg.begin(), msg.end(), [](uint8_t i) { cout << i; });
  cout << endl;

  return 0;
}