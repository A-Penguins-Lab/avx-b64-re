#include <iostream>
#include <string>

const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

// Encoder
std::string b64_encoder(std::string inputString) {
	std::string b64String;
	long unsigned int l = inputString.length();
	std::cout << "Input string" << inputString << "";

	for (unsigned int i = 0; i < l; i+=3) {
		int s  = (int)inputString[i];
      	int s1 = (i + 1 < l) ? (int)inputString[i + 1] : 0;
      	int s2 = (i + 2 < l) ? (int)inputString[i + 2] : 0;

		long unsigned int a = s / 4;
		long unsigned int b = (s * 16) % 64 + (s1 / 16);
		long unsigned int c = (s1 * 4) % 64 + (s2 / 64);
		long unsigned int d = (s2 % 64);

		b64String += base64_chars[a];
		b64String += base64_chars[b];

		if (i + 1 < l) {
			b64String += base64_chars[c];
		} else {
			b64String += "=";
		}

		if (i + 2 < l) {
			b64String += base64_chars[d];
		} else {
			b64String += "=";
		}
	}

	return b64String;
}

// Decoder
std::string b64_decoder(std::string b64String) {
  std::string decodedString;
  std::cout << b64String << std::endl;

  long unsigned int dLength = b64String.length();
  for(unsigned int i = 0; i < dLength; i += 4) {
		char c0 = b64String[i];
		char c1 = b64String[i + 1];
		char c2 = (i + 2 < dLength) ? b64String[i + 2] : '=';
		char c3 = (i + 3 < dLength) ? b64String[i + 3] : '=';

		long unsigned int s  = base64_chars.find(c0);
		long unsigned int s1 = base64_chars.find(c1);
		long unsigned int s2 = (c2 != '=') ? base64_chars.find(c2) : 0;
		long unsigned int s3 = (c3 != '=') ? base64_chars.find(c3) : 0;

		std::cout << s << " " << s1 << " " << s2 << " " << s3 << "\n";

		// First byte
		decodedString += static_cast<char>((s * 4) + (s1 / 16));

		// Second byte (if no padding at c2)
		if (c2 != '=') {
			decodedString += static_cast<char>((s1 % 16) * 16 + (s2 / 4));
		}

		// Third byte (if no padding at c3)
		if (c3 != '=') {
			decodedString += static_cast<char>((s2 % 4) * 64 + s3);
		}
  }

  return decodedString;
}


int main () {
	std::cout << "In main" << std::endl;
	std::string dummy = b64_encoder("Man");
	std::cout <<"Man" << " " << dummy << std::endl; 
	std::string decodedDummy = b64_decoder(dummy);
	std::cout << dummy<< " " <<  decodedDummy << std::endl;
	return 0;
}