S_BOX_0 = [
    [1, 0, 3, 2],
    [3, 2, 1, 0],
    [0, 2, 1, 3],
    [3, 1, 3, 2]
]

S_BOX_1 = [
    [0, 1, 2, 3],
    [2, 0, 1, 3],
    [3, 0, 1, 0],
    [2, 1, 0, 3]
]

def substitute(input_block):
    left_half = input_block >> 4
    right_half = input_block & 0b1111
    
    left_half = S_BOX_0[left_half >> 2][left_half & 0b11]
    right_half = S_BOX_1[right_half >> 2][right_half & 0b11]
    
    return (left_half << 4) | right_half

def permutation(input_block):
    return ((input_block & 0b1000) >> 3) | ((input_block & 0b0100) >> 1) | ((input_block & 0b0010) << 1) | ((input_block & 0b0001) << 3)

def lucifer_encrypt(plaintext, key):
    encrypted_text = ""
    for char in plaintext:
        encrypted_char = permutation(substitute(ord(char)))
        encrypted_char ^= (key & 0xFF)
        encrypted_text += chr(encrypted_char)
    return encrypted_text

def lucifer_decrypt(ciphertext, key):
    decrypted_text = ""
    for char in ciphertext:
        encrypted_char = ord(char)
        decrypted_char = encrypted_char ^ (key & 0xFF)
        decrypted_char = substitute(permutation(decrypted_char))
        decrypted_text += chr(decrypted_char)
    return decrypted_text

def lucifer():
    plaintext = input("Ingrese el texto a cifrar: ")
    key = int(input("Ingrese la clave (48 bits): "))
    encrypted_text = lucifer_encrypt(plaintext, key)
    print("Texto cifrado:", encrypted_text)
    decrypted_text = lucifer_decrypt(encrypted_text, key)
    print("Texto descifrado:", decrypted_text)

lucifer()
