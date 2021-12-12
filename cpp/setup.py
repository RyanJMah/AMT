from distutils.core import setup, Extension

def main():
    setup(
        name = "test",
        description  = "this is a test...",
        author = "Ryan Mah",
        ext_modules = [Extension("test", ["src/test.cpp"])]
    )


if __name__ == "__main__":
    main()
