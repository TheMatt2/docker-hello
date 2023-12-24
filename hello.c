#define _XOPEN_SOURCE 500

#include <ftw.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>

void exec(const char *cmd)
{
  execl(cmd, cmd, (char *) NULL);

  // Only returns on error
  perror("execl");
  exit(1);
}

int listdir(const char *path)
{
  // https://stackoverflow.com/questions/12489/how-do-you-get-a-directory-listing-in-c
  DIR *dp;
  struct dirent *ep;
  dp = opendir(path);

  if (dp != NULL)
  {
    while ((ep = readdir(dp)) != NULL)
    {
      puts(ep->d_name);
    }

    closedir(dp);
    return 0;
  }
  else
  {
    perror("opendir");
    return 1;
  }
}

/* Started from ChatGPT
ssize_t read_thru(int fd, void *buf, size_t count) {
    ssize_t bytes_read = 0;
    ssize_t retval;

    while (bytes_read < count) {
        retval = read(fd, (char *) buf + bytes_read, count - bytes_read);

        if (retval == -1) {
            perror("read");
            return -1;  // Error occurred
        }

        if (retval == 0) {
            break;  // End of file
        }

        bytes_read += retval;
    }

    return bytes_read;
}
*/

#define CHUNK_SIZE 4096

int cat(const char *path)
{
  int fd = open(path, O_RDONLY);

  if (fd < 0)
  {
    perror("open");
    return 1;
  }

  static char buf[CHUNK_SIZE];

  while (1 == 1)
  {
    // Keep reading until no data left
    ssize_t n = read(fd, buf, CHUNK_SIZE);

    if (n < 0)
    {
      perror("read");
      return 1;
    }
    else if (n == 0)
    {
      break;
    }

    printf("%.*s", (int)n, buf);
  }

  return 0;
}

static int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
  // https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/
  printf("%-4s %5d %7jd   %s\n",
    (tflag == FTW_D) ?   "d"   : (tflag == FTW_DNR) ? "dnr" :
    (tflag == FTW_DP) ?  "dp"  : (tflag == FTW_F) ?
         (S_ISBLK (sb->st_mode) ? "f b" :
          S_ISCHR (sb->st_mode) ? "f c" :
          S_ISFIFO(sb->st_mode) ? "f p" :
          S_ISREG (sb->st_mode) ? "f r" :
          S_ISSOCK(sb->st_mode) ? "f s" :
                                  "f ?"):
    (tflag == FTW_NS) ?  "ns"  : (tflag == FTW_SL) ?  "sl" :
    (tflag == FTW_SLN) ? "sln" : "?",
    ftwbuf->level, (intmax_t) sb->st_size, fpath);
  return 0; /* To tell nftw() to continue */
}

int tree(const char *path)
{
  printf("%-4s %5s %7s   %s\n", "Type", "Depth", "Size", "Path");

  int flags = FTW_PHYS;

  if (nftw(path, display_info, 20, flags) == -1)
  {
    perror("nftw");
    return 1;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  char *path = ".";

  switch (argc)
  {
    case 1:
      break;
    case 3:
      path = argv[2];
      /* Intentional Fallthrough */
    case 2:
      if      (strcmp(argv[1], "ls"  ) == 0) return listdir(path);
      else if (strcmp(argv[1], "cat" ) == 0) return cat(path);
      else if (strcmp(argv[1], "tree") == 0) return tree(path);
      /* Intentional Fallthrough */
    default:
      printf("%s ls|cat|tree [path]\n", argv[0]);
      return 0;
  }

  // Show Hello
  printf("Hello, world!\n");

  exec("/bin/hello_go"); // no return
}
