#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <sys/stat.h>
#include <cstdlib>
#include <cctype>

struct line {
    line() : str(nullptr), len(0) {}
    char* str;
    size_t len;

    char* ptr() const {
        return str;
    }

    size_t size() const {
        return len;
    }
};

line* find_lines(char* buffer, size_t buffer_size, size_t& lines_count) {
    for (int i = 0; i < buffer_size; ++i) {
        if (buffer[i] == '\n') {
            ++lines_count;
        }
    }

    line* lines = new line[lines_count];
    lines[0].str = buffer;
    int j = 1;

    for (int i = 0; i < buffer_size && j < lines_count + 1; ++i) {
        if (buffer[i] == '\n') {
            if (i < buffer_size - 1) {
                lines[j].str = buffer + i + 1;
            }
            lines[j - 1].len = lines[j].ptr() - lines[j - 1].ptr() - 1;
            ++j;
            buffer[i] = '\0';
        }
    }
    lines[j - 2].len = buffer + buffer_size - lines[j - 2].ptr() - 1;

    return lines;
}

size_t to_str(const char* a) {
    size_t pos = 0;
    if (a == nullptr) {
        return pos;
    }
    while (!(a[pos] >= 'A' && a[pos] <= 'Z') && !(a[pos] >= 'a' && a[pos] <= 'z') && a[pos] != '\0') {
        ++pos;
    }
    return pos;
}

bool comparator(const line& a, const line& b) {
    size_t a_i = to_str(a.ptr());
    size_t b_i = to_str(b.ptr());
    while (a.ptr()[a_i] != '\0' && b.ptr()[b_i] != '\0' && tolower(a.ptr()[a_i]) == tolower(b.ptr()[b_i])) {
        ++a_i;
        ++b_i;
    }
    return (a.ptr()[a_i] == '\0' && b.ptr()[b_i] != '\0') || tolower(a.ptr()[a_i]) < tolower(b.ptr()[b_i]);
}

size_t return_to_str(const line& a) {
    if (&a == nullptr) {
        return 0;
    }
    size_t pos = a.size() - 1;
    while (!(a.ptr()[pos] >= 'A' && a.ptr()[pos] <= 'Z') && !(a.ptr()[pos] >= 'a' && a.ptr()[pos] <= 'z')
           && &a.ptr()[pos] != a.ptr()) {
        --pos;
    }
    return pos;

}

bool reverse_comparator(const line& a, const line& b) {
    size_t a_i = return_to_str(a);
    size_t b_i = return_to_str(b);
    while (&a.ptr()[a_i] != a.ptr() && &b.ptr()[b_i] != b.ptr() && tolower(a.ptr()[a_i]) == tolower(b.ptr()[b_i])) {
        --a_i;
        --b_i;
    }
    return (&a.ptr()[a_i] == a.ptr() && &b.ptr()[b_i] != b.ptr()) || tolower(a.ptr()[a_i]) < tolower(b.ptr()[b_i]);
}

void print_lines(const line* lines, size_t lines_count, std::FILE* file) {
    for (int i = 0; i < lines_count; ++i) {
        if (lines[i].size() == 0) {
            continue;
        }
        std::fwrite(lines[i].ptr(), sizeof(char), lines[i].size(), file);
        std::fwrite("\n", sizeof('\n'), sizeof('\n'), file);
    }
}

void recover_buffer(char* buffer, size_t buffer_size) {
    for (int i = 0; i < buffer_size; ++i) {
        if (buffer[i] == '\0') {
            buffer[i] = '\n';
        }
    }
}

char* to_buffer(const char* input_file_name, size_t& file_size) {
    std::FILE* f = fopen(input_file_name, "r");

    struct stat file_info;
    fstat(fileno(f), & file_info);
    file_size = static_cast<size_t>(file_info.st_size);

    char* buffer = new char[file_size];
    std::fread(buffer, sizeof(char), file_size, f);

    std::fclose(f);

    return buffer;
}

void print_sorted_lines(const line* lines, size_t lines_count, const char* output_file_name) {
    std::FILE* f = fopen(output_file_name, "w");
    print_lines(lines, lines_count, f);
    std::fclose(f);
}

void print_original(char* buffer, size_t file_size, const char* output_file_name) {
    recover_buffer(buffer, file_size);
    std::FILE* f = fopen(output_file_name, "w");
    std::fwrite(buffer, sizeof(char), file_size, f);
    std::fclose(f);
}

int main() {
    size_t file_size = 0;
    char* buffer = to_buffer("input.txt", file_size);

    size_t lines_count = 0;
    line* lines = find_lines(buffer, file_size, lines_count);

    std::sort(lines, lines + lines_count, comparator);

    print_sorted_lines(lines, lines_count, "output1.txt");

    std::sort(lines, lines + lines_count, reverse_comparator);

    print_sorted_lines(lines, lines_count, "output2.txt");

    print_original(buffer, file_size, "output3.txt");

    return 0;
}