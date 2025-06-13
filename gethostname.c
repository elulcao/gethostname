#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

// gethostname() - get host name of machine running this program
int gethostname(char *name, size_t len)
{
  if (len < 1)
  {
    return 1; // invalid length
  }

  const char *new_name = getenv("NEWHOSTNAME");
  if (new_name && *new_name)
  {
    // ensure the buffer is always null terminated
    snprintf(name, len, "%s", new_name);
    return 0;
  }

  static int (*real_gethostname)(char *, size_t) = NULL;
  if (!real_gethostname)
  {
    real_gethostname = dlsym(RTLD_NEXT, "gethostname");
    if (!real_gethostname)
    {
      return 1; // failed to resolve symbol
    }
  }

  return real_gethostname(name, len);
}
