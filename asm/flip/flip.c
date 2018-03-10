#include <unistd.h>

void g(void)
{
  char ch;
  if (read(0,&ch,1))
  {
    g();
    write(1,&ch,1);
  }
  // deallocate ch
}

int main(void)
{
  g();
}
