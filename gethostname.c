#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// gethostname() - get host name of machine running this program
int gethostname(char *name, size_t len)
{
  if (len < 10)
  {             // check if the buffer is large enough
    return (1); // return 1 if len is less than 10
  }
  if (getenv("NEWHOSTNAME")) // check if the environment variable NEWHOSTNAME is set
  {
    strncpy(name, getenv("NEWHOSTNAME"), len); // copy the value of the environment variable NEWHOSTNAME to the buffer
  }

  return 0; // return 0 if everything is ok
}
