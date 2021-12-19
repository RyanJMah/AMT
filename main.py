import os
import sys

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))

import lib.audio_decode as audio_decode
# import lib.audio_data as audio_data

def main():
    # test = audio_data.AudioData(44100.0, 16, [1, 2, 3, 4])

    # asdf.test()
    # filepath = os.path.join(_THIS_DIR, "samples", "Piano_C_Major_Scale.wav")
    filepath = os.path.join(_THIS_DIR, "samples", "Piano_C_Major_Scale_115_BPM.wav")
    sample_rate, bit_depth, samples = audio_decode.decode_wav(filepath)

    print(f"sample_rate = {sample_rate}")
    print(f"bit_depth = {bit_depth}")
    print(f"samples_len = {len(samples)}")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(0)
