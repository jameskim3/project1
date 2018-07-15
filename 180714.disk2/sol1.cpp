extern void _write_data(int sector, unsigned char* data, int size);
extern void _read_data(int sector, unsigned char* data);
extern void _change_disk(int disk);

void insert_file(const char *file_name, const unsigned char *data, int offset, int size)
{}
void delete_file(const char *file_name, int offset, int size)
{}
void read_file(const char *file_name, const unsigned char *data, int offset, int size)
{}
void init()
{}