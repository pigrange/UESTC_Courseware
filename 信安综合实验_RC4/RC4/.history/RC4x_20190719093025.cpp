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

    buffer = new char[size + 1];
    memset(buffer, 0, size + 1);
    pbuf->sgetn(buffer, size);
    filestream.close();
    // buffer[size] = 0;
    return buffer;
  } else {
    cout << "File not exist." << endl;
    return nullptr;
  }
}

char *writeFile(vector<uint8_t> msg, const char *filepath) {
  ofstream outstream;
  outstream.open(filepath);
  for (auto i : msg) outstream << i;
  outstream.close();
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <key> <filepath>" << endl;
    return 1;
  }
  auto filepath = argv[1];
  char *buffer = readFile(filepath);
  auto keylen = string(argv[2]).length(), msglen = string(buffer).length();

  RC4 rc4;
  vector<uint8_t> key(keylen, 0), msg(msglen, 0);
  key.assign(argv[2], argv[2] + keylen);
  msg.assign(buffer, buffer + msglen);

  cout << "message: " << endl;
  for_each(msg.begin(), msg.end(), [](uint8_t i) { cout << i; });
  cout << endl;
  rc4.reset(key, keylen);
  rc4.crypt(msg, msg, msglen);
  cout << "encrypt: " << endl;
  for (auto i : msg) cout << i;
  cout << endl;

  rc4.reset(key, keylen);
  rc4.crypt(msg, msg, msglen);
  cout << "decrypt: " << endl;
  for_each(msg.begin(), msg.end(), [](uint8_t i) { cout << i; });
  writeFile(msg, filepath);
  cout << endl;
  return 0;
}