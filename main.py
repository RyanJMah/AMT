import os
import sys

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))

import lib.asdf as asdf
import lib.audio_decode as audio_decode

def main():
    asdf.test()
    # audio_decode.decode_wav("asdf")

if __name__ == "__main__":
    main()
