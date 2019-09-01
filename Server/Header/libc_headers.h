/*
** EPITECH PROJECT, 2018
** my_functions.h
** File description:
** prototype of my libc functions
*/

#ifndef PSU_ZAPPY_2018_LIBC_HEADERS_H
#define PSU_ZAPPY_2018_LIBC_HEADERS_H

bool my_strcmp(const char *first, const char *two, bool case_sensitive);
bool is_numerical(const char to_verify);
bool is_alphabetical(const char to_verify);
bool is_alphanumerical(const char to_verify);
bool case_sensitive_validity(const char first, const char two);
bool my_strncmp(const char *first, const char
*two, unsigned int max, bool case_sensitive);
bool is_a_numeric_string(char const *string);
bool getchar_special_cases(char **new_str, int *to_translate, int *counter);
bool character_is_in_string(const char *in_string, const char *character);
bool str_in_str(const char *to_find, const char *in);
bool only_wrong_characters(const char *to_test, const char *bad_characters);
bool its_a_special_case(const char *str, int *place, va_list *list);
char *cut_str(const char *string_to_cut, const
unsigned int from, const unsigned int to);
char **my_str_to_word_array(const char *string_to_cut, const char *separator);
char **strings_to_two_dim(const unsigned int nb, ...);
char *my_strcat(const char *first, const char *second);
char *copy_after_x_character(const char *str, const char charac);
char *special_case(char **buffer);
char *part_of_str(char **buffer);
char *get_next_line(int fd, bool reset, unsigned int readsize);
char *my_getchar(const int to_translate);
char *my_strncat(const int unsigned number, ...);
char **get_file(char *file_path);
char *my_strcpy(const char *to_copy);
char *get_cleaned_str(char **tmp);
char *clean_str(const char *to_clean, const char *bad_characters);
int getnbr(const char *to_translate);
int safe_getnbr(const char *to_translate);
int main(int argc, const char **argv);
list_t *get_all_files_in_folder(char *path);
long unsigned int get_number_of_line(char *path);
node_t *case_first_node(list_t **list, node_t *new_member);
node_t *append(list_t **list, void *data_to_add);
struct sockaddr_in set_a_socket_adress(sa_family_t
        domain, unsigned int type, int port);
unsigned int its_end(const char *in_string, const char *separators, int where);
unsigned int get_number_of_dimensions(const
    char *in_string, const char *separator);
unsigned int is_lower_upper(const char to_verify);
unsigned int bigger(const char *one, const char *two);
unsigned int intlen(const int to_size);
unsigned int determine_modulo(const int to_print);
unsigned int find_occurencies(char *in_str, char *to_find);
unsigned int my_strlen(const char *str);
void get_next_separator(const char *string,
        const char *separator, unsigned int *from);
void get_the_tab(const char *string_to_cut,
        const char *separator, char ***array);
void free_two_dim_tab(char **tab);
void my_realloc_cut_str(char **new, const char *to_copy,
const unsigned int from, const unsigned int to);
void my_reallocstrcat(char **dest, const char *to_cat);
void reset_buffer(char **buffer, bool reset);
void get_the_number_in_str(char **new_str, unsigned
int counter, unsigned int power, int tmp);
void my_reallocstrncat(const unsigned number, char **to_realloc, ...);
void my_putchar(char to_print);
void putnbr(const int to_print);
void uputnbr(const unsigned int to_print);
void remove_two(node_t *to_remove, list_t **list);
void remove_from_linked_list(node_t *to_remove, list_t **list);
void *data_at_index(list_t *list, unsigned int index);
void free_the_list(list_t **list, void (free_func)(void *data));
void *get_data_from_value(list_t *list, void *to_find,
        bool (compare_func)(void *node_value, void *data_to_test));
void my_reallocstrcpy(char **dest, const char *to_copy);
void putstr(const char *str);
void vprint_special_cases(char flag, va_list *list);
void vprint(const char *to_print, ...);
void *safe_malloc(size_t size);
void set_timeout(struct timeval *timeout,
        __suseconds_t usecond, __time_t second);
void remove_by_value(list_t **list, void *to_find,
        bool (compare_func)(void *node_value, void *data_to_test));
unsigned int tab_len(const char **tab);
bool cmp_unsigned_int(node_t *tmp, void *value);
void free_two_dim_tab(char **tab);
list_t *get_all_files_in_folder(char *path);
void exit_error(const char *message, ...);
void list_for_each(list_t *list, void (func)(void *data));
void extract_a_node(list_t **list, node_t *to_remove);
node_t *get_node_by_value(list_t *list, void *value,
        bool (*cmp_func)(void *data, void *data_to_compare));
node_t *begin(list_t *list);
node_t *end(list_t *list);
void insert_at_index(list_t **list, void *data, uint32_t index);
#endif //PSU_ZAPPY_2018_LIBC_HEADERS_H
