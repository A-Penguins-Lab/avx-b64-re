#include <iostream>
#include <string>
#include <chrono>
#include <vector>

const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

std::vector<std::string> sentences = {
	"The cat slept on the mat.",
	"A dog barked loudly in the street.",
	"She opened the window to feel the breeze.",
	"The stars twinkled in the night sky.",
	"He wrote a letter to his old friend.",
	"The child laughed at the clown.",
	"Birds sang at dawn.",
	"The phone rang twice.",
	"They walked along the riverbank.",
	"The sun rose over the hills.",
	"Rain fell softly on the roof.",
	"The teacher explained the lesson.",
	"A car honked in the distance.",
	"She baked a chocolate cake.",
	"The train arrived late.",
	"He found a coin on the ground.",
	"The leaves rustled in the wind.",
	"She painted a beautiful picture.",
	"The ocean waves crashed loudly.",
	"He played his guitar all night.",
	"The lamp flickered in the storm.",
	"The baby smiled for the first time.",
	"She wore a red dress.",
	"The road was empty at midnight.",
	"The dog wagged its tail.",
	"He fixed his broken watch.",
	"Snow covered the mountains.",
	"The girl skipped down the street.",
	"He read a book by the fireplace.",
	"The plane flew across the sky.",
	"The shop closed early.",
	"She found her lost keys.",
	"The moonlight lit the garden.",
	"He drank a glass of water.",
	"The train whistled as it left.",
	"The flowers bloomed in spring.",
	"She cooked a delicious meal.",
	"The boat sailed into the harbor.",
	"He caught a fish in the lake.",
	"The market was crowded with people.",
	"The dog chased a butterfly.",
	"The old man told a story.",
	"The baby cried in the night.",
	"She bought a new hat.",
	"The horse galloped across the field.",
	"He climbed the tall tree.",
	"The candle melted slowly.",
	"The clock struck twelve.",
	"She danced in the rain.",
	"The door creaked open.",
	"The fox ran into the woods.",
	"He dropped his wallet.",
	"The wind howled at night.",
	"She knitted a scarf.",
	"The frog jumped into the pond.",
	"He drank coffee in the morning.",
	"The shopkeeper smiled politely.",
	"The bus stopped at the station.",
	"She drew a house on paper.",
	"The apple fell from the tree.",
	"He repaired his old bike.",
	"The owl hooted at midnight.",
	"She packed her suitcase.",
	"The train slowed at the crossing.",
	"The cat chased a mouse.",
	"He wore a blue jacket.",
	"The river flowed swiftly.",
	"She wrote in her diary.",
	"The soldier marched forward.",
	"He planted a rose in the garden.",
	"The bell rang loudly.",
	"She fed the birds.",
	"The kite flew high.",
	"The road curved to the left.",
	"He sang a happy song.",
	"The rabbit hopped away.",
	"She whispered a secret.",
	"The glass shattered on the floor.",
	"He washed the dirty dishes.",
	"The clouds hid the sun.",
	"She tied her shoelaces.",
	"The farmer harvested wheat.",
	"The child drew with crayons.",
	"He listened to the radio.",
	"The waves splashed on the shore.",
	"She planted tulips in the garden.",
	"The dog barked at strangers.",
	"He polished his shoes.",
	"The rain soaked his clothes.",
	"She opened the gift box.",
	"The singer bowed on stage.",
	"The storm shook the trees.",
	"He sharpened his pencil.",
	"The sun set behind the hills.",
	"She found a seashell on the beach.",
	"The baker sold fresh bread.",
	"He locked the door.",
	"The bicycle fell over.",
	"She smiled at the camera.",
	"The night was silent."
};

std::pair<std::string, unsigned int> b64_encoder(std::string input) {
    std::string b64_string;
	unsigned int l = input.length();

	for (unsigned int i = 0; i < l; i+=3) {
		// Notice how the loop is doing i+3 instead of i+1

		// (int)string is to convert it to integers. 
		int s = (int)input[i];
		
		// The short hand is for checking whether i+1 and i+2 are > l
		int s1 = (i + 1 < l) ? (int)input[i + 1] : 0;
      	int s2 = (i + 2 < l) ? (int)input[i + 2] : 0;

		// mysterious operation -- (1)
		long unsigned int a = s / 4;

		// mysterious operation -- (2)
		long unsigned int b = (s * 16) % 64 + (s1 / 16);
		
		// mysterious operation -- (3)
		long unsigned int c = (s1 * 4) % 64 + (s2 / 64);

		// mysterious operation -- (4)
		long unsigned int d = (s2 % 64);

		b64_string += base64_chars[a];
		b64_string += base64_chars[b];

		if (i + 1 < l) b64_string += base64_chars[c];
		else b64_string += "=";

		if (i + 2 < l) b64_string += base64_chars[d];
		else b64_string += "=";
	}

	return {b64_string, b64_string.length()};
}

std::pair<std::string, unsigned int> b64_decoder(std::string encodedInput) {
	std::string decodedString;
	long unsigned int eLength = encodedInput.length();

	for(unsigned int i = 0; i < eLength; i += 4) {
		// Notice how the skip now is +4 rather than +3

		char s = base64_chars.find(encodedInput[i]);
		char s1 = base64_chars.find(encodedInput[i + 1]);
		
		// For the last 2 characters, since l + 1 or l + 2 might not be valid
		char c2 = (i + 2 < eLength) ? encodedInput[i + 2] : '=';
		char c3 = (i + 3 < eLength) ? encodedInput[i + 3] : '=';

		long unsigned int s2 = (c2 != '=') ? base64_chars.find(c2) : 0;
		long unsigned int s3 = (c3 != '=') ? base64_chars.find(c3) : 0;

		// Mysterious operation -- (1)
		decodedString += static_cast<char>((s * 4) + (s1/16));

		// Mysterious operation -- (2)
		if (c2 != '=') {
			decodedString += static_cast<char>((s1 % 16) * 16 + (s2 / 4));
		}

		// Mysterious operation -- (3)
		if (c3 != '=') {
			decodedString += static_cast<char>((s2 % 4) * 64 + s3);
		}

	}

	return {decodedString, decodedString.length()};

}

void BasicLoadTest(int numTests) {
	// Record Two time points
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

    // Print them
    for (const auto& s : sentences) {
		std::pair encodedstring = b64_encoder(s);
		// std::cout <<"Man" << " " << encodedstring.first << std::endl; 

		std::pair deocdedString = b64_decoder(encodedstring.first);
		// std::cout << encodedstring.first << " " << deocdedString.first << std::endl;
    }

    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    
    // Derive the duration
    std::chrono::duration<double, std::milli> fp_ms = end - start; 
    std::chrono::duration<unsigned long long, std::milli> int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << fp_ms.count() << " milliseconds" << "";
}

void AdvancedLoadTest() {

}

int main (int argc, char* argv[]) {
	BasicLoadTest(2);

	return 0;
}