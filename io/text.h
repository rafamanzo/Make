typedef struct line{
  int size;
  char *txt;
} text_line;

typedef struct txt{
  text_line line;
  text_line *next_line;
} text;

#define fileClose fclose
