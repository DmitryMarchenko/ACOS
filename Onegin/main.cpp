#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

struct line {
    line() : str(nullptr), len(0) {}
    char* str;
    size_t len;
};

line* find_begins_of_lines(char* buffer, size_t buffer_size, size_t& endl_count) {
    for (int i = 0; i < buffer_size; ++i) {
        if (buffer[i] == '\n') {
            ++endl_count;
        }
    }

    line* begins_of_lines = new line[endl_count];
    begins_of_lines[0].str = buffer;
    int j = 1;

    for (int i = 0; i < buffer_size && j < endl_count + 1; ++i) {
        if (buffer[i] == '\n') {
            if (i < buffer_size - 1) {
                begins_of_lines[j].str = buffer + i + 1;
            }
            begins_of_lines[j - 1].len = begins_of_lines[j].str - begins_of_lines[j - 1].str - 1;
            ++j;
            buffer[i] = '\0';
        }
    }
    begins_of_lines[j - 2].len = buffer + buffer_size - begins_of_lines[j - 2].str - 1;

    return begins_of_lines;
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
    size_t a_i = to_str(a.str);
    size_t b_i = to_str(b.str);
    while (a.str[a_i] != '\0' && b.str[b_i] != '\0' && a.str[a_i] == b.str[b_i]) {
        ++a_i;
        ++b_i;
    }
    return (a.str[a_i] == '\0' && b.str[b_i] != '\0') || a.str[a_i] < b.str[b_i];
}

size_t return_to_str(const line& a) {
    if (&a == nullptr) {
        return 0;
    }
    size_t pos = a.len - 1;
    while (!(a.str[pos] >= 'A' && a.str[pos] <= 'Z') && !(a.str[pos] >= 'a' && a.str[pos] <= 'z')
           && &a.str[pos] != a.str) {
        --pos;
    }
    return pos;

}

bool reverse_comparator(const line& a, const line& b) {
    size_t a_i = return_to_str(a);
    size_t b_i = return_to_str(b);
    while (&a.str[a_i] != a.str && &b.str[b_i] != b.str && a.str[a_i] == b.str[b_i]) {
        --a_i;
        --b_i;
    }
    return (&a.str[a_i] == a.str && &b.str[b_i] != b.str) || a.str[a_i] < b.str[b_i];
}

void print_lines(const line* lines, size_t lines_count, std::FILE* file) {
    for (int i = 0; i < lines_count; ++i) {
        std::fwrite(lines[i].str, sizeof(char), lines[i].len, file);
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

int main() {
    std::FILE* f = fopen("input.txt", "r");
    std::fseek(f, 0, SEEK_END);
    auto file_size = static_cast<size_t>(std::ftell(f));

    std::fseek(f, 3, SEEK_SET);//fstat
    char* buffer = new char[file_size];
    std::fread(buffer, sizeof(char), file_size, f);
    std::fclose(f);

    size_t endl_count = 0;
    line* begins_of_lines = find_begins_of_lines(buffer, file_size, endl_count);

    std::sort(begins_of_lines, begins_of_lines + endl_count, comparator);

    std::FILE* f1 = fopen("output1.txt", "w");
    print_lines(begins_of_lines, endl_count, f1);
    std::fclose(f1);

    std::sort(begins_of_lines, begins_of_lines + endl_count, reverse_comparator);

    std::FILE* f2 = fopen("output2.txt", "w");
    print_lines(begins_of_lines, endl_count, f2);
    std::fclose(f2);

    recover_buffer(buffer, file_size);

    std::FILE* f3 = fopen("output3.txt", "w");
    std::fwrite(buffer, sizeof(char), file_size, f3);
    std::fclose(f3);

    return 0;
}