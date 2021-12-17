import os
from distutils.core import setup, Extension

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
_INC_DIRS = [os.path.join(_THIS_DIR, "inc")]

def main():
    setup(
        name = "audio_decode",
        description  = "Signal Processing C++ libraries to be imported in Python",
        author = "Ryan Mah",

        packages = ["."],
        package_data = {
            "audio_decode": ["build/audio_decode.so"]
        }

        # ext_modules = [            
        #     Extension("audio_decode", ["src/audio_decode.cpp"], include_dirs = _INC_DIRS, library_dirs = ["boost_python38"]),
        #     # Extension("audio_data", ["src/audio_data.cpp"], include_dirs = _INC_DIRS)
        # ]
    )

if __name__ == "__main__":
    main()
