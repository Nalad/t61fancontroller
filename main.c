#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define AUTO_SPEED 10
#define NO_FAN_SPEED 0

void change_speed(int speed);

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Too few arguments.\n");
        return EXIT_FAILURE;
    } else if (argc > 4) {
		fprintf(stderr, "Too many arguments.\n");
		return EXIT_FAILURE;
	}

    int sleep_no_fan = atoi(argv[1]);
    int sleep_auto_fan = atoi(argv[2]);
    int safe_temp = atoi(argv[3]);

    for (;;) {
        FILE *temp_input = fopen("/proc/acpi/ibm/thermal", "r");
        if (temp_input == NULL) {
            fprintf(stderr, 
                    "You are not running kernel with Thinkpad patch!\n");
            return EXIT_FAILURE;
        }
        // if something strange happened
        int temp = safe_temp + 1;
        fscanf(temp_input,"temperatures: %d", &temp);
        fclose(temp_input);

        bool is_auto = true;
        if (temp > safe_temp) {
            change_speed(AUTO_SPEED);
            is_auto = true;
        } else if (temp <= safe_temp) {
            change_speed(NO_FAN_SPEED);
            is_auto = false;
        }

        if (is_auto) {
            sleep(sleep_auto_fan);
        } else {
            sleep(sleep_no_fan);
        }
    }

    return 0;
}

void change_speed(int speed) {
    char tmp_string[60] = {0};
    char speed_string[5] = {0};

    switch(speed) {
        case AUTO_SPEED:    strcpy(speed_string, "auto"); break;
        case 0:             strcpy(speed_string, "0"); break;
        default:            fprintf(stderr, "Error in change_speed");
    }

    sprintf(tmp_string, "echo level %s > /proc/acpi/ibm/fan", speed_string);
    system(tmp_string);

    printf("Speed level has been changed to %s\n", speed_string);
}
