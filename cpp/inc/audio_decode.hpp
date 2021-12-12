#pragma once

#include <string>
#include <vector>
#include <stdint.h>
#include <stddef.h>
#include "Python.h"

namespace AudioDecode {
    std::vector<uint8_t> _read_file(std::string filepath);
    size_t _decode_big_endian(size_t start, size_t end);
    size_t _decode_little_endian(size_t start, size_t end);
    std::string _uint_to_ascii(size_t num);

    std::vector<int32_t> decode_wav(std::string filepath);
};

namespace AudioDecode_PyWrappers {
    PyObject* decode_wav(PyObject* self, PyObject* args);
};
