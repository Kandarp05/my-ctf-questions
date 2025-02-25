import string

# Nokia-style T9 mapping with special characters
T9_MAPPING = {
    'a': '2', 'b': '22', 'c': '222',
    'd': '3', 'e': '33', 'f': '333',
    'g': '4', 'h': '44', 'i': '444',
    'j': '5', 'k': '55', 'l': '555',
    'm': '6', 'n': '66', 'o': '666',
    'p': '7', 'q': '77', 'r': '777', 's': '7777',
    't': '8', 'u': '88', 'v': '888',
    'w': '9', 'x': '99', 'y': '999', 'z': '9999',
    '{': '#', '}': '#', '.': '#', '_': '#'
}

# Updated DTMF Keypad frequencies
KEYPAD = {
    '1': (697, 1209), '2': (697, 1336), '3': (697, 1477),
    '4': (770, 1209), '5': (770, 1336), '6': (770, 1477),
    '7': (852, 1209), '8': (852, 1336), '9': (852, 1477),
    '*': (941, 1209), '0': (941, 1336), '#': (941, 1477)
}

def text_to_t9(text):
    return '*'.join(T9_MAPPING.get(char, '') for char in text.lower() if char in T9_MAPPING)

def generate_3d_points(t9_sequence):
    points = []
    index = 0
    for s in t9_sequence:
        if s in KEYPAD:
            x, y = KEYPAD[s]
            z = (index + 1) * 100
            index = index + 1
            points.append((x, y, z))
    return points

def save_obj_file(points, filename="project.obj"):
    with open(filename, "w") as f:
        for x, y, z in points:
            f.write(f"v {x} {y} {z}\n")
    print(f"3D point file '{filename}' created!")

def jumble_points(points):
    import random
    jumbled = points.copy()
    random.shuffle(jumbled)
    return jumbled

if __name__ == "__main__":
    flag = "apoorvctf{kya_be_lode_teri_mkc}"  # Change this to your actual flag
    t9_sequence = text_to_t9(flag)
    print(f"T9 Sequence: {t9_sequence}")
    points = generate_3d_points(t9_sequence)
    jumbled_points = jumble_points(points)
    print(jumbled_points)
    save_obj_file(jumbled_points)
