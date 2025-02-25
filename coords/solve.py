def decode_dtmf(file_path):
    # Read and sort points by z-coordinate first
    points = []
    with open(file_path, 'r') as file:
        for line in file:
            if line.startswith('v'):
                _, x, y, z = line.strip().split()
                points.append((float(x), float(y), float(z)))

    dtmf_map = {
        (697, 1209): '1', (697, 1336): '2', (697, 1477): '3',
        (770, 1209): '4', (770, 1336): '5', (770, 1477): '6',
        (852, 1209): '7', (852, 1336): '8', (852, 1477): '9',
        (941, 1209): '*',  (941, 1336): '0', (941, 1477): '#'
    }
    
    multitap_map = {
        '1': ['1'], '2': ['A', 'B', 'C'], '3': ['D', 'E', 'F'],
        '4': ['G', 'H', 'I'], '5': ['J', 'K', 'L'], '6': ['M', 'N', 'O'],
        '7': ['P', 'Q', 'R', 'S'], '8': ['T', 'U', 'V'], '9': ['W', 'X', 'Y', 'Z'],
        '0': ['0'], '#': ['#']
    }
    
    points.sort(key=lambda p: p[2])

    dtmf_sequence = []
    for x, y, _ in points:
        x, y = int(x), int(y)
        dtmf_char = dtmf_map.get((x, y), '')
        if dtmf_char:
            dtmf_sequence.append(dtmf_char)

    print(dtmf_sequence)
    
    result = []
    
    count = 1
    for i in range(len(dtmf_sequence) - 1):
        if dtmf_sequence[i+1] != '*':
            count = count + 1
            continue
        ch = multitap_map[dtmf_sequence[i]][count - 1]
        result.append(ch)
        count = 0
    
    return ''.join(result)

# Main execution
if __name__ == "__main__":
    result = decode_dtmf("project.obj")
    print(result)