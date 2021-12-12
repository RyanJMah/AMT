import os
from distutils.core import setup, Extension

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
_SRC_DIR = os.path.join(_THIS_DIR, "src")
_INC_DIR = os.path.join(_THIS_DIR, "inc")

def _get_sources():
    return [os.path.join(_SRC_DIR, s) for s in os.listdir(_SRC_DIR)]

def main():
    setup(
        name = "test",
        description  = "this is a test...",
        author = "Ryan Mah",
        ext_modules = [Extension("test", _get_sources(), include_dirs = [_INC_DIR])]
    )


if __name__ == "__main__":
    main()
