#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double convert(double fahrenheit) {
  double celsius = (fahrenheit - 32) / 1.8;
  return celsius;
}

void fToC() {
  char text[100000];
  fgets(text, sizeof(text), stdin);
  int len = strlen(text);

  // printf("%d", len);

  int onNumber = 0, onDot = 0, hasF = 0, numberSize = 0, startIndex = -1, index = 0;
  char *pointer;
  double out = 0.0;
  char num[16] = "";

  if (text[0] == '\0' || text[0] == '\n' || len == 0) {
    printf("Error");
    return;
  }

  for (int i = 0; i < len; i++) {
    char c = text[i];

    // printf("%c", c);
    // printf("s: %s\n", num);

    if (onNumber == 1) {
      if (onDot == 0 && isdigit(c)) {
        numberSize++;
        num[index] = c;
        index++;
      }
      
      if (onDot == 0 && c == '.') {
        onDot = 1;
        numberSize++;
        num[index] = '.';
        index++;
      }

      if (onDot == 1 && isdigit(c)) {
        numberSize++;
        num[index] = c;
        index++;
      }

      if ((onDot == 1 && c == 'F') || (onDot == 0 && c == 'F')) {
        out = strtod(num, &pointer);
        double celsius = convert(out);
        
        printf("%0.2fC", celsius);
        onNumber = 0, onDot = 0, hasF = 0, numberSize = 0, startIndex = -1;
        continue;
      }
    }

    if (onNumber == 0 && isdigit(c)) {
      onNumber = 1;
      startIndex = i;
      numberSize++;
      num[index] = c;
      index++;
    }

    if (onNumber == 0 && !isdigit(c)) {
      printf("%c", c);
    }
  }
}

int main() {
  fToC();
  return 0;
}
