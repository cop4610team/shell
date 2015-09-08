#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void my_setup() {}
void my_prompt() {}
void my_clean () {} 

void my_read(char *str) { 
  int pos;

  printf("Shell> ");
	
	// read in 250 characters
  fgets(str, 250, stdin);

  // add null char to end of input 
  pos = strlen(str) - 1;
  str[ pos ] = '\0';

  //printf("You entered: %s \n", str);  
}

void parse_whitespace(char *line) {
	
	//printf("begin_parse_white: %s \n", line);
	
	// remove leading and trailing whitespace
	int i;
	int begin = 0;
	int end = strlen(line) - 1;

	while(isspace(line[ begin ]))
	  begin++;

	while((end >= begin) && isspace(line[ end ]))
	  end--;

	// shift all characters back to the start of the string array
	for (i = begin; i <= end; i++)
	        line[ i - begin ] = line[ i ];

	// null terminate string
	line[ i - begin ] = '\0';
	 
	// remove extraneous whitespace 
	int x;
	for(i = x = 1; line[ i ]; ++i)
	  if(!isspace(line[ i ]) || (!isspace(line[ i - 1 ])))
	    line[ x++ ] = line[ i ];
	  
	// null terminate string
	line[ x ] = '\0';
	
	printf("end_parse_whitespace: %s \n", line);
	
}

void parse_arguments(char *str, char **args) {
	//printf("start_arg: %s \n", str);
	char * line = strtok (str, " ");
	int num_spaces = 0, i;
	
  // split string and append tokens to args 
  while(line) {
 	 args = realloc(args, sizeof(char*) * ++num_spaces);

  	if(args == NULL)
   	 exit(-1); /* memory allocation failed */

  	args[ num_spaces - 1 ] = line;

  	line = strtok(NULL, " ");
	}

	// realloc one extra element for the last NULL 
	args = realloc(args, sizeof(char*) * (num_spaces + 1));
	args[ num_spaces ] = 0;

// print the result 

	printf("end_parse_args \n");
	for (i = 0; i < (num_spaces+1); ++i)
  	printf ("args[%d] = %s\n", i, args[i]);

}

char **my_parse(char *line) {
	char **args = NULL;
	parse_whitespace(line);
	parse_arguments(line, args); 
	//args = expand_variables(args);
	//args = resolve_paths(args);

	return &line;
}

/*

void my_execute (char ** cmd) {
//Match against patterns
//Execute based on pattern 
//Print results
}
*/

/*****************
PROGRAM START *********/

int main() { 
  char *line;
  char **cmd; 
  
  while (1) {
    my_setup();
    my_prompt();
    my_read(line);
    cmd = my_parse(line);
    //my_execute(cmd);
    //my_clean();
  } 
  
  return 0; 
}
