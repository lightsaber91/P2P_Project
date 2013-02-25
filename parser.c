#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *config_path = "/home/lightsaber/Programming/Progetto_P2P/config.ini";

struct setting {
  	double MAX_DOWN;
	double MAX_UP;
	char shared_folder[50];
};

struct setting *parse_config_file ()
{
	struct setting *s;
	s = malloc(sizeof(struct setting));
	size_t n = 50;
	char *line = malloc(n*sizeof(char));
	if(line == NULL) {
		perror("Failure allocating memory for parsing config.ini");
		exit(EXIT_FAILURE);
	}
	FILE *config = fopen(config_path, "r");
	if(config == NULL) {
		perror("Fail opening configuration file");
		exit(EXIT_FAILURE);
	}
	for(;;) {
		getline(&line, &n, config);
		if(strncmp(line, "EOF", 3) == 0)
			return s;
		if(strncmp(line, "#", 1) == 0);
		else {
			if(strncmp(line, "Shared_folder=", 14) == 0) {
				int i = 14;
				while(line[i] != ';') {
					s->shared_folder[i-14] = line[i];
					i++;
				}
			}
                        if(strncmp(line, "Download_speed=", 15) == 0) {
                                int i = 15;
				char d_max[strlen(line)-i];
                                while(line[i] != ';') {
                                        d_max[i-15] = line[i];
                                        i++;
                                }
				s->MAX_DOWN = atof(d_max);
                        }
                        if(strncmp(line, "Upload_speed=", 13) == 0) {
                                int i = 13;
                                char u_max[strlen(line)-i];
                                while(line[i] != ';') {
                                        u_max[i-13] = line[i];
                                        i++;
                                }
                                s->MAX_UP = atof(u_max);
                        }
		}
	}
}
