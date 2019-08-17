#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

unsigned char *init_sbox(const char K[], int klen, int slen) {
  auto *S = (unsigned char *)malloc(slen + 1);
  int pos = 0;
  while (pos < slen) S[pos++] = pos - 1;
  int i = -1, j = 0, temp;
  while (i++ < slen - 1) {
    j = (j + S[i] + K[i % klen]) % slen;
    temp = S[i];
    S[i] = S[j];
    S[j] = temp;
  }
  return S;
}

unsigned char *rc4_crypt(const unsigned char M[], long mlen, unsigned char S[],
                         int slen) {
  auto *result = (unsigned char *)malloc(mlen + 1);
  int i = 0, j = 0, t;
  for (int k = 0; k < mlen; k++) {
    //生成i和j
    i = (j + 1) % slen;
    j = (j + S[i]) % slen;
    //交换S[i]和S[j]的值
    int temp = S[i];
    S[i] = S[j];
    S[j] = temp;
    t = (S[i] + S[j]) % slen;
    result[k] = M[k] ^ S[t];

    printf("result[%d] is %d\n", k, result[k]);
    cout << "M[k] is " << (int)M[k] << endl;
    cout << "s[t] is " << (int)S[t] << endl;
    cout << "-----------------------------" << endl;
  }
  result[mlen] = 0;
  return result;
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
    filestream.close();
    // buffer[size] = 0;
    return buffer;
  } else {
    cout << "File not exist." << endl;
    return nullptr;
  }
}

char *writeFile(unsigned char *buffer, const char *filepath) {
  ofstream outfile;
  outfile.open(filepath);
  outfile << buffer;
  outfile.close();
}

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    cout << "Invalid parameter" << endl;
    return 0;
  }

  char *buffer;
  const char *filepath = argv[1];
  const char *key = argv[2];

  //加密
  buffer = readFile(filepath);
  if (!buffer) {
    cout << "Read failed" << endl;
    return 0;
  }

  long len = strlen(buffer);
  cout << "msg len is" << len << endl;
  unsigned char *sbox = init_sbox(key, strlen(key), 256);
  unsigned char *result =
      rc4_crypt((unsigned char *)buffer, len - 3, sbox, 256);
  cout << result << endl;
  cout << "result len is " << strlen((char *)result) << endl;
  writeFile(result, filepath);
  return 0;
}
