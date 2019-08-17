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

char *readPlain(const char *filepath) {
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
    cout << "size is " << size << endl;
    buffer = new char[size + 1];
    memset(buffer, 0, size + 1);
    pbuf->sgetn(buffer, size);
    filestream.close();
    return buffer;
  } else {
    cout << "File not exist." << endl;
    return nullptr;
  }
}

char *readCiphertext(const char *filepath, int *len) {
  string cipher = string(readPlain(filepath));
  cout << "cipher is " << cipher << endl;
  string res = "";
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
  char *result = (char *)res.c_str();
  for (int i = 0; i < count; i++) {
    cout << result[i];
  }
  cout << "result is" << result;
  return (char *)res.c_str();
}

char *writeCiphertext(vector<int> msg, const char *filepath) {
  ofstream outstream;
  outstream.open(filepath);
  for (auto i : msg) outstream << i << " ";
  outstream.close();
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<options> <filepath> <key>" << endl;
    return 1;
  }
  auto option = string(argv[1]);
  auto filepath = argv[2];
  cout << "option is " << option << endl;

  const char *buffer = nullptr;
  if (option == "encrypt") {
    buffer = readPlain(filepath);
  } else if (option == "decrypt") {
    buffer = readCiphertext(filepath);
  } else {
    cout << "invaliate argument" << endl;
    return 1;
  }

  auto keylen = string(argv[3]).length(), msglen = string(buffer).length();

  RC4 rc4;
  vector<uint8_t> key(keylen, 0), msg(msglen, 0);
  key.assign(argv[3], argv[3] + keylen);
  msg.assign(buffer, buffer + msglen);

  cout << "message: " << endl;
  for_each(msg.begin(), msg.end(), [](uint8_t i) { cout << i; });
  cout << endl;
  rc4.reset(key, keylen);
  rc4.crypt(msg, msg, msglen);
  cout << "encrypt: " << endl;

  vector<int> msgCode;
  // i 为unsigned char,这里分别取其高4位和低4位
  for (auto i : msg) {
    // cout << hex << (i >> 4);
    // cout << hex << (i & 0x0f) << " ";
    cout << hex << i << " ";
    msgCode.push_back(i);
  }
  cout << endl;
  writeCiphertext(msgCode, filepath);

  // rc4.reset(key, keylen);
  // rc4.crypt(msg, msg, msglen);
  // cout << "decrypt: " << endl;
  // for_each(msg.begin(), msg.end(), [](uint8_t i) { cout << i; });
  cout << endl;
  return 0;
}