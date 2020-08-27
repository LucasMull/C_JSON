#include "JSON.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h> //for access()
#include <limits.h> //for MAX_INT
#include <string.h>
#include <locale.h>


FILE *select_output(int argc, char *argv[]);
char *get_buffer(char filename[]);
void reviver_test(json_item_st *item);

int main(int argc, char *argv[])
{
  char *locale = setlocale(LC_CTYPE, "");
  assert(locale);

  FILE *f_out = select_output(argc, argv);
  char *buffer = get_buffer(argv[1]);

  json_st *json = json_parse_reviver(buffer, NULL);

  json_item_st *item = json_item_get_root(json->root);
  while (item){
    item = json_item_next(item);
  }

  char *new_buffer = json_stringify(json, JSON_ALL);
  fwrite(new_buffer,1,strlen(new_buffer),f_out);
  free(new_buffer);

  json_destroy(json);

  free(buffer);
  fclose(f_out);

  return EXIT_SUCCESS;
}

FILE *select_output(int argc, char *argv[])
{
  char *arg_ptr=NULL;
  while (argc--){
    arg_ptr = *argv++;
    if ((*arg_ptr++ == '-') && (*arg_ptr++ == 'o') && (*arg_ptr == '\0')){
      assert (argc == 1); //check if theres exactly one arg left

      char *file = *argv;
      assert(access(file, W_OK)); //check if file exists

      return fopen(file, "w");
    }
  }

  return fopen("data.txt", "w");
}

/* returns file size in long format */
static long
fetch_filesize(FILE *ptr_file)
{
  fseek(ptr_file, 0, SEEK_END);
  long filesize = ftell(ptr_file);
  assert(filesize > 0);
  fseek(ptr_file, 0, SEEK_SET);

  return filesize;
}

/* returns file content */
static char*
read_file(FILE* ptr_file, long filesize)
{
  char *buffer = malloc(filesize+1);
  assert(buffer);
  //read file into buffer
  fread(buffer,sizeof(char),filesize,ptr_file);
  buffer[filesize] = '\0';

  return buffer;
}

/* returns buffer containing file content */
char*
get_buffer(char filename[])
{
  FILE *file = fopen(filename, "rb");
  assert(file);

  long filesize = fetch_filesize(file);
  char *buffer = read_file(file, filesize);

  fclose(file);

  return buffer;
}

void reviver_test(json_item_st *item){
  if (json_item_keycmp(item,"u") && json_item_numbercmp(item,3)){
        json_item_st *sibling = json_item_get_sibling(item,2);
        if (json_item_keycmp(sibling,"m")){
          fputs(json_item_get_string(sibling),stdout);
          fputc('\n',stdout);
        }
  }
}
