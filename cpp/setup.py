import os
from distutils.core import setup, Extension

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
_INC_DIRS = ["inc"]

def main():
    setup(
        name = "cpp-package",
        description  = "cpp to be imported in python",
        author = "Ryan Mah",
        ext_modules = [
            Extension("audio_decode", ["src/audio_decode.cpp"], include_dirs = _INC_DIRS),
            Extension("audio_data", ["src/audio_data.cpp"], include_dirs = _INC_DIRS)
        ]
    )

if __name__ == "__main__":
    main()
