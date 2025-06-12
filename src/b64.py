base64_table = {
    i: c for i, c in enumerate(
        'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'
    )
}

def encode_b64(string: str) -> str:
    encoded_array = []
    final_string = []
    byte_array = [ord(x) for x in string]
    bit_stream = ''.join(format(ord(x), '08b') for x in string)

    if len(byte_array) % 3 == 0:
        print(f"While encoding, the bit stream will be divided into: {len(byte_array) / 3}")
        for idx in range(0, len(bit_stream), 6):

            encoded_array.append(
                    bit_stream[idx: idx + 6]
            )

        for idx, chunk in enumerate(encoded_array):

            bit_stream_chunk = ''.join(chunk)
            ascii_b64_char = base64_table[
                int(bit_stream_chunk, 2)
            ]

            final_string.append(ascii_b64_char)

        return ''.join(final_string)



reverse_base64_table = {
    v: k for k,v in base64_table.items()
}

def decode_b46_text(string: str):
    encoded_array = []
    decoded_string = []
    bit_stream = ''.join(format(reverse_base64_table[x], '06b') for x in string)

    if len(string) % 4 == 0:
        print(f"While decoding, the bit stream will be divided into: {len(string) / 4}")
        for idx in range(0, len(bit_stream), 8):
            encoded_array.append(
                    bit_stream[idx: idx + 8]
            )

        for idx, chunk in enumerate(encoded_array):

            bit_stream_chunk = ''.join(chunk)
            
            decimal_num = int(bit_stream_chunk, 2)
            decoded_string.append(chr(decimal_num))

        return ''.join(decoded_string)

if __name__ == "__main__":
    string = 'Rishik'
    encoded_string = encode_b64(string)
    decoded_string = decode_b46_text(encoded_string)
    
    print(encoded_string, decoded_string)
