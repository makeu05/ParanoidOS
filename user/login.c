#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static void
trim_newline(char *s)
{
  int n = strlen(s);
  if(n > 0 && s[n-1] == '\n')
    s[n-1] = '\0';
}

int
main(void)
{
  char username[32];
  char password[32];

  for(;;) {
    printf("ParanoidOS login: ");
    gets(username, sizeof(username));
    if(username[0] == 0)
      continue;
    trim_newline(username);

    printf("Password: ");
    gets(password, sizeof(password));
    if(password[0] == 0)
      continue;
    trim_newline(password);

    if(login(username, password) == 0) {
      printf("Bienvenue, %s.\n", username);
      char *argv[] = { "sh", 0 };
      exec("sh", argv);
      printf("exec sh failed\n");
      exit(1);
    }
    printf("Identifiants invalides.\n");
  }
}
