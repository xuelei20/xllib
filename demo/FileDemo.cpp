#include "../comm/File.h"
#include <string.h>

int main()
{
  xuel::AppendFile file("FileDemo.txt");
  char szContent[] = "hello txt.";
  file.append(szContent, strlen(szContent));
  // file.append(szContent, sizeof(szContent));
  return 0;
}
