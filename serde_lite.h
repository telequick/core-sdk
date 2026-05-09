#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace telequick_core {

class SerdeWriter {
public:
    void write_bytes(const uint8_t* data, size_t len) {
        _buffer.insert(_buffer.end(), data, data + len);
    }

    template<typename T>
    void write_pod(T value) {
        // Redpanda uses direct little endian
        uint8_t temp[sizeof(T)];
        std::memcpy(temp, &value, sizeof(T));
        
        // Ensure little endian (assuming x86_64 LE host for this lite version)
        write_bytes(temp, sizeof(T));
    }

    void write_string(const std::string& str) {
        write_pod<int32_t>(str.length());
        write_bytes(reinterpret_cast<const uint8_t*>(str.data()), str.length());
    }

    struct envelope_marker { size_t size_offset; };
    envelope_marker begin_envelope(uint8_t version, uint8_t compat_version) {
        write_pod<uint8_t>(version);
        write_pod<uint8_t>(compat_version);
        envelope_marker m; m.size_offset = _buffer.size();
        write_pod<int32_t>(0); // dummy size
        return m;
    }
    void end_envelope(envelope_marker m) {
        int32_t real_size = _buffer.size() - m.size_offset - sizeof(int32_t);
        std::memcpy(&_buffer[m.size_offset], &real_size, sizeof(int32_t));
    }

    const std::vector<uint8_t>& buffer() const { return _buffer; }

private:
    std::vector<uint8_t> _buffer;
};

class SerdeReader {
public:
    SerdeReader(const uint8_t* ptr, size_t len) : _ptr(ptr), _len(len) {}

    const uint8_t* read_bytes(size_t len) {
        if (_len < len) throw std::runtime_error("SerdeReader buffer underflow");
        const uint8_t* ret = _ptr;
        _ptr += len;
        _len -= len;
        return ret;
    }

    template<typename T>
    T read_pod() {
        if (_len < sizeof(T)) throw std::runtime_error("SerdeReader buffer underflow");
        T value;
        std::memcpy(&value, _ptr, sizeof(T));
        _ptr += sizeof(T);
        _len -= sizeof(T);
        return value;
    }

    std::string read_string() {
        int32_t len = read_pod<int32_t>();
        if (len < 0) throw std::runtime_error("SerdeReader invalid string length");
        const uint8_t* data = read_bytes(len);
        return std::string(reinterpret_cast<const char*>(data), len);
    }
    
    struct envelope_header { uint8_t v; uint8_t cv; int32_t size; const uint8_t* end; };
    envelope_header read_envelope_header() {
        envelope_header h;
        h.v = read_pod<uint8_t>();
        h.cv = read_pod<uint8_t>();
        h.size = read_pod<int32_t>();
        h.end = _ptr + h.size;
        return h;
    }
    void skip_to_envelope_end(envelope_header h) {
        if (_ptr < h.end) {
            _len -= (h.end - _ptr);
            _ptr = h.end;
        }
    }

private:
    const uint8_t* _ptr;
    size_t _len;
};

} // namespace telequick_core
