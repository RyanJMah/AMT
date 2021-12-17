import os
import sys

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))

import audio_decode

def main():
    audio_decode.test()
    audio_decode.decode_wav("asdf")

if __name__ == "__main__":
    main()
