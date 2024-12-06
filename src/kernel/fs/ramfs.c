#include <ramfs.h>
#include <string.h> // Для функции strlen
#include <stdbool.h> // Для типа bool

char* itoa(int num, char* str, int base);

void reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

typedef struct {
    char name[MAX_NAME_LENGTH];
    uint8_t data[MAX_FILE_SIZE];
    size_t size;
    bool is_directory;
} RamFile;

RamFile ramfs[MAX_FILES];
// Счётчик файлов
int file_count = 0;

void init_ramfs() {
    file_count = 0;
}

int ramfs_create(const char* name, bool is_directory) {
    if (file_count >= MAX_FILES) {
        return -1;
    }

    RamFile* file = &ramfs[file_count];
    strncpy(file->name, name, MAX_NAME_LENGTH);
    file->size = 0;
    file->is_directory = is_directory;

    return file_count++;
}

int ramfs_write(int file_id, const void* buffer, size_t size) {
    if (file_id < 0 || file_id >= file_count || ramfs[file_id].is_directory) {
        return -1;
    }

    RamFile* file = &ramfs[file_id];
    size_t write_size = size > MAX_FILE_SIZE ? MAX_FILE_SIZE : size;
    memcpy(file->data, buffer, write_size);
    file->size = write_size;

    return write_size;
}

// Чтение данных из файла в RAM-файловой системе
int ramfs_read(int file_id, void* buffer, size_t size) {
    if (file_id < 0 || file_id >= file_count || ramfs[file_id].is_directory) {
        return -1; 
    }

    RamFile* file = &ramfs[file_id];
    size_t read_size = size > file->size ? file->size : size;
    memcpy(buffer, file->data, read_size);

    return read_size;
}

void print_file_info(int file_id) {
    if (file_id < 0 || file_id >= file_count) {
        kprint("Invalid file ID", 15);
        return;
    }

    RamFile* file = &ramfs[file_id];
    kprint("File: ", 15);
    kprint(file->name, 15);
    kprint(" Size: ", 15);
    char size_str[10];
    itoa(file->size, size_str, 10);
    kprint(size_str, 15);
    kprint(" Content: ", 15);
    newline();
    kprint((char*)file->data, 15);
    newline();
}

void test_ramfs() {
    init_ramfs(); 
    kprint(":: RamFS Test Start", 15);
    newline();

    kprint(":: Creating file 'test.txt'...", 15);
    newline();
    int file_id = ramfs_create("test.txt", false);
    if (file_id < 0) {
        kprint(":: Failed to create file", 15);
        newline();
        return;
    }
    kprint(":: File created successfully", 15);
    newline();
    print_file_info(file_id);

    kprint(":: Writing data to file...", 15);
    const char* test_data = "RamFS test";
    int write_size = ramfs_write(file_id, test_data, strlen(test_data));
    if (write_size < 0) {
        kprint(":: Failed to write to file", 15);
        return;
    }
    kprint(":: Data written successfully", 15);
    print_file_info(file_id);

    kprint(":: Reading data from file...", 15);
    char buffer[MAX_FILE_SIZE];
    int read_size = ramfs_read(file_id, buffer, MAX_FILE_SIZE);
    if (read_size < 0) {
        kprint(":: Failed to read from file", 15);
        return;
    }
    buffer[read_size] = '\0';

    kprint(":: Data read successfully", 15);
    kprint(":: Read content: ", 15);
    kprint(buffer, 15);

    if (strcmp(buffer, test_data) == 0) {
        kprint(":: RamFS test passed successfully!", 15);
    } else {
        kprint(":: RamFS test failed!", 15);
    }

    kprint(":: RamFS Test End", 15);
}

char* itoa(int num, char* str, int base) {
    int i = 0;
    bool isNegative = false;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
    if (isNegative)
        str[i++] = '-';
    str[i] = '\0';
    reverse(str, i);
    return str;
}
