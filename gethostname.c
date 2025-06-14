#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

// gethostname() - get host name of machine running this program
int gethostname(char *name, size_t len)
{
  static int (*orig_gethostname)(char *, size_t) = NULL;

  if (!orig_gethostname)
  {
    orig_gethostname = dlsym(RTLD_NEXT, "gethostname");
  }

  if (len < 10)
  {             // check if the buffer is large enough
    return (1); // return 1 if len is less than 10
  }

  if (getenv("NEWHOSTNAME")) // check if the environment variable NEWHOSTNAME is set
  {
    strncpy(name, getenv("NEWHOSTNAME"), len); // copy the value of the environment variable NEWHOSTNAME to the buffer
  }
  else if (orig_gethostname) // if env var not set, call the original gethostname
  {
    return orig_gethostname(name, len);
  }

  return 0; // return 0 if everything is ok
}
