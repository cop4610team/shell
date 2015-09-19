#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_prompt();
char *my_read();
char **my_parse(char *data);
void my_execute(char **cmd);
void my_clean();
char *parse_whitespace(char *input);
char **parse_arguments(char *parsed);
char **resolve_paths(char **args);
char **expand_variables(char **args);



void print_prompt() {
  char *user = getenv("USER");
  char *machine = getenv("MACHINE");
  char *pwd = getenv("PWD");

  printf("%s@%s: %s=> ", user, machine, pwd);

}


char *my_read() {
  char *str;
  int pos;

  //get data from stdin
  //read in 250 characters
  //if (fgets(str, 250, stdin) != NULL)
  fgets(str, 250, stdin);

  //add null char to end of input
  pos = strlen(str) -1;
  str[pos] = '\0';

 //printf("You entered: %s \n", str);

  //return as c string
  return str;

  //if dynamically created make sure to free during cleanup
}


char **my_parse(char *data) {
  //takes in c string as input
  //returns an array of c strings

  char *parsed;
  char **args = NULL;

  parsed = parse_whitespace(data);

  args = parse_arguments(parsed);
  //args = expand_variables(args);
  //args = resolve_paths(args);

  return args;
}


void my_execute(char **cmd) {
  //match against patterns
  //execute based on patterns
  //print results
  int i;

  //exit
  if(strcmp(cmd[0], "exit") == 0) {
    printf("Exiting Shell...\n\n");
    exit(1);
  }

  //echo
  if(strcmp(cmd[0], "echo") == 0) {
    if((cmd[1])[0] != '$') {
      //print out remaining arguments
      for(i=1; cmd[i]; i++)
        printf("%s ", cmd[i]);
      printf("\n");
    }
    else if( (cmd[1])[0] == '$'){
      //take off the first char
      memmove(cmd[1], cmd[1]+1, strlen(cmd[1]));
      //save original argument
      char *orig = strcpy(orig, cmd[1]);
      //make argument all uppercase for use
      for(i=0; (cmd[1])[i] != '\0'; i++)
        (cmd[1])[i] = toupper((cmd[1])[i]);
      char *ev = getenv(cmd[1]);
      if(ev == NULL)
        printf("%s: Undefined variable.\n", orig);
      else
        printf("%s\n", ev);
    }
  }



}//end my_execute




char *parse_whitespace(char *input) {
  //takes in c string as input
  //returns same c string after adding/removing whitespace
  //goal to transform c string such that there is exactly one space between each argument


  //leading white space
  //trailing white space
  //extra white space between arguments

  //no white spaces between characters
  //but for special characters

  //extra characters


  //printf("begin_parse_white: %s\n", input);

  //remove leading and trailing whitespace
  int i,
      begin,
      end;

  begin = 0;
  end = strlen(input) - 1;

  while(isspace(input[begin]))
    begin++;

  while((end >= begin) && isspace(input[end]))
    end--;

  //shift all characters back to the start of the string array
  for (i=begin; i<=end; i++)
    input[i-begin] = input[i];

  //null terminate string
  input[i-begin] = '\0';

  //remove extraneous whitespace
  int x;
  for(i=x=1; input[i]; ++i)
    if(!isspace(input[i]) || (!isspace(input[i-1])))
      input[x++] = input[i];

  //null terminate string
  input[x] = '\0';

  //printf("end_parse_whitespace: %s \n", input);

  return input;
}


char **parse_arguments(char *parsed) {
  //takes in a c string representing the input command with augmented whitespace
  //returns an array of c strings representing the arguments of the command

  char **y = NULL;

  //printf("start_arg: %s \n", str);
  char *x = strtok(parsed, " ");
  int i,
      num_spaces = 0;

  //split string and append token to args
  while(x) {
    y = realloc(y, sizeof(char*) * ++num_spaces);

    if (y == NULL)
      exit(-1); //memory allocation failed

    y[num_spaces - 1] = x;

    x = strtok(NULL, " ");
  }

  //realloc one extra element for the last NULL
  y = realloc(y, sizeof(char*) * (num_spaces+1));
  y[num_spaces] = 0;

  //print the result
  //printf("end_parse_args\n");
  //for(i=0; i<(num_spaces+1); ++i)
    //printf("args[%d] = %s\n", i, y[i]);

  return y;
}


char **resolve_paths(char **args) {
  return NULL;
}


char **expand_variables(char **args) {
  return NULL;
}


void my_clean() {
//  if (y)
  //  free(y);
}


int main() {
  char *input;
  char **cmd;

  while(1) {
    //print prompt
    print_prompt();

    //read input
    input = my_read();

    //transform input
    cmd = my_parse(input);

    //match against patterns, execute based on pattern, print results
    my_execute(cmd);

    //clean up
    //my_clean();
  }

  return 0;
}
