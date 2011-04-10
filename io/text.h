typedef struct line{
  int size;
  char *txt;
  int final;
} text_line;

typedef struct txt{
  text_line line;
  struct txt *next_line;
} text;

text getText(char *file);
void printText(text txt);
void writeText(char *file, text txt);
